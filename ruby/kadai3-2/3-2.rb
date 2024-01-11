#!/usr/bin/ruby
# coding: utf-8
file_name = "kinmu_suzuki2023_12Dec_txt"
name=file_name.split("_")
name[1].slice!(-4,4)
name = name[1]
month = file_name
month =month.slice(-14,7)
require "time"
worktime = 0
File.open(file_name){|f|
	f.each_line{|line|
		if (!(line[0]=="#"))
			value = line.split
			
			start = Time.parse(value[1])
			fin = Time.parse(value[2])
			worktime+=fin-start
			
		end
	}
}
h_m = (worktime/60).divmod(60)   #-----秒だったのを分にしてから時間にする、あまりを分とする---divmod出力(商, あまり)
puts(name +" "+ month +" "+h_m[0].to_s+"h "+h_m[1].to_s+"m") 
