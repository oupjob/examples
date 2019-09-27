use strict;
use warnings;

my %h1 = (one => 1, two => 2);
my %h2 = (three =>3 , four => 4);

sub h_uno { \%h1 }

sub h_multi {
    my %all = (%h1, %h2);

    \%all;
}

while (my ($k, $v) = each %{h_uno()}) {
    print "k=$k, v=$v\n";
}

# следующий цикл не завершится никогда
while (my ($k, $v) = each %{h_multi()}) {
    print "k=$k, $v=$v\n";
}
