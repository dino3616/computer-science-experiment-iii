use strict;
use warnings;

print "Input integers A: ";
my $x = <STDIN>;
print "Input integers B: ";
my $y = <STDIN>;

chomp($x);
chomp($y);

my $sum = 0;
for (my $i = $x; $i <= $y; $i++) {
    $sum += $i;
}

print "Sum of integers between $x and $y is $sum.\n";

