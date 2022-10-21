set term jpeg

set xlabel "t" 
set ylabel "Wartosci" 

set title "Metoda jawna Eulera"
set out "../euler.jpeg"
plot "euler0.01.csv" u 1:2 w l lw 1 t 'dt = 0.01s', "euler0.10.csv" u 1:2 w l lw 1 t 'dt = 0.1s', "euler1.00.csv" u 1:2 w l lw 5 t 'dt = 1.0s', "euler_analytic.csv" u 1:2 w l lw 2 t "analytic"

set title "Metoda jawna Eulera - blad"
set out "../euler_diff.jpeg"
plot "euler0.01_diff.csv" u 1:2 w l lw 1 t 'dt = 0.01s', "euler0.10_diff.csv" u 1:2 w l lw 1 t 'dt = 0.1s', "euler1.00_diff.csv" u 1:2 w l lw 1 t 'dt = 1.0s'

set title "Metoda jawna RK2"
set out "../rk2.jpeg"
plot "rk20.01.csv" u 1:2 w l lw 1 t 'dt = 0.01s', "rk20.10.csv" u 1:2 w l lw 1 t 'dt = 0.1s', "rk21.00.csv" u 1:2 w l lw 1 t 'dt = 1.0s', "rk2_analytic.csv" u 1:2 w l lw 2 t 'analytic'

set title "Metoda jawna RK2 - blad"
set out "../rk2_diff.jpeg"
plot "rk20.01_diff.csv" u 1:2 w l lw 1 t 'dt = 0.01s', "rk20.10_diff.csv" u 1:2 w l lw 1 t 'dt = 0.1s', "rk21.00_diff.csv" u 1:2 w l lw 1 t 'dt = 1.0s'
