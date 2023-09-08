#!/usr/bin/ruby
require "open3"
require "csv"

def plot_to_out(x,y,z,b,type,name,folder) 
	File.open("output.txt","w"){|a|
		for i in 0..x.length-1 do
			a.puts(x[i][0].to_s + " "+(y[i][0].to_f/0.25).to_s + z[i][0].to_s+b[i][0].to_s)		#データを受取、温度を0.25で割ることで0~25を0~100に変換
		end
	}
	File.open("gnuplot.plt" , "w"){|gn|			#gnuplot に送るファイルの作成
		gn.puts("set terminal "+type+" size 1600,800 font'arial, 22'")
		gn.puts('set output "fig/'+name[0,4]+"."+type+'"')
		gn.puts("set lmargin 20 ")
		gn.puts("set rmargin 10 ")
		gn.puts("set size 1,1")
		gn.puts("set xdata time")
		gn.puts("set timefmt '%H:%M:%S'")
		gn.puts("set ylabel 'Temprature / Humidity' offset -4")
		gn.puts("set y2label 'CO2[ppm]'")
		gn.puts("set yrange [0:100]")
		gn.puts("set y2range [0:1600]")
		gn.puts("set y2tics")
		gn.puts("set ytics ('5°C 20%%' 20,'10°C 40%%' 40,'15°C 60%%' 60,'20°C 80%%' 80,'25°C 100%%' 100,) nomirror")
		gn.puts("set xtics format '%H:%M'")
		gn.puts("plot 'output.txt' using 1:2 with line axis x1y1 title 'Temp','output.txt' using 1:3 with line axis x1y1 lc 'blue' title 'Humi','output.txt' using 1:4 with line axis x1y2 lc 'green' title 'CO2'")

	}
	Open3.popen3("gnuplot"){|gn|
		gn.puts('call "gnuplot.plt"')
	}
	
end
def plot(folder,file)
	Dir.chdir("./"+folder){
	type= "png"
	x1 = CSV.read(file).map{|row| row[0, 1]}
	temp=CSV.read(file).map{|row| row[1, 1]}
	hum=CSV.read(file).map{|row| row[2, 1]}
	co2=CSV.read(file).map{|row| row[3, 1]}
	plot_to_out(x1,temp,hum,co2,type,file,folder)
}
end


Dir.foreach("./"){|folder|
	if(!(folder.include?(".")))
		for i in 1..12
			month="%02d" %i
			for i in 1..31 do
				i="%02d" %i
				file=month+i+".csv"
				begin
					plot(folder,file)
					rescue
				end
			end
		end
	end
	
}
