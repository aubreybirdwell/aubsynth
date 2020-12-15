/* combine two buffers into a stereo buffer
 * Programmer: Aubrey Birdwell
 * When: fall 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float *addBuffers(float *data,
		  float *data2,
		  double duration,
		  int srate,
		  int nchan)
{
  
  int sampleFrames = (int)(duration * srate) ;
  int samples = sampleFrames * nchan ;
  float *ptrMix, *pM, *d1, *d2;

  d1 = data;
  d2 = data2;
   
  pM = ptrMix = (float *)malloc(samples * sizeof(float));
  
  if ( ptrMix == NULL ) {
    printf("Error! Memory not allocated.");
    exit(0);
  }
  
  for ( int i = 0; i < samples; i++) {
    *pM++ = *d1++ + *d2++;      
  }
  
  return ptrStereo;
}
