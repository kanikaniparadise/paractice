#!/usr/bin/ruby
require "open3"
require "csv"

def plot_to_out(type,x,y,name) 
	File.open("output.txt","w"){|a|
		for i in 0..x.length-1 do
			a.puts(x[i][0].to_s+y[i][0].to_s)
		end
	}
	Open3.popen3("gnuplot"){|gn|
		gn.puts("set terminal "+type)
		gn.puts('set output "'+name+"."+type+'"')
		gn.puts("set xdata time")
		gn.puts("set timefmt '%H:%M:%S'")
		gn.puts("plot 'output.txt' using 1:2 with line title '"+name+"'")
		
	}
end

file='0106.csv'
type= "svg"


x1 = CSV.read(file).map{|row| row[0, 1]}
temp=CSV.read(file).map{|row| row[1, 1]}
hum=CSV.read(file).map{|row| row[2, 1]}
co2=CSV.read(file).map{|row| row[3, 1]}

plot_to_out(type,x1,temp,"temp")
plot_to_out(type,x1,hum,"hum")
plot_to_out(type,x1,co2,"CO2")







=begin
Open3.popen3("gnuplot"){|gn|
	gn.puts("set terminal png")
	gn.puts('set output "plot_sample.png"')
	gn.puts("plot x")
	
}
=end
