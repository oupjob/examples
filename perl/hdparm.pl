#!/usr/bin/perl

@args = split( /,/, @ARGV[1] );
$test = shift @args;
%raid_results;

@hdparm_test_hdd = ();
@hdparm_test_cache=();

if ( !$test ) { 
    print STDOUT "0";
    exit 0;
}

foreach $arg (@args) {
    ($disk, $right) = split( /:/, $arg );
    
    if ( $right ) {
    # disk is RAID member   
    #   after checking all, RAID results will be substitute here  
        $result .= "$disk $right FUTURE_$disk,";
    } else {
        @hdparm_test_hdd = ("hdparm -t $disk");
        @hdparm_test_cache ("hdparm -T $disk");
        
        if ( $disk =~ /md\d+/ ) {
            $raid_results{$disk} = $res;
            $result .= "RAID $disk $res,";
        }
    }
}

foreach $raid ( keys %raid_results ) {
    $code = $raid_results{$raid};
    $result =~ s/FUTURE_$raid/$code/g;
}

