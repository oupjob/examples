#!/usr/bin/perl

$TEST_FILE="/tmp/test";
$FILE_SIZE=1;

sub write_ {
	sysopen ( OUT, '/tmp/test', 1 ) || return 2;
	binmode( OUT, ":raw" );
	$i = 0;
	while ( $i != $FILE_SIZE ) {
        syswrite OUT, pack( 'c', 0b10101010 ), 1 || return 1;
        $i++;
	}
	close( OUT );
	return $i;
}

sub read_ {
    open ( IN, '<', '/tmp/test' ) || return 2;
    binmode( IN, ":unix" );
    $i = 0;
    $buf = "";
    while ( ! eof(IN) ) {
        read IN, $buf, 1;
        $i++;
        print STDOUT "$buf\n";
    }
    close IN;
    return $buf;
}

$write = write_( 0b10101010 );
$read  =  read_( 0b10101010 );

print "W=$write R=$read\n"
