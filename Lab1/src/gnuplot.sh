set term jpeg

set xlabel "Kolejne iteracje" 
set ylabel "Wartosci" 

set title "Metoda jawna Eulera"
set out "euler.jpeg"
plot "euler.csv" t 'dt = 0.01s'