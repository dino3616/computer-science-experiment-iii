use strict;
use warnings;
use feature qw(say);

my @week = qw(Monday Tuesday Wednesday Thursday Friday Saturday Sunday);
my @input;
my $index = 0;

while (<STDIN>) {
    chomp;
    push @input, $_;
}

foreach my $input (sort {$a <=> $b} @input) {
    say "week[$input]: $week[$input - 1]";
}
