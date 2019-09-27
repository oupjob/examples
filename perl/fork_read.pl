#!/usr/bin/perl

open( README, '/dev/pts/3 |' ) || die "can't open file";

while( <README> ) {
	print $_;
}
