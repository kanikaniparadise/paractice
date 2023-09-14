#!/usr/bin/ruby
# coding: utf-8
require "date"
now = Date.today
start = Date.new(2023,8,26)
p (now-start).to_s
puts(start.to_s+" から "+now.to_s+" までの暦日数は、 "+ (((now-start).to_i).to_s)+"日")
