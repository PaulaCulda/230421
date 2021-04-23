#Set the output to a png file
set terminal png size 400,400
#The file we'll write to
set output 'data.png'
# The graphic title
set title 'Puterea semnalului'
set ylabel 'Puterea semnalului [dBm]'
set xlabel 'Numar esantioane'
set grid
unset key

#plot the graphic
plot "data.txt" with lines lc "violet" lw 3
pause -1

