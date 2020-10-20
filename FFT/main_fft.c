#include <stdio.h>
#include <math.h>
#include "fft.h"

#define L 16

float TWOPI ;/* needed for rfft and cfft */
float PI ; /* needed for rfft and cfft */

int main() {
  float x[L], y[L], z[L] ;
  int n ;

  PI = 4.*atanf(1.) ;
  TWOPI = 8.*atanf(1.) ;

  for ( n = 0 ; n < L ; n++ )
    x[n] = y[n] = 1. + cosf( 8*n*TWOPI/L ) + cosf( 3*n*TWOPI/L ) ;
  rfft( y, L/2, 1 ) ;
  for ( n = 0 ; n < L ; n++ )
    z[n] = y[n] ;
  rfft( z, L/2, 0 ) ;

  printf( "%4s%9s%10s%10s%10s\n", "n ", "x(n)", "y(2n)", "y(2n+1)", "z(n)" ) ;

  for ( n = 0 ; n < L ; n++ )
    {
    if ( n < L/2 )
      {
      printf( "[%2d] %9f %9f %9f %9f\n", n, x[n], y[n<<1], y[(n<<1)+1], z[n] );
      }
    else
      {
      printf( "[%2d] %9f                     %9f\n", n, x[n], z[n]);
      }
    }

  return 0;
}
