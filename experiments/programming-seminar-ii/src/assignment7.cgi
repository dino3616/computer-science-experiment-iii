#!/usr/bin/perl

use strict;
use warnings;
use utf8;
use CGI;
use CGI::Carp qw(fatalsToBrowser);

# フォームの「送信」ボタンが押された時に、フォームから入力された文字列がわかるメッセージ (例えば、「??? が入力されました。」など) を Web ページにに出力する CGI プログラム

# 「送信」ボタンが押された時は、属性 name の「send」に対して属性 value の「送信」がセットされます。param を使って if の条件を作ってみましょう。この条件を満たしたら、変数 body にフォームから入力された文字列を代入します。

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

