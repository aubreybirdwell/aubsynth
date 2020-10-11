/* creates a sine wave float value data block of specific parameters
 * Programmer: Aubrey Birdwell
 * When: Summer 2020
 * references: http://soundfile.sapp.org/doc/WaveFormat/
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BITS 16
#define MaxLinearAmp 32512 // +-2^15 or 32768 but I subtracted 256 to leave some headroom

/* Function for dynamically generating a sine wave 
 * A: amplitude 0.0 - 0.9
 * desiredPhase: usually 0 unless waveform used as an lfo or control signal 
 * F: frequency in hz 0.1 - 20.0 khz -ish 
 * duration: seconds in 0.0 floats
 * srate: usually 44100 for cd quality but will use higher in the future
 * nchan: audio channels, 1 for now
 */ 

float *sineWave(double A,
		double desiredPhase, 
		double F,
		double duration,
		int srate,
		int nchan)
{
  
  // create buffer length for sine wave - divide samplerate by 1000 to obtain ms sample chunks
  int sampleFrames = (int)(duration * srate) ;
  int samples = sampleFrames * nchan ;
  float  *ptrWave, *p; //buffer pointer, short *ptrWave;
  double twopi = 2 * M_PI ;
  double phaseInc = (F * twopi / srate) ; //increment of the phase
  double ph = desiredPhase * twopi ;
  
  //make a buffer
  p = ptrWave = (float *)malloc(samples * sizeof(float));
  
  if ( ptrWave == NULL ) {
    printf("Error! Memory not allocated.");
    exit(0);
  }
  
  /* I need to address multiple channels at some point...
   * re: MaxLinearAmps -- no need to scale by this anymore
   * Need to keep in mind the value I am feeding the function
   * and that it will only be values between 0.0 - 1.0
   */

  p = ptrWave ;
  for ( int i = 0 ; i < samples ; i++ ) {
    *p++ = A * sin(ph) ;
    ph += phaseInc ;
    if ( ph >= twopi )
      ph -= twopi ;
  }
  
  return ptrWave;
}
