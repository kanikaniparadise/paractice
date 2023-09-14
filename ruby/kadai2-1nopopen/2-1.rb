#!/usr/bin/ruby
# coding: utf-8
require "fileutils"
Dir.foreach("./"){|folder|		#-----フォルダの名前を取得each する--
	if(!(folder.include?(".")))		#-----現在のフォルダ . や上のフォルダ .. を抜く--
		Dir.chdir(folder){
			begin
				Dir.mkdir("fig")
				rescue
			end
		}
		Dir.glob("./"+folder+"/*.csv") {|file|		#shelに投げるファイルを選び、順に所定の場所に動かす、shelをうごかし、完成したファイルをfigフォルダに入れる
			FileUtils.cp(file,"input.csv")
			system('./2-1.sh')
			FileUtils.cp("out.svg",File.dirname(file)+"/fig/"+File.basename(file,".csv")+".svg")
		}
	end
}
begin
	File.delete("out.svg")
	File.delete("input.csv")
	rescue
end
