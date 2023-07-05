use strict;
use warnings;

sub above_average {
    my @input = @_;
    my $sum = 0;
    my $count = 0;
    my @result;

    foreach my $input (@input) {
        $sum += $input;
        $count++;
    }

    my $average = $sum / $count;

    foreach my $input (@input) {
        if ($input > $average) {
            push @result, $input;
        }
    }

    return @result;
}

my @result = &above_average(10, 80, 32, 58, 13, 3);
print "@result\n";
