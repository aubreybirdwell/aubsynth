#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "aubsynth.h"

float *ampMod(float *cf,
	      float *mf,
	      float db,
	      float dur,
	      int srate,
	      int nchan)
{
  float *ptrData, *pd, *pdB;

  //calculate samples
  int samples = dur * srate * nchan;
 
  ptrData = (float *)malloc(samples * sizeof(float));
  pd = ptrData;
  pdB = ptrData;
  
  while ( samples-- )
    {
      *pd++ = ((1 + *mf++) * *cf++);
    }

 pdB = transformDecibels(pdB, samples, db);  
   
 return ptrData;
}
