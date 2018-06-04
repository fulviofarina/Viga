set grid
set title 'Resultados generales'
set xlabel 'x'
set ylabel 'w(x)'
#set yrange [-1e6:1e6]
set yrange [-1e-1:1e-1]
#set yrange [-1:1]
set cbrange [-10:10]
set terminal gif animate delay 10
set output "pics/Plot.gif"
