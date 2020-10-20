#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fft.h"

#define L 16

float TWOPI ;/* needed for rfft and cfft */
float PI ; /* needed for rfft and cfft */

int main() {

  float *x, *y, *z;
  
  x = (float *)malloc(L * sizeof(float));
  y = (float *)malloc(L * sizeof(float));
  z = (float *)malloc(L * sizeof(float));

  if ((x == NULL) || (y == NULL) || (z == NULL)) {
    printf("Error! Memory not allocated.");
    exit(0);
  }

  float *px, *py, *p2y, *pz, *p2z;
  px = x;
  py = y;
  p2y = y;
  
  pz = z;
  p2z = z;

  
  
  //allocate these three instead
  //float x[L], y[L], z[L] ;

  int n ;

  PI = 4.*atanf(1.) ;
  TWOPI = 8.*atanf(1.) ;

  for ( n = 0 ; n < L ; n++ )
    {
      *(px+n) = 1. + cosf( 8*n*TWOPI/L ) + cosf( 3*n*TWOPI/L ) ;
      *(py+n) = *(px+n);
    }
 
  rfft( p2y, L/2, 1 );
  
  for ( n = 0 ; n < L ; n++ )
    *(pz+n) = *(py+n) ;

  rfft( p2z, L/2, 0 );

  printf( "%4s%9s%10s%10s%10s\n", "n ", "x(n)", "y(2n)", "y(2n+1)", "z(n)" ) ;

  for ( n = 0 ; n < L ; n++ )
    {
    if ( n < L/2 )
      {
	printf( "[%2d] %9f %9f %9f %9f\n", n, *(px+n), *(py+(n<<1)), *(py+((n<<1)+1)), *(pz+n) );
      }
    else
      {
	printf( "[%2d] %9f                     %9f\n", n, *(px+n), *(pz+n));
      }
    }

  free(x);
  free(y);
  free(z);
  
  return 0;
}
