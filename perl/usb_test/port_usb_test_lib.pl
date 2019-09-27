#!/usr/bin/perl

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
sub list_usb_hubs() {
    opendir( my $dh, $sysfs_usb_root ) or die "cannot open: $sysfs_usb_root";
    my @hubs = map { readlink( "$sysfs_usb_root/$_" ) } grep( /\d+-\d+$/, readdir( $dh ) );
    @hubs = map { local $_ = $_; s/(\.\.\/)+/\/sys\//g; $_ } @hubs;
    closedir( $dh );
# print map { "$_\n" } @hubs; 
    return @hubs;
}

