/* rk4.c:
 *
 * Runge-Kutta 4 implementation for KdV solver.
 *
 * Author: Adam M. Holmes
 */

#include "rk4.h"


/* Solve time ODE using Runge-Kutta 4 */
double *
rk4(double *data, int length, double dx, double dt)
{
  // Find k1
  double *k1 = udt(data, length, dx);
  
  // Find k2
  double *data_cpy = malloc(sizeof(double) * length);
  assert(data_cpy);
  memcpy(data_cpy, data, sizeof(double) * length);
  int i; for (i = 0; i < length; i++) {
    data_cpy[i] += (dt / 2) * k1[i];
  }
  double *k2 = udt(data_cpy, length, dx);
  
  // Find k3
  memcpy(data_cpy, data, sizeof(double) * length);
  for (i = 0; i < length; i++) {
    data_cpy[i] += (dt / 2) * k2[i];
  }
  double *k3 = udt(data_cpy, length, dx);
  
  // Find k4
  memcpy(data_cpy, data, sizeof(double) * length);
  for (i = 0; i < length; i++) {
    data_cpy[i] += dt * k3[i];
  }
  double *k4 = udt(data_cpy, length, dx);
  
  // Combine results
  double *res = calloc(length, sizeof(double));
  assert(res);
  for (i = 0; i < length; i++) {
    res[i] = (dt / 6) * (k1[i] + (2*k2[i]) + (2*k3[i]) + k4[i]);
  }

  free(data_cpy);
  free(k1); free(k2); free(k3); free(k4);
  
  return res;
}
