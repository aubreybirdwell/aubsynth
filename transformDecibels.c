
/* apply db to short buffer
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "aubsynth.h"

#define a0 (pow(10, -5))

float *transformDecibels(float *data, int samples, float desiredDecibels)
{

  float *out, *outdata; //output pointers
  float *ptrdata, *pd; //current datablock pointers
  float currentA, desiredA, scale; //

  ptrdata = pd = data;

  outdata = (float *)malloc(samples * sizeof(float)) ;

  if ( ptrdata == NULL ) {
    printf("Error! Memory not allocated.");
    exit(0);
  }
  
  out = outdata;
  
  //formula to calculate linear amps 
  //db = pow(10.0, db/20) / 2 ; 

  /* Possibly clean up this next block once it is dialed in
   *
   *
   */

  //get the amplitude in db
  currentA = quickDecibels(ptrdata, samples);
  
  // find peak linear Amps and multiplier ratio ... fyi the following two lines convert back to linear 
  desiredA = pow(10.0, desiredDecibels/20);
  //printf("desiredA = %f\n", desiredA);

  currentA = pow(10.0, (currentA/20));
  //printf("currentA = %f\n", currentA);  

  scale = desiredA / currentA;
  
  for ( int i = 0; i < samples; i++) {
    *out++ = (*pd++ * scale);
  }

  return outdata ;
}


