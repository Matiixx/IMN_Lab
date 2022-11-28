set term jpeg size 1600,1200

#S(it) global
set out "./results.jpeg"
set multiplot layout 2,3


#S(it)
set title "S(it, k)"
set xlabel "it"
set ylabel "S"
set autoscale xy
plot "multimesh_S_16.dat" u 1:2 w l lw 2 t 'k=16 it=0-80'   ,\
     "multimesh_S_8.dat"  u 1:2 w l lw 2 t 'k=8 it=81-213'  ,\
     "multimesh_S_4.dat"  u 1:2 w l lw 2 t 'k=4 it=214-371' ,\
     "multimesh_S_2.dat"  u 1:2 w l lw 2 t 'k=2 it=372-510' ,\
     "multimesh_S_1.dat"  u 1:2 w l lw 2 t 'k=1 it=511-516'

# set ylabel "y"
# set xlabel "x"
set pm3d
set view map
unset surface

# splot "mulitmesh_V_16.dat" u 1:2:3 w p pt 5 ps 1 palette
set xlabel "x"
set ylabel "y"
set zlabel "v"
set xrange [0:25.6]
set yrange [0:25.6]

set palette defined (-1 'blue', 0 'white', 1 'red')

set title "V_{k=16}(x,y)"
splot "multimesh_V_16.dat" u 1:2:3 w p pt 5 ps 8 notitle

set title "V_{k=8}(x,y)"
splot "multimesh_V_8.dat" u 1:2:3 w p pt 5 ps 8 notitle

set title "V_{k=4}(x,y)"
splot "multimesh_V_4.dat" u 1:2:3 w p pt 5 ps 8 notitle

set title "V_{k=2}(x,y)"
splot "multimesh_V_2.dat" u 1:2:3 w p pt 5 ps 8 notitle

set title "V_{k=1}(x,y)"
splot "multimesh_V_1.dat" u 1:2:3 w p pt 5 ps 8 notitle

# unset view map


unset multiplot