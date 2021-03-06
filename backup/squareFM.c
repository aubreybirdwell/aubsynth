/* squareWave.c creates a square oscilator of desired number of partials
 * Aubrey Birdwell
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "aubsynth.h"

float *squareFM(float db,
		  float fund,
		  int partials,
		  float *mod,
		  float mi,
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
  for (int i = 0; i < partials; i++)
    {
      //end at nyquist frequency
      int freq = (2*i+1) * fund;
      if (freq > srate/2) {break;}
      flist[i] = freq;

      //no need for phase ... or could it be interesting?
      phlist[i] = 0;
      alist[i] = A / (2*i+1);
      
      //printf("freq %d = %f\n", i, fList[i]);
      //printf("amp %d = %f\n", i, aList[i]); 
      
    }

  output = additiveFM(flist, phlist, alist, partials, mod, mi, dur, srate, nchan);
  output = transformDecibels(output, samples, db); 

  return output;
  
}

