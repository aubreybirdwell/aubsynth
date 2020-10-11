/* takes an int buffer of specified length and returns a float buffer
 * Programmer: Aubrey Birdwell
 * When: Summer 2020
 * references: http://soundfile.sapp.org/doc/WaveFormat/
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BITS 16
#define MaxLinearAmp 32768 // +-2^15 or 32768 subtract 3 db

short *intFloat(short *data,
		double duration,
		int srate,
		int nchan)
{
  
  int sampleFrames = (int)(duration * srate) ;
  int samples = sampleFrames * nchan ;
  
  short *pd;
  float *ptrFloat, *pf;
  
  pd = data;
  
  pf = ptrFloat = (float *)malloc(samples * sizeof(float));
  
  if ( ptrFloat == NULL ) {
    printf("Error! Memory not allocated.");
    exit(0);
  }
 
  for ( int i = 0; i < samples; i++) {
    *pf++ = (float)(*pd++ / MaxLinearAmp);
  }
  
  return ptrFloat;
}

