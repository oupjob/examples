#!/usr/bin/perl

$pid = fork();

if ( !defined( $pid ) ) { 
	# can't fork	
	exit 2; 
}

elsif ( $pid ) {
	# parent process
	open( PIDFILE, ">", "/tmp/tsw_stress_test.pid" ) || exit 3;
	print PIDFILE $pid;
	close PIDFILE;
	exit 0;
} else {
	# child process
	`stress -t 30 -c 1`;
	exit $?;
}



# open( README, 'stress -t 20 -c 1 |' ) || die "can't open 'stress'";
# open( README, 'cat /dev/urandom |' ) || die "can't open 'stress'";

#while ( <README> ) {
#	print $_;
#}
