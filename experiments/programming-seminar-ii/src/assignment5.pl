use strict;
use warnings;

my $input = <STDIN>;
chomp($input);

if ($input =~ /^[01]+5$/) {
    print "accepted\n";
} else {
    print "not accepted\n";
}
