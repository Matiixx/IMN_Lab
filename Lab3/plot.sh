set term jpeg size 1920,480


set out "./trapezy.jpeg"
set multiplot layout 1,4

set title "v(t)"
plot "metoda_trapezow_1e-05.dat" u 1:4 w l lw 2 t 'tol=10^-^5', "metoda_trapezow_0.01.dat" u 1:4 w l lw 2 t 'tol=10^-^2'

set title "x(t)"
plot  "metoda_trapezow_1e-05.dat" u 1:3 w l lw 2 t 'tol=10^-^5', "metoda_trapezow_0.01.dat" u 1:3 w l lw 2 t 'tol=10^-^2'

set title "dt(t)"
plot "metoda_trapezow_1e-05.dat" u 1:2 w l lw 2 t 'tol=10^-^5', "metoda_trapezow_0.01.dat" u 1:2 w l lw 2 t 'tol=10^-^2'

set title "v(x)"
plot "metoda_trapezow_1e-05.dat" u 3:4 w l lw 2 t 'tol=10^-^5', "metoda_trapezow_0.01.dat" u 3:4 w l lw 2 t 'tol=10^-^2'

unset multiplot

set out "./rk2.jpeg"
set multiplot layout 1,4

set title "v(t)"
plot "metoda_rk2_1e-05.dat" u 1:4 w l lw 2 t 'tol=10^-^5', "metoda_rk2_0.01.dat" u 1:4 w l lw 2 t 'tol=10^-^2'

set title "x(t)"
plot  "metoda_rk2_1e-05.dat" u 1:3 w l lw 2 t 'tol=10^-^5', "metoda_rk2_0.01.dat" u 1:3 w l lw 2 t 'tol=10^-^2'

set title "dt(t)"
plot "metoda_rk2_1e-05.dat" u 1:2 w l lw 2 t 'tol=10^-^5', "metoda_rk2_0.01.dat" u 1:2 w l lw 2 t 'tol=10^-^2'

set title "v(x)"
plot "metoda_rk2_1e-05.dat" u 3:4 w l lw 2 t 'tol=10^-^5', "metoda_rk2_0.01.dat" u 3:4 w l lw 2 t 'tol=10^-^2'

unset multiplot