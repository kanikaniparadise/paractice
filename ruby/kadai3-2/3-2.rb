#!/usr/bin/ruby
file_name = "kinmu_okazaki2023_08Aug.txt"
name=file_name.split("_")
name[1].slice!(-4,4)
name = name[1]
month = file_name
month =month.slice(-14,7)
puts month
require "time"
worktime = 0
File.open(file_name){|f|
	f.each_line{|line|
		if (!(line[0]=="#"))
			puts line
			value = line.split
			
			start = Time.parse(value[1])
			fin = Time.parse(value[2])
			puts(start,fin)
			worktime+=fin-start
			
		end
	}
}
h_m = (worktime.divmod(60))[0].divmod(60)
puts(name +" "+ month +" "+h_m[0].to_s+"h "+h_m[1].to_s+"m") 
