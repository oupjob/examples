#!/usr/bin/perl

open( README, ' |' ) || die "can't open file";

while( <README> ) {
	print $_;
}
