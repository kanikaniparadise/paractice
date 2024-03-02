
                                  
require 'matrix'
require "bigdecimal"
def etof (num)
  numout=num
  if(num.include?("e"))then
    numl=num.split("e")
    numout =(numl[0].to_f*(10**numl[1].to_f)).to_s
    puts numl
    puts(numl[0].to_f*(10**(numl[1].to_f)))
  end
  return numout
  
end

  



file = File.open("bunny.ply", "r")
datas = file.read().split("\n")
objf= File.open("bunny.obj","w")
number=0
i=0
numofv=0
numoff=0
vs =[[]]  
while(numofv==0 || numoff==0)do
  if(datas[i].include?("vertex")) then
    numofv = datas[i]
  elsif(datas[i].include?("face"))
    numoff = datas[i]
  end
  i=i+1
end
numofv=numofv.delete("^0-9").to_i
numoff=numoff.delete("^0-9").to_i
puts numoff
puts numofv

while (true !=datas[i].include?("end_header"))do
  i=i+1
end
puts(i)
i=i+1

numofv.times{
  data = datas[i].split(" ")
  out = "v " +BigDecimal((data[0].to_f*10).to_s).to_s("f")+" "+BigDecimal((data[1].to_f*10).to_s).to_s("f")+" "+BigDecimal((data[2].to_f*10).to_s).to_s("f")
  vs.push([data[0].to_f*10,data[1].to_f*10,data[2].to_f*10])
  objf.puts(out)
  i=i+1
}
numoff.times{
  data = datas[i].split(" ")
  out = "f " + (data[1].to_i + 1).to_s+" "+(data[2].to_i + 1).to_s+" "+(data[3].to_i + 1).to_s
  objf.puts(out)
  vn=[]
  bects=[]
  puts("aa")
  puts(data[1])
  puts("vv")
  points=Vector[vs[(data[1].to_i)+1],vs[(data[2].to_i)+1],vs[(data[3].to_i)+1]]
  puts(points)
  puts("3")
  bects[0]=(Vector.elements(points[1]) - Vector.elements(points[0])).to_a
  puts(bects)
  puts("4")
  bects[1]=(Vector.elements(points[2]) - Vector.elements(points[0])).to_a
  puts(bects[0][1])
  puts(bects[1][2])
  puts(bects[0][2])
  puts(bects[1][1])
  
  puts("5")
  vn[0]=(bects[0][1] * bects[1][2])-(bects[0][2] * bects[1][1])
  vn[1]=(bects[0][2] * bects[1][0])-(bects[0][0] * bects[1][2])
  vn[2]=(bects[0][0] * bects[1][1])-(bects[0][1] * bects[1][0])
  size = ((vn[0]**2)+(vn[1]**2)+(vn[2]**2))**(1/2.0)
  out= "vn " + (vn[0]/size).to_s + " " + (vn[1]/size).to_s + " " + (vn[2]/size).to_s
    objf.puts(out)
  i=i+1
}
  
