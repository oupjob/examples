#!/usr/bin/perl

my @xrandr = `DISPLAY=:0 xrandr`;

@xrandr = grep { /\s+connected/ } @xrandr;
print map { "$_\n" } @xrandr;
print scalar @xrandr;
