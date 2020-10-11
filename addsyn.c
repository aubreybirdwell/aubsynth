/* addsyn.c creates a list of natural overtone series
 * Aubrey Birdwell
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "aubsynth.h"

float *addsyn(float db,
	      float fund,
	      float ph,
	      int partials,
	      float flist,
	      float phlist,
	      float alist,
	      float dur,
	      int srate,
	      int nchan) {
  
  //return from addsyn.c and send back...
  float *output;
  
  //use 1.0 for calculation since the buffer is scaled to db at end
  float A = 1.0;
  
  //calculate samples
  int samples = dur * srate * nchan;
  
  //regular array ... gets destroyed after wave construction
  float flist[partials];
  float phlist[partials];
  float alist[partials];
  
  //construct partials list for freq and amplitude
  for (int i = 1; i < partials; i++)
    {
      flist[i] = flist[i-1] * fund
      
      //no need for phase ... or could it be interesting?
      phlist[i] = phlist[i-1];
      
      alist[i] = A * alist[i-1]; 
      
      printf("freq %d = %f\n", i, flist[i]);
      printf("amp %d = %f\n", i, alist[i]); 
      
    }
  
  //assign fundamental frequency to the first element of the list
  flist[0] = fund;
  phlist[0] = ph;
  alist[0] = A;
  
  output = addfreqs(flist, phlist, alist, partials, dur, srate, nchan);
  output = transformDecibels(output, samples, db); 
  
  return output;
  
}





#include <stdio.h>
#include <stdlib.h>
#include "aubsynth.h"


float *addsyn(float A,
	      float desiredPhase,
	      float fund,
	      float dur,
	      int srate,
	      int nchan,
	      int nPartials,
	      float flist[],
	      float alist[])
{
  
  float *output, *partial;
  
  output = sineWave(A, desiredPhase, fund, dur, srate, nchan);
  
  for(int i = 0; i < nPartials; i++) {
    partial = sineWave(alist[i], desiredPhase, (flist[i]*fund), dur, srate, nchan); 
    output = addBuffers(output, partial, dur, srate, nchan);
  }
  
  return output;
}
