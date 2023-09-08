
suuretu =[]
Struct.new("Koumoku",:hizuke,:naiyou,:kingaku)
suuretu.push(Struct::Koumoku.new("2033-03-02","taxi",5000))
suuretu.push(Struct::Koumoku.new("2022-04-02","taxi",5000))
suuretu.push(Struct::Koumoku.new("2022-04-02","taxi",5000))
puts(suuretu)
puts(suuretu[0][0].split("-"))
for i in 0..suuretu.length-1
  keisann = suuretu[i][0].split("-")
  suuretu[i][0]=(keisann[0]<<keisann[1]).to_i
end



puts(suuretu.sort{|x, y| x["hizuke"] <=> y["hizuke"] })

Struct.new("Month_kingaku",:month,:kingaku)


mae = suuretu[0][0]
tukigoto=[]
tukigoto.push(Struct::Month_kingaku.new(mae,0))
j=0
puts(tukigoto[j][1])
puts("ここから")
for i in 0..suuretu.length-1
  puts(i)
  if mae==suuretu[i][0]
    tukigoto[j][1]+=suuretu[i][2]
  else
    mae = suuretu[i][0]
    tukigoto.push(Struct::Month_kingaku.new(mae,0))
    j+=1
    tukigoto[j][1]+=suuretu[i][2]
  end

end
puts(tukigoto)
