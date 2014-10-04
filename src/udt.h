/* udt.h:
 *
 * Defines the time derivative. Breaks the domain up so that the
 * derivatives can be calculated in parallel.
 * 
 * Author: Adam M. Holmes
 */

#ifndef UDT_H
#define UDT_H


#include <omp.h>
#include "deriv.h"


/* Calculate du/dt value at x-point "index" */
double * udt(double *data, int length, double dx);


#endif
