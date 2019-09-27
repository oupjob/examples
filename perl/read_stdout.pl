#!/usr/bin/perl

open( README, '/home/r2d2/perl/loop.sh |' ) || die "can't open /dev/input/mice";

while( <README> ) {
	print $_;
}
