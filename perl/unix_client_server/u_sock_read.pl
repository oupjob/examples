#!/usr/bin/perl

use IO::Socket::UNIX;
# open( README, '/dev/pts/3 |' ) || die "can't open file";

# $as = new IO::Poll();

my $sock_path = "/tmp/perl_unix_server.sock";

$socket = new IO::Socket::UNIX (
    Type    => SOCK_STREAM(),
    Local   => $sock_path,
    Listen  => 3
);  

my $count = 1;
while (my $conn = $socket->accept()) {    
    $conn->read( $str, 32 );
    print STDOUT "REQUEST: [$str]";
    
    $conn->print("Hello " . $str . "\n");
}

