set term jpeg size 1600,2400

set out "./results.jpeg"
set multiplot layout 5,2

set autoscale xfix
set autoscale yfix
set size ratio 0.5
set xlabel "x"
set ylabel "y"

set contour
set view map

set title "Q=-1000 psi(x,y)"
set cntrparam levels increment -55,0.2,-50
set cbr [-55:-50]
splot "-1000_psi.dat" u 1:2:3 w l nosurface lt 2 lw 3 palette notitle

set title "Q=-1000 dzeta(x,y)"
set cntrparam levels increment -200,10,350
set cbr [-200:350]
splot "-1000_dzeta.dat" u 1:2:3 w l nosurface lt 2 lw 3 palette notitle


set pm3d
unset surface
unset contour


set title "Q=-1000 u(x,y)"
# set palette defined (-2 'blue', 5 'cyan', 7 'green', 10 'yellow', 16 'red')
set cbr [-2:16]
splot "-1000_u.dat" u 1:2:3 w p pt 5 ps 8 notitle

set title "Q=-1000 v(x,y)"
# set palette defined (-6 'blue', -5 'cyan', -4 'green', -3 'yellow', -2 'red')
set cbr [-6:1]
splot "-1000_v.dat" u 1:2:3 w p pt 5 ps 8 notitle

unset pm3d
set contour
set view map

set title "Q=-4000 psi(x,y)"
set cntrparam levels increment -218,1,-202
set cbr [-218:-202]
splot "-4000_psi.dat" u 1:2:3 w l nosurface lt 2 lw 3 palette notitle

set title "Q=-4000 dzeta(x,y)"
set cntrparam levels increment -750,40,1200
set cbr [-750:1200]
splot "-4000_dzeta.dat" u 1:2:3 w l nosurface lt 2 lw 3 palette notitle

set pm3d
unset surface
unset contour

set title "Q=-4000 u(x,y)"
# set palette defined (-2 'blue', 5 'cyan', 7 'green', 10 'yellow', 16 'red')
set cbr [-10:70]
splot "-4000_u.dat" u 1:2:3 w p pt 5 ps 8 notitle

set title "Q=-4000 v(x,y)"
# set palette defined (-6 'blue', -5 'cyan', -4 'green', -3 'yellow', -2 'red')
set cbr [-14:4]
splot "-4000_v.dat" u 1:2:3 w p pt 5 ps 8 notitle


unset pm3d
set contour
set view map

set title "Q=4000 psi(x,y)"
set cntrparam levels increment 200,1,217
set cbr [200:217]
splot "4000_psi.dat" u 1:2:3 w l nosurface lt 2 lw 3 palette notitle

unset multiplot