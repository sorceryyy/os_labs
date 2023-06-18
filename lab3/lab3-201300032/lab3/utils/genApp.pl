#!/usr/bin/perl

open(SIG, $ARGV[0]) || die "open $ARGV[0]: $!";

$n = sysread(SIG, $buf, 30000);

if($n > 512 *40){
	print STDERR "ERROR: App too large: $n bytes (max 20480)\n";
	exit 1;
}

print STDERR "OK: App block is $n bytes (max 512 * 40)\n";

$buf .= "\0" x (20480-$n);

open(SIG, ">$ARGV[0]") || die "open >$ARGV[0]: $!";
print SIG $buf;
close SIG;
