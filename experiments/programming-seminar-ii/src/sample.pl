use strict;
use warnings;

my $x    = 15;
my $str1 = "Hello, ";
my $y    = $x + 5;
my $str2 = $str1 . "World.";
my $z    = $y . $x;

print $y, "\n", $str2, "\n", $z, "\n";
