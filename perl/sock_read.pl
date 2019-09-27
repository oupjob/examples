#!/usr/bin/perl

use IO::Socket::INET;
# open( README, '/dev/pts/3 |' ) || die "can't open file";

# $as = new IO::Poll();

$socket = new IO::Socket::INET (
    LocalAddr => 'localhost',
    LocalPort => 2333,
    TYPE => SOCK_STREAM,
    #                               Reuse => 1,
    Listen => 3
);  

my $count = 1;
while (my $conn = $socket->accept()) {    
    $client_addr = $conn->peerhost();
    $client_port = $conn->peerport();
    
    # $str = "REQUEST: $client_addr:$client_port: ";
    
    $char = "";
#     while ( $char != " " ) {
#         $char = "";
#         read( $socket, $char, 1 );
#         $str .= $char;
#     }
    $conn->read( $str, 32 );
    print STDOUT "REQUEST: [$str]";
    
    $conn->print("Hello " . $str . "\n");
}

