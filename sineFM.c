/* creates a sine wave float value data block of specific parameters
 * Programmer: Aubrey Birdwell
 * When: Summer 2020
 * references: http://soundfile.sapp.org/doc/WaveFormat/
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "aubsynth.h"

/* Function for dynamically generating a frequency modulated sine wave using an audio buffer  
 * mod is the buffer of data to modulate the carrier with
 * mi = modulation index or intensity of modulation 
 * desiredPhase: usually 0 unless waveform used as an lfo or control signal 
 * F: frequency in hz 0.1 - 20.0 khz -ish 
 * db = desired db, scaled afterwards
 * duration: seconds in 0.0 floats
 * srate: usually 44100 for cd quality but will use higher in the future
 * nchan: audio channels, 1 for now
 */ 

float *sineFM(double A,
	      double desiredPhase, 
	      double F,
	      float *mod,
	      double mi,
	      double duration,
	      int srate,
	      int nchan)
{
  

  int sampleFrames = (int)(duration * srate) ;
  int samples = sampleFrames * nchan ;
  float  *ptrWave, *p, *m; //buffer pointer, short *ptrWave;
  double twopi = 2 * M_PI ;
  double phaseInc = (F * twopi / srate) ; //increment of the phase
  double ph = desiredPhase * twopi ;
  
  //make a buffer
  p = ptrWave = (float *)malloc(samples * sizeof(float));
  
  if ( ptrWave == NULL ) {
    printf("Error! Memory not allocated.");
    exit(0);
  }
  
  p = ptrWave ;
  m = mod ;
  
  for ( int i = 0 ; i < samples ; i++ ) {
    *p++ = A * sin(ph+(mi * *m++)) ;
    ph += phaseInc ;
    if ( ph >= twopi )
      ph -= twopi ;
  }
  
  return ptrWave;
}
