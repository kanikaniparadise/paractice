#!/usr/bin/ruby
# coding: utf-8
require "fileutils"
Dir.foreach("./"){|folder|		#-----フォルダの名前を取得each する--
  if(!(folder.include?(".")))		#-----現在のフォルダ . や上のフォルダ .. を抜く--
    Dir.mkdir(folder + "/fig") unless Dir.exist?(folder + "/fig")
    Dir.glob("./"+folder+"/*.csv") {|file|		#shelに投げるファイルを選び、順に所定の場所に動かす、gnuplotをうごかし、完成したファイルをfigフォルダに入れる
      FileUtils.cp(file,"input.csv")
      system('gnuplot 2-1.plt')
      FileUtils.cp("out.svg",File.dirname(file)+"/fig/"+File.basename(file,".csv")+".svg")
    }
  end
}
File.delete("out.svg")
File.delete("input.csv")
