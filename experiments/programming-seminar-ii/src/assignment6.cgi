#!/usr/bin/perl

use strict;
use warnings;
use utf8;
use CGI;
use CGI::Carp qw(fatalsToBrowser);

my $cgi = new CGI;

my $cookie = $cgi->cookie('counter');

if (!defined($cookie)) {
    $cookie = $cgi->cookie(-name=>'counter', -value=>1);
    print $cgi->header(-cookie=>$cookie);
    print $cgi->start_html(-title=>'counter', -charset=>'utf-8');
    print $cgi->h1('Counter'), "\n";
    print $cgi->p('count: 1'), "\n";
    print $cgi->end_html;
}
else {
    my $value = $cgi->cookie('counter');

    $value++;

    $cookie = $cgi->cookie(-name=>'counter', -value=>$value);

    print $cgi->header(-cookie=>$cookie);
    print $cgi->start_html(-title=>'counter', -charset=>'utf-8');
    print $cgi->h1('Counter'), "\n";
    print $cgi->p("count: $value"), "\n";
    print $cgi->end_html;
}
