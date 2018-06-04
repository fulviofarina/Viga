set grid
set title 'Resultados generales'
set xlabel 'x'
set ylabel 'y'
set zlabel 'w'
set yrange [-0.25:0.25]
#set zrange [-1e6:1e6]
set zrange [-1e-1:1e-1]
#set zrange [-1:1]
set cbrange [-10:10]
set terminal gif animate delay 10
set output "pics/Surface.gif"
