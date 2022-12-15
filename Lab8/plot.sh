# #set term postscript size 20cm, 40cm color enhanced solid font "Helvetica, 10"

# #
# #
# #   plik z danymi: x, y, psi(x,y), ksi(x,y), u(x,y), v(x,y)
# #
# #

# reset
set term png size 3200, 4800 
# set size 1,1
# #set size square

# set lmargin  1.5
# set bmargin  7.5
# set rmargin  1.5
# set tmargin  7.0


set out "res.png"
set grid
set multiplot layout 5,2

# set grid
# unset grid
# set object 1 rect from 0,0 to 0.5,0.55 fs solid noborder fc rgb "black" front # przeszkoda


# ###########################################################

set pm3d
# #set surface
set view map
unset surface
# #set palette defined (-2 "blue", 0 "white", 16 "red")
# set size ratio -1

# ###########################################################
set title 'Mapa predkosci v_x'
set xlabel 'x'
set ylabel 'y'

set palette rgbformulae 33,13,10 # paleta kolorow

splot [0:4][0:0.9][-5:45] "v.dat" u 1:2:3 w p pt 5 ps 8 palette notitle
# ###########################################################
set title 'Mapa predkosci v_y'
set xlabel 'x'
set ylabel 'y'

splot [0:4][0:0.9][-20:30] "v.dat" u 1:2:4 w p pt 5 ps 8 palette notitle
# ###########################################################
unset pm3d
set title 'calka gestosci c(t)'
set xlabel 't'
set ylabel 'c(t)'

set yrange [0.5:1.05]

plot "c_xsr_0.dat" u 1:2 w l lw 2 t "D=0.0", "c_xsr_0.1.dat" u 1:2 w l lw 2 t "D=0.1"
# ###########################################################
unset pm3d
set title 'srednie polozenie x(t)'
set xlabel 't'
set ylabel 'x(t)'

set yrange [0:4]

plot "c_xsr_0.dat" u 1:3 w l lw 2 t "D=0.0", "c_xsr_0.1.dat" u 1:3 w l lw 2 t "D=0.1"
# ###########################################################
set pm3d
set view map
unset surface

set title 'D=0 u(x,y) it=2000, t=0.113947'
set xlabel 'x'
set ylabel 'y'

set palette rgbformulae 33,13,10 # paleta kolorow

splot [0:400][0:90][0:18] "map_u_2000_0.dat" u 1:2:3 w p pt 5 ps 8 palette notitle
# ###########################################################
set title 'D=0.1 u(x,y) it=2000, t=0.113947'
set xlabel 'x'
set ylabel 'y'

set palette rgbformulae 33,13,10 # paleta kolorow

splot [0:400][0:90][0:4] "map_u_2000_0.1.dat" u 1:2:3 w p pt 5 ps 8 palette notitle
# ###########################################################
# set title 'Funkcja strumienia Psi(x,y) Q=-4000'
# set xlabel 'x'
# set ylabel 'y'
# #unset key
# unset ztics
# set contour base
# # set cntrparam level 500
# set cntrparam levels increment -218,0.5,-202
# #unset surface
# #set view equal
# #set view 0,0

# splot [0:2][0:0.9][-218:-202] "wyn_Qm4000.dat" u 1:2:3 w l palette notitle
# ###########################################################
# set title 'Funkcja wirowosci ksi(x,y) Q=-4000'
# set xlabel 'x'
# set ylabel 'y'
# set cntrparam levels increment -800,40,1200

# splot [0:2][0:0.9][-800:1200] "wyn_Qm4000.dat" u 1:2:4 w l palette notitle
# ###########################################################
# unset pm3d
# set pm3d
# unset surface
# unset contour
# #unset cntrparam level
# #set palette defined (-10 "blue", 0 "white", 70 "red")

# set title 'Pozioma skladowa predkosci u(x,y) Q=-4000'
# set xlabel 'x'
# set ylabel 'y'

# splot [0:2][0:0.9][-10:70] "wyn_Qm4000.dat" u 1:2:5 notitle
# ###########################################################
# #set palette defined (-14 "blue", 0 "white", 4 "red")
# set title 'Pionowa skladowa predkosci v(x,y) Q=-4000'
# set xlabel 'x'
# set ylabel 'y'

# splot [0:2][0:0.9][-14:4] "wyn_Qm4000.dat" u 1:2:6 notitle


# ###########################################################
# unset pm3d
# #set palette rgbformulae 33,13,10 # paleta kolorow

# set title 'Funkcja strumienia Psi(x,y) Q=4000'
# set xlabel 'x'
# set ylabel 'y'
# #unset key
# unset ztics
# set contour base
# # set cntrparam level 500
# set cntrparam levels increment 202,0.5,218
# #unset surface
# #set view equal
# #set view 0,0

# splot [0:2][0:0.9][202:218] "wyn_Q4000.dat" u 1:2:3 w l palette notitle
# ##############################################################
# #set title 'Funkcja wirowosci ksi(x,y) Q=4000'################
# #set xlabel 'x'
# #set ylabel 'y'

# #splot [0:2][0:0.9] "wyn_Q4000.dat" u 1:2:4 w l palette notitle


unset multiplot
# reset

