/* muliplies two audio buffers of same length
 * Programmer: Aubrey Birdwell
 * When: Summer 2020
 * references: http://soundfile.sapp.org/doc/WaveFormat/
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "aubsynth.h"

//function to multiply two buffers with same length
float *multiplyBuffers(float *data,
		       float *data2,
		       double duration,
		       int srate,
		       int nchan)
{
  
  int sampleFrames = (int)(duration * srate) ;
  int samples = sampleFrames * nchan ;
  float *ptrMix, *pM, *d1, *d2 ;
  float currentdb;
  
  pM = ptrMix = (float *)malloc(samples * sizeof(float));
  d1 = data;
  d2 = data2;

  currentdb = (quickDecibels(d1, samples) + quickDecibels(d2, samples))/2 ;

  d1 = data;
  d2 = data2;
  
  if ( ptrMix == NULL ) {
    printf("Error! Memory not allocated.");
    exit(0);
  }
  
  for ( int i = 0; i < samples; i++) {
    *pM = *d1++ * *d2++;      
  }

  ptrMix = transformDecibels(pM, samples, currentdb);
  
  return ptrMix;
}
