#!/usr/bin/ruby
# coding: utf-8
def search(want)
  each_month=[[],[],[],[],[],[],[],[],[],[],[],[]]
  n=Array.new(12,0)
  require "fileutils"
  Dir.foreach("./"){|folder|
    if(!(folder.include?(".")))
      Dir.glob("./"+folder+"/*.csv"){|file|
        month = File.basename(file)[0,2]
        File.open(file){|f|
          f.each_line{|line|
            each_month[(month.to_i)-1].push(line.split(",")[want].to_i) unless line.split(",")[want].to_i == 9999
          }
        }
      }
      case want
      when 1 then
        want = "温度について"
      when 2 then
        want = "湿度について"
      when 3 then
        want = "CO2について"
      else
      end
      printf(folder[-4,4]+"年の")
      puts want
      0.step(11,1){|i|
        puts((i+1).to_s+"月")
        m_length=each_month[i].length
        each_month[i]=each_month[i].sort
        printf("ave = ")
        puts(each_month[i].sum/m_length)
        printf("max = ")
        puts(each_month[i][m_length-1])
        printf("min = ")
        puts(each_month[i][0])
        printf("med = ")
        if(m_length % 2==0) then
          puts((each_month[i][m_length/2]+each_month[i][(m_length/2)+1])/2)
        else
          puts(each_month[i][m_length/2])
        end
      }
    end
  }
end

search(1)
search(2)
search(3)
