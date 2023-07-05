use strict;
use warnings;

foreach my $key (sort keys %ENV) {
    print "$key = $ENV{$key}\n";
}
