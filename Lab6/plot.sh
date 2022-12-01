set term jpeg size 2400,1600

set out "./results.jpeg"
set multiplot layout 2,3

set pm3d
set view map
unset surface

set xlabel "x"
set ylabel "y"
set cblabel "V"
set cbrange [-10:10]

set palette defined (-10 'blue', 0 'white', 10 'red')

set title "nx=ny=50"
splot "V5_50.dat" u 1:2:3 w p pt 5 ps 8 notitle

set title "nx=ny=100"
splot "V5_100.dat" u 1:2:3 w p pt 5 ps 8 notitle

set title "nx=ny=200"
splot "V5_200.dat" u 1:2:3 w p pt 5 ps 8 notitle


set cbrange [-0.8:0.8]
set palette defined (-0.8 'blue', 0 'white', 0.8 'red')

set title "nx=ny=100, e_1=1, e_2=1"
splot "V6_1.dat" u 1:2:3 w p pt 5 ps 8 notitle

set title "nx=ny=100, e_1=1, e_2=2"
splot "V6_2.dat" u 1:2:3 w p pt 5 ps 8 notitle

set title "nx=ny=100, e_1=1, e_2=10"
splot "V6_10.dat" u 1:2:3 w p pt 5 ps 8 notitle


unset multiplot