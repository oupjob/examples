#!/usr/bin/perl

use IO::Socket::INET;
#open( README, '/dev/pts/3 |' ) || die "can't open file
                              
$msg = $ARGV[0];
$msg .= " ";

# create a connecting socket
$socket = new IO::Socket::INET (
    PeerHost => 'localhost',
    PeerPort => 2333,
    Proto => 'tcp',
    TYPE => SOCK_STREAM
);

$size = $socket->send( $msg );
print "Sent data of length: $size\n";

shutdown($socket, 1);

$response = "";
$socket->recv( $response, 32 );
print "Response: $response\n";

$socket->close();



