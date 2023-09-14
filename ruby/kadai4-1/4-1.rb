#!/usr/bin/ruby
def linear(x)
  return (180*x).to_s
end

system('./4-1.sh')



File.open("output.txt" , "w"){|f|
  0.step(1,1.0/19.0){|x|
    puts x
    f.puts(x.to_s+" "+linear(x))
  }
}
