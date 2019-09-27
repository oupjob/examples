#!/usr/bin/perl

my $number = $ARGV[ 1 ];

my $fh;
if ( not open( $fh, "<", "/proc/cpuinfo" ) ) {
    print STDOUT 0;
    exit 0;
}

my @v_core_id = grep { /core id/ } <$fh>;
my %h = map { $_, 1 } @v_core_id;
@v_core_id = keys %h;

my $core_id = $v_core_id[ $number ];
$core_id = ( $core_id =~ /\d+/ )[ 0 ];

print STDOUT $core_id;
