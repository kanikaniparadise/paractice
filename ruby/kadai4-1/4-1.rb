#!/usr/bin/ruby
def linear(x)
  return (180*x).to_s
end
File.open("output.txt" , "w"){|f|
  0.step(1,1.0/19.0){|x|
    f.puts(x.to_s+" "+linear(x))
  }
}
system('gnuplot 4-1.plt')
