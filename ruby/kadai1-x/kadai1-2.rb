#!/usr/bin/ruby
require "csv"
require 'ostruct'
rist = CSV.read("input.csv")

for i in 0..rist.length-1
  keisann = rist[i][0].split("-")
  rist[i][0]=(keisann[0]<< keisann[1]).to_i
  rist[i][2]=rist[i][2].to_i
end




rist.sort{|x, y| x[0] <=> y[0] }


k = nil
mae = rist[0][0]
tukigoto=[]
tukigoto.push(OpenStruct.new({month:mae,kingaku:0}))
j=0

koumoku= { }
				#mae=一つ前が何年何月の処理を行ったのかを保管する。　k=なんの科目を処理しようとしているか
for i in 0..rist.length-1
  koumoku[rist[i][1]]=rist[i][1]
  k=rist[i][1]
  if mae==rist[i][0]
    
    tukigoto[j].kingaku+=rist[i][2]

  else
    mae = rist[i][0]
    tukigoto.push(OpenStruct.new({month:mae,kingaku:0}))
    j+=1
    tukigoto[j].kingaku+=rist[i][2]
  end
  if tukigoto[j][k].nil?
    tukigoto[j][k]=rist[i][2]
  else
    tukigoto[j][k]+=rist[i][2]
  end
end
puts(tukigoto)		#月ごと、その項目ごとを表示



koumokugoto=OpenStruct.new({})


koumoku.each {|j,i|
  for k in 0..tukigoto.length-1		#-----月ごとの中から項目ごとを抽出して、項目ごとのデータを作る
  	begin
 	if koumokugoto[i].nil?
    		eval("koumokugoto[i]=tukigoto[k]."+i)
    	else
    		eval("koumokugoto[i]+=tukigoto[k]."+i)
    	end
    	rescue
    end
  end
}
puts(koumokugoto)
File.open("result.txt","w"){|a|
	a.puts(tukigoto)
	a.puts(koumokugoto)
}
