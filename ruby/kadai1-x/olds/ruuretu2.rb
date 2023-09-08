#!/usr/bin/ruby

require 'ostruct'
rist =[]
Struct.new("Koumoku",:hizuke,:naiyou,:kingaku)
rist.push(Struct::Koumoku.new("2033-03-02","taxi",5000))
rist.push(Struct::Koumoku.new("2022-04-02","taxi",5000))
rist.push(Struct::Koumoku.new("2022-04-02","book",5000))
rist.push(Struct::Koumoku.new("2022-04-02","book",5000))

for i in 0..rist.length-1
  keisann = rist[i][0].split("-")
  rist[i][0]=(keisann[0]<<keisann[1]).to_i
end




rist.sort{|x, y| x["hizuke"] <=> y["hizuke"] }


k = nil
mae = rist[0][0]
tukigoto=[]
tukigoto.push(OpenStruct.new({month:mae,kingaku:0}))
j=0
puts(tukigoto[j].kingaku)
puts("ここから")

koumoku= { }

for i in 0..rist.length-1
  puts(i)
  koumoku[rist[i][1]]=rist[i][1]
  if mae==rist[i][0]
    k=rist[i][1]
    tukigoto[j].kingaku+=rist[i][2]

  else
    mae = rist[i][0]
    tukigoto.push(OpenStruct.new({month:mae,kingaku:0}))
    j+=1
    tukigoto[j].kingaku+=rist[i][2]
  end
  if tukigoto[j][k].nil?
    tukigoto[j][k]=rist[i][2]
    puts("Uni")
  else
    tukigoto[j][k]+=rist[i][2]
  end

end
puts(tukigoto)		#月ごと、その項目ごとを表示
puts(koumoku)


koumokugoto=OpenStruct.new({})


koumoku.each {|i|

  isub=i.values_at
  puts(isub)
  puts("hitokugiri")
  eval("koumokugoto."+ isub +"=nozomi")
}
puts(koumokugoto)
