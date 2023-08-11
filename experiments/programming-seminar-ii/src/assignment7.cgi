#!/usr/bin/perl

use strict;
use warnings;
use utf8;
use CGI;
use CGI::Carp qw(fatalsToBrowser);

my $cgi = new CGI;

my $body;

if ($cgi->param('send')) {
    my $value = $cgi->param('value');
    $body = $cgi->p("$value が入力されました。");
}

print $cgi->header(-charset=>'utf-8');
print $cgi->start_html(-title=>'form', -charset=>'utf-8');
print $cgi->h1('form'), "\n";
print $cgi->start_form;
print $cgi->textfield(-name=>'value', -value=>'');
print $cgi->submit(-name=>'send', -value=>'送信');
print $cgi->end_form;
print $body;
print $cgi->end_html;
