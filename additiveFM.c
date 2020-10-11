#include <stdio.h>
#include <stdlib.h>
#include "aubsynth.h"


float *additiveFM(float flist[],
		float phlist[],
		float alist[],
	        int nPartials,
		float *mod,
		float mi,
		float dur,
		int srate,
		int nchan)
{
  
  float *output, *partial;
  
  output = sineFM(alist[0], phlist[0], flist[0], mod, mi, dur, srate, nchan);

  //start at [1] to skip fundamental...
  for(int i = 1; i < nPartials; i++) {
    partial = sineFM(alist[i], phlist[i], flist[i], mod, mi, dur, srate, nchan); 
    output = addBuffers(output, partial, dur, srate, nchan);
  }
  
  return output;
}
