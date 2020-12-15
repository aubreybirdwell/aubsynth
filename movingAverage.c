/* average two buffers of the same size
 * Programmer: Aubrey Birdwell
 * When: fall 2020
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float *movingAverage(float *data,
		     double duration,
		     int srate,
		     int nchan)
{
  
  int sampleFrames = (int)(duration * srate) ;
  int samples = sampleFrames * nchan ;
  
  float *p, *p2;
  
  p = p2 = data;
  
  //pM = ptrMix = (float *)malloc(samples * sizeof(float));
  
  /* if ( ptrMix == NULL ) { */
  /*   printf("Error! Memory not allocated."); */
  /*   exit(0); */
  /* } */
  
  for ( int i = 0; i < samples; i++) {
    
    if(i == (samples-1))
      *p++ = (*(p2) + *(p2 + i))/2;
    
    *p++ = (*(p2 + i + 1) + *(p2 + i))/2;  
    
  }
  
  return data;
}
