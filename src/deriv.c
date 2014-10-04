/* deriv.c:
 *
 * Provides derivative approximating functions. Uses centered 
 * difference formulas dervied from Taylor Series.
 *
 * If index is on either ends for any of the derivative 
 * approximations, they will wrap around.
 *
 * Author: Adam M. Holmes
 */

#include "deriv.h"

/* First derivative of data at given point */
double
dx1(double *data, int index, int length, double dx)
{
  if (index == 0) {
    return (data[index+1] - data[length-1]) / (2 * dx);
  } else if (index == length-1) {
    return (data[0] - data[index-1]) / (2 * dx);
  } else {
    return (data[index+1] - data[index-1]) / (2 * dx);
  }
}


/* Second derivative of data at given point */
double
dx2(double *data, int index, int length, double dx)
{
  if (index == 0 || index == length) {
    return (data[1] - 2*data[0] + data[length-1]) / (dx * dx);
  } else if (index == length-1 || index == -1) {
    return (data[0] - 2*data[length-1] + data[length-2]) / (dx * dx);
  } else {
    return (data[index+1] - 2*data[index] + data[index-1]) / (dx * dx);
  }
}


/* Third derivative of data at given point */
double
dx3(double *data, int index, int length, double dx)
{
  double before = dx2(data, index-1, length, dx);
  double after = dx2(data, index+1, length, dx);
  
  return (after - before) / (2 * dx);
}
