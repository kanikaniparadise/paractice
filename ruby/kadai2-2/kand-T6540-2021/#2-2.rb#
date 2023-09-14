#!/usr/bin/ruby
require "csv"

def search(month,n)
	f_csv=0
	temp=[]
	month="%02d" %month
	for i in 1..31 do
		i="%02d" %i
		file=month+i+".csv"
		begin
			f_csv=(CSV.read(file).map{|row| row[n, 1]})
			for j in 0..f_csv.length-1 do
				temp.push(f_csv[j][0].to_f)
			end
			rescue 
		end
		
	end
	t_leng=temp.length
	temp =temp.sort
	printf("max = ")
	puts(temp[t_leng-1])
	printf("min = ")
	puts(temp[0])
	printf("med = ")
	if(t_leng % 2==0) then
		puts((temp[t_leng/2]+temp[(t_leng/2)+1])/2)
	else
		puts(temp[t_leng/2])
	end
	
end

for i in 1..12 do
	puts("気温について、"+i.to_s+"月の")
	search(i,1)
end
for i in 1..12 do
	puts("湿度について、"+i.to_s+"月の")
	search(i,2)
end
for i in 1..12 do
	puts("CO2について、"+i.to_s+"月の")
	search(i,3)
end
