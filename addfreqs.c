#include <stdio.h>
#include <stdlib.h>
#include "aubsynth.h"


float *addfreqs(float flist[],
		float phlist[],
		float alist[],
	        int nPartials,
		float dur,
		int srate,
		int nchan)
{
  
  float *output, *partial;
  
  output = sineWave(alist[0], phlist[0], flist[0], dur, srate, nchan);

  //start at [1] to skip fundamental...
  for(int i = 1; i < nPartials; i++) {
    partial = sineWave(alist[i], phlist[i], flist[i], dur, srate, nchan); 
    output = addBuffers(output, partial, dur, srate, nchan);
  }
  
  return output;
}
