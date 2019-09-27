#!/usr/bin/perl

$disk = $ARGV[0];

@hdparm_hdd_test=`hdparm -t $disk`;
@hdparm_cache_test=`hdparm -T $disk`;

$hdd_test = @hdparm_hdd_test[ (scalar @hdparm_hdd_test) - 1 ];
$cache_test = @hdparm_cache_test[ (scalar @hdparm_cache_test) - 1 ];

$hdd_test = "Timing cached reads:   5582 MB in  2.00 seconds = 2792.07 MB/sec";

$hdd_test = $1 if $hdd_test =~ /=\s+(\d+\.\d+)/;
$cache_test = $1 if $cache_test =~ /=\s+(\d+\.\d+)/; 

print "$hdd_test $cache_test";