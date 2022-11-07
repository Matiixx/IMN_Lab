set term jpeg size 1080,1920

set xlabel "t"
set yrange [0:500]

set out "./res.jpeg"
set multiplot layout 3,1

set title "Metoda Picarda"
plot "picard.dat" u 1:2 w l lw 2 t 'u(t)', "picard.dat" u 1:3 w l lw 2 t 'z(t)=N-u(t)'

set title "Metoda Newtona"
plot "newton.dat" u 1:2 w l lw 2 t 'u(t)', "newton.dat" u 1:3 w l lw 2 t 'z(t)=N-u(t)'

set title "Niejawna metoda RK2"
plot "rk2.dat" u 1:2 w l lw 2 t 'u(t)', "rk2.dat" u 1:3 w l lw 2 t 'z(t)=N-u(t)'

unset multiplot