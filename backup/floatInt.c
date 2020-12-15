/* takes a Float buffer of specified length and returns a short buffer
 * Programmer: Aubrey Birdwell
 * When: Summer 2020
 * references: http://soundfile.sapp.org/doc/WaveFormat/
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BITS 16
#define MaxLinearAmp 32512 // +-2^15 or 32768 subtract 3 dB instead of 256 <----- todo

short *floatInt(float *data,
		double duration,
		int srate,
		int nchan)
{
  
  int sampleFrames = (int)(duration * srate) ;
  int samples = sampleFrames * nchan ;
  
  float *pd;
  short *ptrShort, *p;
  
  pd = data;
  
  p = ptrShort = (short *)malloc(samples * sizeof(short));
  
  if ( ptrShort == NULL ) {
    printf("Error! Memory not allocated.");
    exit(0);
  }
 
  for ( int i = 0; i < samples; i++) {
    *p++ = (int)(*pd++ * MaxLinearAmp);
  }
  
  return ptrShort;
}

