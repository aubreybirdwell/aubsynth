/*programmed by: Aubrey Birdwell
 * summer 2020
 */

#include <stdio.h>
#include <stdlib.h>

#define MaxLinearAmp 32512 // +-2^15 or 32768 but I subtracted 256 to leave some headroom


//simple adsr
float *adsr(double timePoints[],
	    double ampPoints[],
	    float *data,
	    double duration,
	    int srate,
	    int nchan)
{
  
  int sampleFrames = (int)(duration * srate) ;
  int samples = sampleFrames * nchan ;
  float *ptrADSR, *p ;
  
  int t0,t1,t2,t3,t4;
  
  float aInc, dInc, sInc, rInc;
  
  //make start and end point in samples
  t0 = (int)(timePoints[0] * samples);
  t1 = (int)(timePoints[1] * samples);
  t2 = (int)(timePoints[2] * samples);
  t3 = (int)(timePoints[3] * samples);
  t4 = (int)(timePoints[4] * samples);
  
  //increments to scale the line segments
  aInc = (ampPoints[1]-ampPoints[0]) / (t1 - t0);
  dInc = (ampPoints[2]-ampPoints[1]) / (t2 - t1);
  sInc = (ampPoints[3]-ampPoints[2]) / (t3 - t2);
  rInc = (ampPoints[4]-ampPoints[3]) / (t4 - t3);
  
  //allocate a buffer
  p = ptrADSR = (float *)malloc(samples * sizeof(float));
  
  if ( ptrADSR == NULL ) {
    printf("Error! Memory not allocated.");
    exit(0);
  }

  // write onto the segments of the buffer
  // datasample * base_amp + (iter * seg_inc)  
  for (int i = 0 ; i < (t1 - t0); i++) {
    *p++ = (*(data + i) * (ampPoints[0] + (i * aInc)));
  }
  
  for (int i = 0 ; i < (t2 - t1); i++) {
    *p++ = (*(data + t1 + i) * (ampPoints[1] + (i * dInc)));
  }
  
  for (int i = 0 ; i < (t3 - t2); i++) {
    *p++ = (*(data + t2 + i) * (ampPoints[2] + (i * sInc)));
  }
  
  for (int i = 0 ; i < (t4 - t3); i++) {
    *p++ = (*(data + t3 + i) * (ampPoints[3] + (i * rInc)));
  }
  
  return ptrADSR;  
}
