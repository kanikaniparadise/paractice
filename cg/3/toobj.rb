file = File.open("bunny.ply", "r")
datas = file.read().split("\n")
objf= File.open("bunny.obj","w")
number=0
i=0
numofv=0
numoff=0
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
  out = "v " + data[0]+" "+data[1]+" "+data[2]
  objf.puts(out)
  i=i+1
}
numoff.times{
  data = datas[i].split(" ")
  out = "f " + (data[1].to_i + 1).to_s+" "+(data[2].to_i + 1).to_s+" "+(data[3].to_i + 1).to_s
  objf.puts(out)
  i=i+1
}
