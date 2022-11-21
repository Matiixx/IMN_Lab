set term jpeg size 1600,1400

#S(it) global
set out "./results.jpeg"
set multiplot layout 2,2
set logscale x 10

set title "Relaksacja globalna"
set ylabel "S(it)"
set xlabel "it"
set xrange [1:100000]
plot "global_s_0.6.dat" u 1:2 w l lw 2 t "it_{max}=36886", "global_s_1.dat" u 1:2 w l lw 2 t 'it_{max}=23096'

#S(it) local
set title "Relaksacja lokalna"
plot "local_s_1.dat" u 1:2 w l lw 2 t 'it_{max}=12193', "local_s_1.4.dat" u 1:2 w l lw 2 t 'it_{max}=5547', "local_s_1.8.dat" u 1:2 w l lw 2 t 'it_{max}=1552', "local_s_1.9.dat" u 1:2 w l lw 2 t 'it_{max}=750'

unset logscale x
set ylabel 'y'
set xlabel 'x'

# V
set view map
set title "V(x,y)"
set xrange [0:15]
splot "global_v_0.6.dat" u 1:2:3 w p pt 5 ps 1 palette

# set title "Relaksacja globalna w=1.0"
# splot "global_v_1.dat" u 1:2:3 w p pt 5 ps 1 palette

# Error
set title "delta(x,y)"
splot "global_v_0.6_error.dat" u 1:2:3 w p pt 5 ps 1 palette

# set title "Bład rozwiązania w=1.0"
# splot "global_v_1_error.dat" u 1:2:3 w p pt 5 ps 1 palette

unset multiplot