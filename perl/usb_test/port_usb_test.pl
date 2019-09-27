#!/usr/bin/perl

my $sysfs_usb_root = "/sys/bus/usb/devices";
my $mnt_point = "/media/__USB_TEST_MNT_POINT";
my $test_filename = $mnt_point . "/__USB_TEST_FILE";

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

sub test_usb {
	my $len = 1024;
	my ( $sign1, $sign2 ) = ( 0b10101010, 0b01010101 );	
	
	# write signatures to offsets, 0..$len - 1 by sign1 , $len..$len*2 by sign2
	exit( -1 ) if( not open( my $tfh, ">:raw", $test_filename ) );
	for( my $i = 0; $i < $len; ++$i ) { print $tfh pack( "C", $sign1 ); }
	for( my $i = 0; $i < $len; ++$i ) { print $tfh pack( "C", $sign2 ); }
	close( $tfh );
	
	# read signatures
	exit( -1 ) if( not open( my $tfh, "<:raw", $test_filename ) );
	my $buffer;
	read $tfh, $buffer, $len * 2;
	
	for( my $i = 0; $i < $len; $i++ ) { 
		if ( unpack( "C", substr( $buffer, $i, 1 ) ) ne $sign1 ) {
			print "1";
			exit( 0 );
		}	
	}
	for( my $i = $len; $i < ( $len * 2 ); $i++ ) {
		if ( unpack( "C", substr( $buffer, $i, 1 ) ) ne $sign2 ) {
			print "1";
			exit( 0 );
		}		
	}
	close( $tfh );
	
	unlink( $test_filename );
}

# define USB stick in sysfs
opendir( dir, $sysfs_usb_root );
my @sysfs_usb_dir_content = readdir( dir );
closedir( dir );
@sysfs_usb_dir_content = map { readlink( $sysfs_usb_root . "/" . $_ ) } @sysfs_usb_dir_content;
foreach $sdir ( @sysfs_usb_dir_content ) {
	$sdir =~ s/\.\.\/\.\.\/\.\.\//\/sys\//;
}
#print map { "$_\n" } @sysfs_usb_dir_content;

my @dc_host = grep_subdirs { /host\d+/ } @sysfs_usb_dir_content;
if ( not scalar @dc_host ) { print "1"; exit 0; }
#print map { "$_\n" } @dc_host;

my @dc_target = grep_subdirs { /target.+/ } @dc_host;
if ( not scalar @dc_target ) { print "1"; exit 0; }
#print map { "$_\n" } @dc_target;

my @dc_target_addrs = grep_subdirs { /(\d+:)+/ } @dc_target;
if ( not scalar @dc_target_addrs ) { print "1"; exit 0; }
#print map { "$_\n" } @dc_target_addrs;

my @dc_block = grep_subdirs { /block/ } @dc_target_addrs;
if ( not scalar @dc_block ) { print "1"; exit 0; }
#print map { "$_\n" } @dc_block;

my @dc_disk = grep_subdirs { /sd.+/ } @dc_block;
if ( not scalar @dc_disk ) { print "1"; exit 0; }
#print map { "$_\n" } @dc_disk;

# test each USB stick
foreach $_ ( @dc_disk ) {
	my @path = split /\//, $_;
	my $key = pop @path;
	# $disks{$key} = $_;
	
	# Find partiotions of USB Stick
	# in case if first partition is not sdX1 (but sdXN)
	my @fdisk_out = `fdisk -l`;
	chop @fdisk_out;
	@fdisk_out = grep { /$key\d+/ } @fdisk_out;
	my $partition = ( split /\s+/, $fdisk_out[ 0 ] )[ 0 ];
	
	# mount first partition
	mkdir( $mnt_point ) if not -d $mnt_point;
	my @garbage = `mount $partition $mnt_point 2>&1`;
	if ( $? ) { print @garbage; rmdir( $mnt_point ); exit 0; }
	
	test_usb();
	
	@garbage = `umount $mnt_point`;
	if ( $? ) { print @garbage; exit 0; }
	rmdir( $mnt_point ); # NOTE: remove dir may does after unmount  only (safe remove)

	print "0";
}

