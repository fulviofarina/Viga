set grid
set title 'Resultados generales'
set xlabel 'x'
set ylabel 'y'
set zlabel 'w'
set yrange [-0.25:0.25]
#set zrange [-1e6:1e6]
set zrange [-1e-3:1e-3]
#set zrange [-1:1]
set cbrange [-10:10]
set terminal gif animate delay 10
set output "pics/Surface.gif"
splot 'files/viga1.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga2.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga3.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga4.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga5.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga6.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga7.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga8.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga9.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga10.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga11.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga12.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga13.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga14.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga15.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga16.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga17.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga18.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga19.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga20.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga21.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga22.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga23.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga24.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga25.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga26.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga27.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga28.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga29.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga30.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga31.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga32.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga33.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga34.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga35.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga36.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga37.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga38.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga39.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga40.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga41.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga42.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga43.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga44.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga45.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga46.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga47.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga48.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga49.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga50.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga51.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga52.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga53.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga54.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga55.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga56.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga57.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga58.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga59.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga60.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga61.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga62.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga63.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga64.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga65.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga66.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga67.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga68.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga69.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga70.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga71.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga72.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga73.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga74.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga75.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga76.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga77.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga78.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga79.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga80.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga81.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga82.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga83.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga84.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga85.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga86.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga87.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga88.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga89.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga90.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga91.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga92.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga93.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga94.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga95.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga96.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga97.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga98.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
splot 'files/viga99.dat' using 1:5:2:1 with points palette pointsize 0.3 pointtype 1
