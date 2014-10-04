/* u.c:
 *
 * Numerically integrate a 1-d Korteweg-de-Vries PDE using RK4 and 
 * Finite Difference derivative approximations.
 *
 * This program writes results to a space delimited data file. The 
 * first row comtains x points. Subsequent rows contain the y values
 * for each corresponding time step.
 * 
 * Author: Adam M. Holmes
 *
 * http://youtu.be/HxRmqa1ApOg
 * http://youtu.be/wadUdob22RE
 */

#include "rk4.h"
#include <math.h>

#define TIMESTEPS 150000
#define XSTART -10
#define SSTART 0
#define RANGE 20
#define DELTAX 0.1
#define DELTAT 0.00001
#define LINESKIPMOD 500


/* Generate a soliton solution at any point in time */
double
solution(double x, double t)
{
  /*
  double sech = 1 / cosh((x - (t)) / 2);
  return (1.0f/2.0f) * (sech * sech);
  */
  
  double sech1 = 1 / cosh(2 * (x + 8));
  double sech2 = 1 / cosh(x );
  return (8 * sech1 * sech1) + (2 * sech2 * sech2);
  
}


/* Simulate 1-d KdV equation */
int
main(int argc, char **argv)
{ 
  double dx = DELTAX;
  if (argc > 1) {
    dx = atof(argv[1]);
  }
  double dt = DELTAT;
  int length = (RANGE / (dx)) + 2;
  
  // Create x vector and populate values
  double *x = malloc(sizeof(double) * length); 
  assert(x);
  int i; for (i = 0; i < length; i++) {
    x[i] = XSTART + (i * dx);
  }
  
  // Create y vector and populate values using some solution equations
  double *y = malloc(sizeof(double) * length); 
  assert(y);
  for (i = 0; i < length; i++) {
    y[i] = solution(x[i], SSTART);
  }
  
  // Open file for writing
  FILE *f = fopen("DATA.txt", "w");
  assert(f);
  
  // Write x points and initial y points to file
  for (i = 0; i < length; i++) {
    fprintf(f, "%.8f ", x[i]);
  }
  fprintf(f, "\n");
  for (i = 0; i < length; i++) {
    fprintf(f, "%.16f ", y[i]);
  }
  fprintf(f, "\n");
  
  // Step through time
  double *y_cpy = malloc(sizeof(double) * length);
  assert(y_cpy);
  int t; for (t = 0; t < TIMESTEPS; t++) {
    
    memcpy(y_cpy, y, sizeof(double) * length);
    
    // Find change in y for each x
    double *diff = rk4(y, length, dx, dt);
    
    // Apply change to complete iteration
    for (i = 0; i < length; i++) {
      y[i] = y_cpy[i] + diff[i];
    }
    
    // Write results to data file
    if (t % LINESKIPMOD == 0) {
      for (i = 0; i < length; i++) {
        fprintf(f, "%.16f ", y[i]);
      }
      fprintf(f, "\n");
    }

  }
  
  // Close data file
  fclose(f);
  
  // Free used memory
  free(x);
  free(y);
  
  return 0;
}
