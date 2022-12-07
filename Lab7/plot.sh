set term jpeg size 1600,2400

set out "./results.jpeg"
set multiplot layout 3,2

set autoscale xfix
set autoscale yfix
set size ratio 0.5

# set term png enhanced size 600,300 

# set size ratio -1

# set o "psi-1000.png"
set contour
# set dgrid3d
# set cntrparam levels 200 
# set cntrparam levels increment -200,10,350
# unset surface
set view map

set title "Q=-1000 psi(x,y)"
set cntrparam levels increment -55,0.2,-50
set cbr [-55:-50]
splot "1000_psi.dat" u 1:2:3 w l nosurface lt 2 lw 3 palette notitle

set title "Q=-1000 dzeta(x,y)"
set cntrparam levels increment -200,10,350
set cbr [-200:350]
splot "1000_dzeta.dat" u 1:2:3 w l nosurface lt 2 lw 3 palette notitle


set pm3d
unset surface
unset contour

# set xlabel "x"
# set ylabel "y"
# set cblabel "V"
# set cbrange [-2:16]

# set palette defined (-10 'blue', 0 'white', 10 'red')

# set title "nx=ny=100"
# splot "V5_100.dat" u 1:2:3 w p pt 5 ps 8 notitle

# set title "nx=ny=200"
# splot "V5_200.dat" u 1:2:3 w p pt 5 ps 8 notitle


# set cbrange [-0.8:0.8]
# set palette defined (-0.8 'blue', 0 'white', 0.8 'red')

# set title "nx=ny=100, e_1=1, e_2=1"
# splot "V6_1.dat" u 1:2:3 w p pt 5 ps 8 notitle

# set title "nx=ny=100, e_1=1, e_2=2"
# splot "V6_2.dat" u 1:2:3 w p pt 5 ps 8 notitle

# set title "nx=ny=100, e_1=1, e_2=10"
# splot "V6_10.dat" u 1:2:3 w p pt 5 ps 8 notitle


unset multiplot