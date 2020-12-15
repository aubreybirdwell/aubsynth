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

float *toRFFT(float *data,		
	     int window,
	     double duration,
	     int srate)
{
  
  PI = 4.*atanf(1.) ;
  TWOPI = 8.*atanf(1.) ;
  
  
  int sampleFrames = (int)(duration * srate) ;
  //printf("sampleFrames = %d", sampleFrames);
  //int samples = sampleFrames * nchan ;
  int sections = sampleFrames / window;
  //printf("sections = %d", sections);
  
  for ( int i = 0; i < sections; i += window) {
    //printf("the iterator is: %d", i);
    rfft( (data + i) , L/2, 1 ) ;
  }
  
  return data;
}
