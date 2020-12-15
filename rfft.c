#include <stdio.h>
#include <math.h>
#include "fft.h"

extern float PI ;

/*
 * If forward is true, rfft replaces 2*N real data points in x
 * with N complex values representing the positive frequency half
 * of theri Fourier spectrum, with x[1] replaced with the real 
 * part of the Nyquist frequency value. If forward is false, rfft
 * expects x to contain a * positive frequency spectrum arranged 
 * as before, and replaces it with 2*N real values. N must be a 
 * power of 2. Based on program REALFT in Numerical Recipes: The
 * Art of Scientific Computing (Cambridge University Press, 1986),
 * copywrite 1986 by Numerical Recipes Software. Used by 
 * Permission. 
 */

void rfft(float x[], int  N, int forward ) {

  //float PI = 4.*atan(1.) ;

  float c1, c2, h1r, h1i, h2r, h2i, wr, wi, wpr, wpi, temp, theta ;
  float xr, xi ;
  int i, i1, i2, i3, i4, N2p1 ;
  theta = PI/N ;
  wr = 1. ;
  wi = 0. ;
  c1 = 0.5 ;
  if ( forward == 1 ) {
    c2 = -0.5 ;
    cfft( x, N, forward ) ;
    xr = x[0] ;
    xi = x[1] ;
  } else {
    c2 = 0.5 ;
    theta = -theta ;
    xr = x[1] ;
    xi = 0. ;
    x[1] = 0. ;
  }
  wpr = -2.*pow( sinf( 0.5*theta ), 2. ) ;
  wpi = sinf( theta ) ;
  N2p1 = (N<<1) + 1 ;
  for ( i = 0 ; i <= N>>1 ; i++ ) {
    i1 = i<<1 ;
    i2 = i1 + 1 ;
    i3 = N2p1 - i2 ;
    i4 = i3 + 1 ;
    if ( i == 0 ) {
      h1r =  c1*(x[i1] + xr ) ;
      h1i =  c1*(x[i2] - xi ) ;
      h2r = -c2*(x[i2] + xi ) ;
      h2i =  c2*(x[i1] - xr ) ;
      x[i1] = h1r + wr*h2r - wi*h2i ;
      x[i2] = h1i + wr*h2i + wi*h2r ;
      xr =  h1r - wr*h2r + wi*h2i ;
      xi = -h1i + wr*h2i + wi*h2r ; 
    } else {
      h1r =  c1*(x[i1] + x[i3] ) ;
      h1i =  c1*(x[i2] - x[i4] ) ;
      h2r = -c2*(x[i2] + x[i4] ) ;
      h2i =  c2*(x[i1] - x[i3] ) ;
      x[i1] = h1r + wr*h2r - wi*h2i ;
      x[i2] = h1i + wr*h2i + wi*h2r ;
      x[i3] = h1r - wr*h2r + wi*h2i ;
      x[i4] = -h1i + wr*h2i + wi*h2r ;
    }
    wr = (temp = wr)*wpr - wi*wpi + wr ;
    wi = wi*wpr + temp*wpi + wi ;
  }
  if ( forward == 1 )
    x[1] = xr ;
  else
    cfft( x, N, forward) ;
}
