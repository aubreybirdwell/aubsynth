#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fft.h"

extern float TWOPI ;

/*
 *bit reverse places float array x containing N/2 complex values 
 *into bit-reversed order
 */

void bitreverse(float *x, int N) {
  float rtemp, itemp, *px;
  int i, j, m ;
  px = x;
  
  for ( i = j = 0 ; i < N ; i += 2, j += m ) {
    if ( j > i ) {
      rtemp = *(px+j) ; itemp = *(px+(j+1)) ; /* complex exchange */
      *(px+j) = *(px+1) ; *(px+(j+1)) = *(px+(i+1)) ;
      *(px+i) = rtemp ; *(px+(i+1)) = itemp ;
    }
    for ( m = N>>1 ; m >= 2 && j >= m ; m >>= 1 )
      j -= m ;
  }
}

/*
 *cfft replaces float array x containing NC complex values 
 *(2*NC float values alternating real, imaginary, and so on)
 *by its Fourier transform if forward is true, or by its 
 *invers fourier transform if the forward is false. NC must be
 *a power of 2! Based on program FOUR1 in Numerical Recipes:
 *The Art of Scientific Computing (Cambridge University Press,
 *1986), copywrite 1986 by Numerical Recipes Software. Used
 *by permission (for Elements of Computer Music by Richard
 * Moore)
 *
 */


void cfft(float *x, int  NC, int  forward) {
   
  //float TWOPI = 8.*atan(1.) ;

  float *px, *p2x;
  px = x;
  p2x = x;
  
  float wr, wi, wpr, wpi, theta, scale ;
  int mmax, ND, m, i, j, delta ;
  
  ND = NC<<1 ;
  bitreverse( p2x, ND ) ;
  
  for ( mmax = 2 ; mmax < ND ; mmax = delta ) {
    delta = mmax<<1 ;
    theta = TWOPI/( forward ? mmax : -mmax ) ;
    wpr = -2.*pow( sin( 0.5*theta ), 2. ) ;
    wpi = sin( theta ) ;
    wr = 1. ;
    wi = 0. ;
    
    for ( m = 0 ; m < mmax ; m += 2 ) {
      
      register float rtemp, itemp ;
      
      for ( i = m ; i < ND ; i += delta ) {
	j = i + mmax ;
	rtemp = wr*(*(x+j)) - wi*(*(px+(j+1))) ;
	itemp = wr*(*(px+(j+1))) + wi*(*(px+j)) ;
	*(px+j) = *(px+i) - rtemp ;
	*(px+(j+1)) = *(px+(i+1)) - itemp ;
	*(px+i) += rtemp ;
	*(px+(i+1)) += itemp ;
      }
      
      wr = (rtemp = wr)*wpr - wi*wpi + wr ;
      wi = wi*wpr + rtemp*wpi + wi ;
    }
  }
  /*
   * scale output
   */

  scale = forward ? 1./ND : 2. ;
  for ( i = 0 ; i < ND ; i++ )
    *(px+i) *= scale ;
  {register float *xi=px, *xe=(px+ND) ;
    while (xi < xe)
      *xi++ *= scale;
  }

}
