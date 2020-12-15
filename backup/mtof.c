/* midi to frequency conversion with cents tuning
 * by: Aubrey Birdwell
 *
 */

#include <stdio.h>
#include <math.h>


float mtof(int midi_note, int tune_in_cents) {
  
  float nFreq, fTune;

  //cast incoming integers as floats so as not to truncate values during division.
  fTune = (float)tune_in_cents;
  nFreq = (float)midi_note;
  
  // calculate base frequency without retuning
  nFreq = pow(2,(nFreq - 69)/12) * 440;

  //printf("Tune = %f\n", fTune);
  //printf("detune = %f\n", nFreq * pow(2,tune/1200)); 
  //detune note
  nFreq = nFreq * pow(2,(fTune/1200));

  return nFreq;
  
}

				      
