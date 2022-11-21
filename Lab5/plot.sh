set term jpeg size 1800,1200

#S(it) global
set out "./results.jpeg"
set multiplot layout 2,3

set title "k=16"
# set ylabel "y"
# set xlabel "x"
# set view map

# splot "mulitmesh_V_16.dat" u 1:2:3 w p pt 5 ps 1 palette
set xlabel "x"
set ylabel "y"
set zlabel "v"
# set xrange [0:22.4]
# set yrange [0:22.4] 
# set logscale z

plot [-3:29][-3:29] "mulitmesh_V_16.dat" u 1:2:3 w p pt 5 ps 8 palette notitle
plot [-3:29][-3:29] "mulitmesh_V_8.dat" u 1:2:3 w p pt 5 ps 4 palette notitle
plot [-3:29][-3:29] "mulitmesh_V_4.dat" u 1:2:3 w p pt 5 ps 2 palette notitle
plot [-3:29][-3:29] "mulitmesh_V_2.dat" u 1:2:3 w p pt 5 ps 1 palette notitle
plot [-3:29][-3:29] "mulitmesh_V_1.dat" u 1:2:3 w p pt 5 ps 0.5 palette notitle


#S(it)
set title "S(it)"
set xlabel "it"
set ylabel "S"
set yrange[4.2:5.6]
plot "mulitmesh_S_16.dat" u 1:2 w l lw 2 t 'k=16', "mulitmesh_S_8.dat" u 1:2 w l lw 2 t 'k=8', "mulitmesh_S_4.dat" u 1:2 w l lw 2 t 'k=4', "mulitmesh_S_2.dat" u 1:2 w l lw 2 t 'k=2', "mulitmesh_S_1.dat" u 1:2 w l lw 2 t 'k=1'

# unset logscale x
# set ylabel 'y'
# set xlabel 'x'

# # V
# set view map
# set title "Relaksacja globalna w=0.6"
# set xrange [0:15]
# splot "global_v_0.6.dat" u 1:2:3 w p pt 5 ps 1 palette

# set title "Relaksacja globalna w=1.0"
# splot "global_v_1.dat" u 1:2:3 w p pt 5 ps 1 palette

# # Error
# set title "Bład rozwiązania w=0.6"
# splot "global_v_0.6_error.dat" u 1:2:3 w p pt 5 ps 1 palette

# set title "Bład rozwiązania w=1.0"
# splot "global_v_1_error.dat" u 1:2:3 w p pt 5 ps 1 palette

unset multiplot