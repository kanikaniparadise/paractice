#!/usr/bin/ruby
def sig(x)
  return 180/(Math.exp(10-(20*x))+1)
end

def withcos(x)
  return 90*Math.cos((1+x)*Math::PI)+90
end

File.open("4-2-2.txt" , "w"){|f|
  0.step(1,1.0/19.0){|x|
    f.puts(x.to_s+" "+sig(x).to_s)
  }
}

File.open("4-2-1.txt" , "w"){|f|
  0.step(1,1.0/19.0){|x|
    f.puts(x.to_s+" "+withcos(x).to_s)
  }
}
system('gnuplot 4-2.plt')
