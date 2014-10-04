/* rk4.h:
 *
 * Runge-Kutta 4 implementation for KdV solver.
 *
 * Author: Adam M. Holmes
 */

#ifndef RK4_H
#define RK4_H


#include <string.h>
#include "udt.h"


/* Solve time ODE using Runge-Kutta 4 */
double * rk4(double *data, int length, double dx, double dt);


#endif
