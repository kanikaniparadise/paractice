#!/usr/bin/ruby
require "date"
now = Date.today
start = Date.new(2023,8,26)
puts(start.to_s+" から "+now.to_s+" までの暦日数は、 "+ (((now-start).to_s).split("/"))[0]+"日")
