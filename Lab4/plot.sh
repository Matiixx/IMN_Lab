set term jpeg size 1600,2100

#S(it) global
set out "./results.jpeg"
set multiplot layout 3,2
set logscale x 10

set title "Relaksacja globalna"
set ylabel "S"
set xlabel "nr iteracji"
plot "global_0.6.dat" u 1:2 w l lw 2 t "w=0.6", "global_1.dat" u 1:2 w l lw 2 t 'w=1.0'

#S(it) local
set title "Relaksacja lokalna"
plot "local_s_1.dat" u 1:2 w l lw 2 t 'w=1.0', "local_s_1.4.dat" u 1:2 w l lw 2 t 'w=1.4', "local_s_1.8.dat" u 1:2 w l lw 2 t 'w=1.8', "local_s_1.9.dat" u 1:2 w l lw 2 t 'w=1.9'

unset logscale x
set ylabel 'y'
set xlabel 'x'

# V
set view map
set title "Relaksacja globalna w=0.6"
set xrange [0:15]
splot "global_v_0.6.dat" u 1:2:3 w p pt 5 ps 1 palette

set title "Relaksacja globalna w=1.0"
splot "global_v_1.dat" u 1:2:3 w p pt 5 ps 1 palette

# Error
set title "Bład rozwiązania w=0.6"
splot "global_v_0.6_error.dat" u 1:2:3 w p pt 5 ps 1 palette

set title "Bład rozwiązania w=1.0"
splot "global_v_1_error.dat" u 1:2:3 w p pt 5 ps 1 palette

unset multiplot