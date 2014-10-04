/* deriv.h:
 *
 * Provides derivative approximating functions. Uses centered 
 * difference formulas dervied from Taylor Series.
 *
 * Author: Adam M. Holmes
 */

#ifndef DERIV_H
#define DERIV_H


#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>


/* First derivative of data at given point */
double dx1(double *data, int index, int length, double dx);

/* Second derivative of data at given point */
double dx2(double *data, int index, int length, double dx);

/* Third derivative of data at given point */
double dx3(double *data, int index, int length, double dx);


#endif
