IAM751_project1
---------------
A Korteweg–de Vries (KdV) equation solver written in C. The spacial derivative portions of the PDE are calculated in parallel using OpenMP (the domain is divided up in chunks). The resulting time ODE is solved using Runge-Kutta 4.

building
--------
```
autoreconf -i
./configure
make 
```

notes
-----
Use ***plot_solver.sh*** to run the program and generate an mp4 video from the results.

This program needs OpenMP to compile, and the plotting script needs gnuplot and ffmpeg to generate the plots and video.

A few different soliton examples:  
http://youtu.be/HxRmqa1ApOg  
http://youtu.be/wadUdob22RE  
