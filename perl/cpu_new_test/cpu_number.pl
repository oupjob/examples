#!/usr/bin/perl

my $fh;
if ( not open( $fh, "<", "/proc/cpuinfo" ) ) {
    print STDOUT 0;
    exit 0;
}

my @cpu_info = read( $fh );
my @index;
my @v_core_id;
my ( $i, $i_proc ) = ( 0, 0 );
my $core_id;

foreach my $line ( @cpu_info ) {
    $i_proc = $i if ( $line =~ /processor/ );
    
    if ( $line =~ /core id/ ) {
        $line =~ /(\d+)/;
        $core_id = $1;
        if ( not $core_id ~~ @v_core_id ) {
            push( @v_core_id, $core_d );
            push( @index, $i_proc );
        }
    }
    
    ++$i;
}
