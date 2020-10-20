#include <stdio.h>

#include <stdlib.h>
#include <math.h>
//#include "fft.h"

#define L 16

float TWOPI ;/* needed for rfft and cfft */
float PI ; /* needed for rfft and cfft */

int main() {

  float *px;

  px = (float *)malloc(L * sizeof(float));

  if (px == NULL) {
    printf("Error! Memory not allocated.");
    exit(0);
  }
  
  PI = 4.*(float)atan(1.) ;
  printf("Pi = %f\n", PI);
  
TWOPI = 8.*(float)atan(1.) ;
  printf("TwoPi = %f\n", TWOPI);

  printf("the value of %d is %d", L, (L<<1));
  
  for (int n = 0; n < L; n++)
    {
      //printf("%d\n", n);
      *(px + n) = 1. + (float)cos(8*n*TWOPI/L) + (float)cos(3*n*TWOPI/L);
      printf("value at %d is %f\n", n, *(px + n));
    }

  free(px);

  return 0;
}
