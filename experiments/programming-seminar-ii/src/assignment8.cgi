#!/usr/bin/perl

use strict;
use warnings;
use utf8;
use CGI;
use CGI::Carp qw(fatalsToBrowser);

my $cgi = new CGI;

my $body;

if ($cgi->param('send')) {
    my $value = $cgi->param('message-input');
    open my $fh, '>>', 'bbs.txt' or die "$!";
    print $fh "$value\n";
    close $fh;
}

open my $fh, '<', 'bbs.txt' or die "$!";
while (<$fh>) {
    $body .= $cgi->p($_);
}
close $fh;

print $cgi->header(-charset=>'utf-8');
print $cgi->start_html(-title=>'bbs', -charset=>'utf-8');
print $cgi->h1('bbs'), "\n";
print $cgi->start_form;
print $cgi->start_label;
print 'メッセージ: ';
print $cgi->textfield(-id=>'message-input', -name=>'message-input', -value=>'');
print $cgi->end_label;
print $cgi->submit(-name=>'send', -value=>'送信');
print $cgi->end_form;
print $body;
print $cgi->end_html;
