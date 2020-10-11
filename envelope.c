/*programmed by: Aubrey Birdwell
 * summer 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include "aubsynth.h"

//simple adsr
float *envelope(double timePoints[],
		double ampPoints[],
		int points,
		float *data,
		double duration,
		int srate,
		int nchan)
{
  
  int sampleFrames = (int)(duration * srate) ;
  int samples = sampleFrames * nchan ;
  
  float *ptrADSR, *p, *pd ;

  int incPts = points - 1;

  int tpts[points];
    
  pd = data;
  
  for (int i = 0; i < points; i++) {
    tpts[i] = (int)(timePoints[i] * samples);
  }
  
  //check the sum of stages matched total samples. 
  for (int i = 0; i < points; i++) {
    // printf("The sample number of stage %d is %d\n", i, tpts[i]);
  }
  
  float incr[incPts];

  for (int i = 0; i < incPts; i++) {
    incr[i] = (ampPoints[i+1]-ampPoints[i]) / (tpts[i+1] - tpts[i]);
  }

  //allocate a buffer
  p = ptrADSR = (float *)malloc(samples * sizeof(float));
  
  if ( ptrADSR == NULL ) {
    printf("Error! Memory not allocated.");
    exit(0);
  }

  
  //loop through the segments
  for (int i = 0; i < incPts; i++){
    //outer loop i is total points - 1 as per incPts
    //inner loop j is a large number in thousands scaled to samples
    for (int j = 0; j < (tpts[i+1] - tpts[i]); j++){
      *p++ = (*pd++ * (ampPoints[i] + (j * incr[i])));
    }
  }
  
  return ptrADSR;  
}
