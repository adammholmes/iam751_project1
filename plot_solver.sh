#! /bin/bash
#
# Bash script to run and generate an animated video from 
# our KdV solver using gnuplot.
#
# Author: Adam M. Holmes

THREADS=4

# Run solver
echo "[1/5] Running solver with $THREADS thread(s)..."
OMP_NUM_THREADS=$THREADS ./KdV


# Transpose data because gnuplot is dumb
echo "[2/5] Transposing data file..."
awk '
{ 
  for (i=1; i<=NF; i++)  {
    a[NR,i] = $i
  }
}
NF>p { p = NF }
END {    
  for(j=1; j<=p; j++) {
    str=a[1,j]
    for(i=2; i<=NR; i++){
      str=str" "a[i,j];
    }
    print str
  }
}' DATA.txt > temp.txt


# Generate plots using gnuplot
echo "[3/5] Generating plots for each time iteration from solver data..."
LINES=$(( `cat DATA.txt | wc -l` - 1 ))
for i in `seq 1 $LINES`;
do
TIME=$(echo "$i * 0.005" | bc -l)
printf "Generating plot $i of $LINES\r"
gnuplot > /dev/null 2>&1 << EOF
set term png size 640,480
set output "$i.png"
set xrange [-10:10]
set yrange [0:10]
set nokey
set title "t = $TIME"
set grid x y
plot "temp.txt" using 1:$(($i + 1)) with line lt -1 lw 1 lc rgb "#0198E1"
EOF
done

# Join plots together in a video file
echo "[4/5] Generating a video file from plots..."
rm KdV.mp4 > /dev/null 2>&1
ffmpeg -r 30 -f image2 -i %d.png KdV.mp4 > /dev/null 2>&1


# Clean up
echo "[5/5] Cleaning up..."
rm DATA.txt > /dev/null 2>&1
rm temp.txt > /dev/null 2>&1
for i in `seq 1 $LINES`;
do
  rm $i.png
done
