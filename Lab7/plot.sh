#set term postscript size 20cm, 40cm color enhanced solid font "Helvetica, 10"

#
#
#   plik z danymi: x, y, psi(x,y), ksi(x,y), u(x,y), v(x,y)
#
#

reset
set term png size 1600, 2400 enhanced # font "Helvetica, 18" lw 2
#set size 1,1
#set size square

set lmargin  1.5
set bmargin  7.5
set rmargin  1.5
set tmargin  7.0


set out "maps.png"
set grid
set multiplot layout 5,2

set grid
unset grid
set object 1 rect from 0,0 to 0.5,0.55 fs solid noborder fc rgb "black" front # przeszkoda


###########################################################

#set pm3d
#set surface
unset surface
set view map
#set palette defined (-2 "blue", 0 "white", 16 "red")
set size ratio -1

###########################################################
set title 'Funkcja strumienia Psi(x,y) Q=-1000'
set xlabel 'x'
set ylabel 'y'
#unset key
unset ztics
set palette rgbformulae 33,13,10 # paleta kolorow
set contour base
# set cntrparam level 300
set cntrparam levels increment -55,0.1,-50
#unset surface
#set view equal
#set view 0,0

splot [0:2][0:0.9][-54.5:-50.5] "wyn.dat" u 1:2:3 w l palette notitle
###########################################################
set title 'Funkcja wirowosci ksi(x,y) Q=-1000'
set xlabel 'x'
set ylabel 'y'
set cntrparam levels increment -200,20,350

splot [0:2][0:0.9][-200:350] "wyn.dat" u 1:2:4 w l palette notitle
###########################################################
unset pm3d
set pm3d
unset surface
unset contour
#unset cntrparam level
#set palette defined (-2 "blue", 0 "white", 16 "red")
set title 'Pozioma skladowa predkosci u(x,y) Q=-1000'
set xlabel 'x'
set ylabel 'y'

splot [0:2][0:0.9][-2:16] "wyn.dat" u 1:2:5 notitle
#splot "wyn.dat" u 1:2:5 notitle
###########################################################
#set palette defined (-6 "blue", 0 "white", 1 "red")
set title 'Pionowa skladowa predkosci v(x,y) Q=-1000'
set xlabel 'x'
set ylabel 'y'

splot [0:2][0:0.9][-6:1] "wyn.dat" u 1:2:6 notitle


###########################################################

unset pm3d
set surface
unset surface
#set palette rgbformulae 33,13,10 # paleta kolorow
set view map
#set palette defined (-2 "blue", 0 "white", 16 "red")
set size ratio -1

###########################################################
set title 'Funkcja strumienia Psi(x,y) Q=-4000'
set xlabel 'x'
set ylabel 'y'
#unset key
unset ztics
set contour base
# set cntrparam level 500
set cntrparam levels increment -218,0.5,-202
#unset surface
#set view equal
#set view 0,0

splot [0:2][0:0.9][-218:-202] "wyn_Qm4000.dat" u 1:2:3 w l palette notitle
###########################################################
set title 'Funkcja wirowosci ksi(x,y) Q=-4000'
set xlabel 'x'
set ylabel 'y'
set cntrparam levels increment -800,40,1200

splot [0:2][0:0.9][-800:1200] "wyn_Qm4000.dat" u 1:2:4 w l palette notitle
###########################################################
unset pm3d
set pm3d
unset surface
unset contour
#unset cntrparam level
#set palette defined (-10 "blue", 0 "white", 70 "red")

set title 'Pozioma skladowa predkosci u(x,y) Q=-4000'
set xlabel 'x'
set ylabel 'y'

splot [0:2][0:0.9][-10:70] "wyn_Qm4000.dat" u 1:2:5 notitle
###########################################################
#set palette defined (-14 "blue", 0 "white", 4 "red")
set title 'Pionowa skladowa predkosci v(x,y) Q=-4000'
set xlabel 'x'
set ylabel 'y'

splot [0:2][0:0.9][-14:4] "wyn_Qm4000.dat" u 1:2:6 notitle


###########################################################
unset pm3d
#set palette rgbformulae 33,13,10 # paleta kolorow

set title 'Funkcja strumienia Psi(x,y) Q=4000'
set xlabel 'x'
set ylabel 'y'
#unset key
unset ztics
set contour base
# set cntrparam level 500
set cntrparam levels increment 202,0.5,218
#unset surface
#set view equal
#set view 0,0

splot [0:2][0:0.9][202:218] "wyn_Q4000.dat" u 1:2:3 w l palette notitle
##############################################################
#set title 'Funkcja wirowosci ksi(x,y) Q=4000'################
#set xlabel 'x'
#set ylabel 'y'

#splot [0:2][0:0.9] "wyn_Q4000.dat" u 1:2:4 w l palette notitle


unset multiplot
reset

