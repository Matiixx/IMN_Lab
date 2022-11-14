#S
set term jpeg size 600,600

set out "./S_global.jpeg"
# set multiplot layout 1,2

set title "S(it)"
plot "global_0.6.dat" u 1:2 w l lw 2 t '0.6', "global_1.dat" u 1:2 w l lw 2 t '1.0'

# unset multiplot

# V
set term jpeg size 600,600
set out "V_0.6.jpeg"
set view map

splot "global_v_0.6.dat" u 1:2:3 w p pt 5 ps 1 palette


# set out "./rk2.jpeg"
# set multiplot layout 1,4

# set title "v(t)"
# plot "metoda_rk2_1e-05.dat" u 1:4 w l lw 2 t 'tol=10^-^5', "metoda_rk2_0.01.dat" u 1:4 w l lw 2 t 'tol=10^-^2'

# set title "x(t)"
# plot  "metoda_rk2_1e-05.dat" u 1:3 w l lw 2 t 'tol=10^-^5', "metoda_rk2_0.01.dat" u 1:3 w l lw 2 t 'tol=10^-^2'

# set title "dt(t)"
# plot "metoda_rk2_1e-05.dat" u 1:2 w l lw 2 t 'tol=10^-^5', "metoda_rk2_0.01.dat" u 1:2 w l lw 2 t 'tol=10^-^2'

# set title "v(x)"
# plot "metoda_rk2_1e-05.dat" u 3:4 w l lw 2 t 'tol=10^-^5', "metoda_rk2_0.01.dat" u 3:4 w l lw 2 t 'tol=10^-^2'

# unset multiplot
