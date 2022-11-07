set term jpeg

set xlabel "t"
set yrange [0:500]

set title "Metoda Picarda"
set out "picard.jpeg"
plot "picard.dat" u 1:2 w l lw 2 t 'u(t)', "picard.dat" u 1:3 w l lw 2 t 'z(t)=N-u(t)'

set title "Metoda Newtona"
set out "newton.jpeg"
plot "newton.dat" u 1:2 w l lw 2 t 'u(t)', "newton.dat" u 1:3 w l lw 2 t 'z(t)=N-u(t)'

set title "Niejawna metoda RK2"
set out "rk2.jpeg"
plot "rk2.dat" u 1:2 w l lw 2 t 'u(t)', "rk2.dat" u 1:3 w l lw 2 t 'z(t)=N-u(t)'
