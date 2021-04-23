#Set the output to a png file
set terminal png size 400,400
#The file we'll write to
set output 'data.png'
# The graphic title
set title 'Indicii camerelor'
set grid

unset key
set xlabel 'Numarul camerei'
set ylabel 'Indicele camerei'
#plot the graphic
set xtics 1
set xrange [-1 : *] noreverse nowriteback
set yrange [* : *] reverse 
plot "plot_file.txt" with impulses lw 3
pause -1

