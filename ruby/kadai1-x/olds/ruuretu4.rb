#!/usr/bin/ruby

require 'ostruct'
suuretu =[]
Struct.new("Koumoku",:hizuke,:naiyou,:kingaku)
suuretu.push(Struct::Koumoku.new("2033-03-02","taxi",5000))
suuretu.push(Struct::Koumoku.new("2022-04-02","taxi",5000))
suuretu.push(Struct::Koumoku.new("2022-04-02","book",5000))
suuretu.push(Struct::Koumoku.new("2022-04-02","book",5000))

for i in 0..suuretu.length-1
  keisann = suuretu[i][0].split("-")
  suuretu[i][0]=(keisann[0]<<keisann[1]).to_i
end




suuretu.sort{|x, y| x["hizuke"] <=> y["hizuke"] }


k = nil
mae = suuretu[0][0]
tukigoto=[]
tukigoto.push(OpenStruct.new({month:mae,kingaku:0}))
j=0
puts(tukigoto[j].kingaku)
puts("ここから")

koumoku= { }

for i in 0..suuretu.length-1
  puts(i)
  koumoku[suuretu[i][1]]=suuretu[i][1]
  if mae==suuretu[i][0]
    k=suuretu[i][1]
    tukigoto[j].kingaku+=suuretu[i][2]

  else
    mae = suuretu[i][0]
    tukigoto.push(OpenStruct.new({month:mae,kingaku:0}))
    j+=1
    tukigoto[j].kingaku+=suuretu[i][2]
  end
  if tukigoto[j][k].nil?
    tukigoto[j][k]=suuretu[i][2]
    puts("Uni")
  else
    tukigoto[j][k]+=suuretu[i][2]
    puts("ouiu")
  end

end
puts(tukigoto)
puts(koumoku)
koumokugoto=OpenStruct.new({})
koumoku.each { |i|
  puts(i)
  puts("hitokugiri")
  puts(koumoku.i)
  koumokugoto[i]=0
  for j in 0..tukigoto.length-1
    koumokugoto[koumoku[i]]+=tukigoto[j][koumoku[i]]
  end
}
puts(koumokugoto)
