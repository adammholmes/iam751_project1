/* udt.c:
 *
 * Defines the time derivative. Breaks the domain up so that the
 * derivatives can be calculated in parallel.
 *
 * Author: Adam M. Holmes
 */

#include "udt.h"

/* Calculate du/dt values on data */
double *
udt(double *data, int length, double dx)
{
  
  double *res = calloc(length, sizeof(double));
  assert(res);
  
  // Launch a thread for each chunk of the domain
  #pragma omp parallel shared(res)
  {
    int thread_id = omp_get_thread_num();
    int n_threads = omp_get_num_threads();
  
    // Calculate chunk size; create chunk, calculate domain offset of chunk
    int size = length / n_threads;
    int ideal_size = size;
    int offset = thread_id * ideal_size;
    if (thread_id == n_threads-1) {
      // Compensate for extra points on rightmost chunk
      int leftover = length % ((length / n_threads) * n_threads);
      size += leftover; 
    }
    
    int i; for(i = 0; i < size; i++) {
      double dudt = - dx3(data, offset+i, length, dx) - 
        (6 * data[offset+i] * dx1(data, offset+i, length, dx));
      res[offset+i] = dudt;
    }
    
  }
    
  return res;
}
