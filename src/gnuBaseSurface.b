set grid
set title 'Resultados generales'
set xlabel 'x'
set ylabel 'y'
set zlabel 'w'
set yrange [-0.05:0.05]
set zrange [-1e6:1e6]
set cbrange [-50:50]
set terminal gif animate delay 10
set output "pics/Surface.gif"
