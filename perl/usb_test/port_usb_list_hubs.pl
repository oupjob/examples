#!/usr/bin/perl

my $sysfs_usb_root = "/sys/bus/usb/devices";

# read USB hub directories from sysfs
sub list_usb_hubs() {
    opendir( my $dh, $sysfs_usb_root ) or die "cannot open: $sysfs_usb_root";
    my @hubs = map { readlink( "$sysfs_usb_root/$_" ) } grep( /\d+-\d+$/, readdir( $dh ) );
    @hubs = map { local $_ = $_; s/(\.\.\/)+/\/sys\//g; $_ } @hubs;
    closedir( $dh );
# print map { "$_\n" } @hubs; 
    return @hubs;
}

my @hubs = list_usb_hubs();
print map { "$_\n" } @hubs;
