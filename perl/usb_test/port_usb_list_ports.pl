#!/usr/bin/perl

my $sysfs_usb_root = "/sys/bus/usb";
my $sysfs_usb_root_devices = "$sysfs_usb_root/devices";
my $sysfs_usb_root_drivers = "$sysfs_usb_root/drivers";
my $sysfs_usb_hubs = "$sysfs_usb_root_drivers/hub";

use constant HUB_USB_CLASS => "09";

sub path_chdir($$) {
    my $current = shift;
    my $target = shift;
    
    return $target if ( $target =~ /^\// );
    
    my @lcur = split /\//, $current;
    my @ltrg = split /\//, $target;
    
    my $ncur = scalar @lcur;
    my $ntrg = scalar @ltrg;
    
    my $j = $ncur;
    for( my $i = $ntrg; $i > 0; --$i, --$j ) {
        if ( $ltrg[ $i ] eq ".." ) { $lcur[ $j ] = ""; }
        else { $lcur[ $j ] = $trg[ $i ]; }
    }
    
    return join( '/', @lcur );
}

# read subdirs of dir content readed to @_ and extract matches for regex $code
sub grep_subdirs(&@) {	
	my $code = shift;
	my @res;
	
	foreach my $dpath ( @_ ) {
		next if ( not $dpath or $dpath eq ".." or $dpath eq "." );
		opendir( dir, $dpath );
		my @dir_content = readdir( dir );
		foreach $_ ( @dir_content ) {
			next if ( not $_ or $_ eq ".." or $_ eq "." );
			if ( &$code ) { push( @res, $dpath . "/" . $_ ); }
		}
		closedir( dir );
	}
	
	return @res;
}

# read USB hub directories from sysfs
sub list_usb_hubs_from_devices() {
    opendir( my $dh, $sysfs_usb_root_devices ) or die "cannot open: $sysfs_usb_root_devices";
    # my @hubs = map { readlink( "$sysfs_usb_root_devices/$_" ) } grep( /usb\d+$/, readdir( $dh ) );
    my @hubs;
    foreach ( readdir( $dh ) ) {
        next if( $_ eq '.' or $_ eq '..' );
        my $dir_name = readlink( "$sysfs_usb_root_devices/$_" );
        $dir_name =~  s/(\.\.\/)+/\/sys\//g;
        my $file_name = "$dir_name/bDeviceClass";
        if ( -e $file_name ) {
            open( my $fh, $file_name ) or next;
            read( $fh, my $class, 32 );
            close( $fh );
            chomp( $class );
            push( @hubs, $dir_name ) if ( $class eq HUB_USB_CLASS );
        }
    }
    # @hubs = map { local $_ = $_; s/(\.\.\/)+/\/sys\//g; $_ } @hubs;
    closedir( $dh );
    return @hubs;
}

sub list_usb_hubs_from_drivers() {
    opendir( my $dh, $sysfs_usb_hubs ) or die "cannot open: $sysfs_usb_hubs";
    
    my @hubs;
    foreach ( readdir( $dh ) ) {
        next if( $_ eq '.' or $_ eq '..' );
        if ( $_ =~ /\d+-\d+/ ) {
            my $dir_name = readlink( "$sysfs_usb_hubs/$_" );
            $dir_name =~  s/(\.\.\/)+/\/sys\//g;
            push( @hubs, $dir_name ); # if ( $dir_name =~ /\d+-\d+\// );
        }
    }
    return @hubs;
}

sub list_hub_usb_ports($) {
    my $hub_sysfs_path = shift;
    $hub_sysfs_path = readlink( $hub_sysfs_path ) if ( -l $hub_sysfs_path );
    
    my @ports;
    opendir( my $dh, $hub_sysfs_path ) or return @ports;
    @ports = readdir( $dh );
    closedir( $dh );
    return map { "$hub_sysfs_path/$_" } grep { /(?<!sup)port/ } @ports;
}

sub get_attached_scsi_devices_from_port($) {
    my $port_sysfs_path = shift;
    my $device_sfp;
    $device_sfp = readlink( "$port_sysfs_path/device" ) if ( -l "$port_sysfs_path/device" );
    
    my @dc_host = grep_subdirs { /host\d+/ } ( $device_sfp );
    my @scsi_devices = map { local $_ = $_; $_ =~ s/(host\d+)/\1\/scsi_host\/\1\/device/; $_; } @dc_host;
    
    @scsi_devices = grep_subdirs { /target(\d+:)+/ } @scsi_devices;
    @scsi_devices = map { readlink( $_ ) } @scsi_devices;
    @scsi_devices = grep_subdirs { /(\d+:)+/ } @scsi_devices;
    
    return @scsi_devices;
}

sub disk_name_from_sysfs_scsi_dev_path($) {
    my $sysfs_scsi_dev_path = shift;
    $sysfs_scsi_dev_path = "$sysfs_scsi_dev_path/block";
    opendir( my $dh, $sysfs_scsi_dev_path );
    my @disk = grep { /sd\d+/ } readdir( $dh );
    closedir( $dh );
    
    return "/dev/$disk[ 0 ]";
}

sub get_attached_scsi_devices_from_hub($) {
    my $hub_sysfs_path = shift;
    my @ports = list_hub_usb_ports( $hub_sysfs_path );
}

sub get_attached_scsi_device_from_root() {
    
}

# my @dev_hubs = list_usb_hubs_from_devices();
# print "Hubs (from '$sysfs_usb_root_devices'): \n", map { "\t$_\n" } @dev_hubs;

my @drv_hubs = list_usb_hubs_from_drivers();
# print "Hubs (from '$sysfs_usb_hubs'): \n", map { "\t$_\n" } @drv_hubs;
# map { print "hub: $_:\n", map { "\t$_\n" } list_hub_usb_ports( $_ ), "" } @drv_hubs;

print map { get_attached_scsi_devices_from_port( $_ ) } map { list_hub_usb_ports( $_ ) } @drv_hubs;

