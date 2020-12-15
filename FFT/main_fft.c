#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fft.h"

#define L 16

float TWOPI ;/* needed for rfft and cfft */
float PI ; /* needed for rfft and cfft */

int main() {

  float *x, *y, *z;

  //make a buffer
  x = (float *)malloc(L * sizeof(float));
  
  if ( x == NULL ) {
    printf("Error! Memory not allocated.");
    exit(0);
  }

    //make a buffer
  y = (float *)malloc(L * sizeof(float));
  
  if ( y == NULL ) {
    printf("Error! Memory not allocated.");
    exit(0);
  }
  
  //make a buffer
  z = (float *)malloc(L * sizeof(float));
  
  if ( z == NULL ) {
    printf("Error! Memory not allocated.");
    exit(0);
  }

  //float x[L], y[L], z[L] ;
    
  PI = 4.*atanf(1.) ;
  TWOPI = 8.*atanf(1.) ;

  int n ;
  for ( n = 0 ; n < L ; n++ )
    x[n] = y[n] = 1. + cosf( 8*n*TWOPI/L ) + cosf( 3*n*TWOPI/L ) ;

  rfft( y, L/2, 1 ) ;

  //test code for debugging
    /* for( n = 0; n<L ;n++) */
    /* { */
    /*   printf("y[%d] = %f\n", n, y[n]); */
    /* } */

    /* y[0] = 1.; */
    /* y[1] = 1.; */
    /* y[6] = 0.5; */
    
  for ( n = 0 ; n < L ; n++ )
    z[n] = y[n] ;
  
  rfft( z, L/2, 0 ) ;

  for( n = 0; n<L ;n++)
    {
      printf("y[%d] = %f\n", n, y[n]);
    }
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
