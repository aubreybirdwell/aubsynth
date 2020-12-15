/* combine two buffers into a stereo buffer
 * Programmer: Aubrey Birdwell
 * When: fall 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fft.h"

float TWOPI ;/* needed for rfft and cfft */
float PI ; /* needed for rfft and cfft */

#define L 16

float *toCFFT(float *data,		
	       int window,
	       double duration,
	       int srate)
{
  
  PI = 4.*atanf(1.) ;
  TWOPI = 8.*atanf(1.) ;
  
  
  int sampleFrames = (int)(duration * srate) ;
  //int samples = sampleFrames * nchan ;
  int sections = sampleFrames / window;
  
  for ( int i = 0; i < sections; i += window) {            
    cfft( (data + i) , L/2, 0 ) ;
  }
  
  return data;
}
