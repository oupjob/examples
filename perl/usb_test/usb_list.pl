#!/usr/bin/perl

my $sysfs_usb_root = "/sys/bus/usb/devices";
#my @sysfs_usb = `ls -l $sysfs_usb_root | grep -v total`;
#@sysfs_usb = map { join( " -> ", ( split( /\s+/, $_) )[ 8, 10 ] ) } @sysfs_usb;

# print map { "> $_ \n"} @sysfs_usb;

# @sysfs_usb = grep { /host/ } map {  } @sysfs_usb;

opendir( dir, $sysfs_usb_root );
@dir_content = readdir( dir );
closedir( dir );

@dir_content = map { readlink( $sysfs_usb_root . "/" . $_ ) } @dir_content;
@dir_content = map { ( $x = $_  ) =~ s/\.\.\/\.\.\/\.\./\/sys/  } @dir_content;

print map { "$_\n" } @dir_content;

