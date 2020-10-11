/* driver program for aubrey's synthesizer
 * Programmer: Aubrey Birdwell
 * When: Summer 2020
 * references: http://soundfile.sapp.org/doc/WaveFormat/
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "aubsynth.h"

// driver main
int main() {

  //relevant to all buffers
  float seconds = 10.0;
  int srate = 44100;
  short nchan = 1;
  
  //pointers for buffers and filewrite
  float *waveform, *waveform2;
  char *fileName; 
  
  //samples var
  int samples = (int)(seconds * srate * nchan);

  //adsr specific test data:

  double timeX[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
  double ampY[] = {0.0, 0.4, 0.5, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.05, 0.0};

  //name of sound file output
  fileName = "newSound.wav";

  /*
  waveform2 = sineWave(0.5, 0, mtof(64, 10), seconds, srate, nchan);
  waveform = squareFM(90.0, mtof(32,0), 10, waveform2, 50, seconds, srate, nchan);
  */

  
  // a fm sound with a trangle for modulation with an eg applied to it
  
  waveform2 = triangleWave(90.0, mtof(32, 10), 10, seconds, srate, nchan);

  //waveform2 = sineWave(.5, 0, mtof(32, 10), seconds, srate, nchan);

  waveform2 = envelope(timeX, ampY, 11, waveform2, seconds, srate, nchan);
  
  waveform2 = sineFM(0.7, 0, mtof(32, 0), waveform2, 50, seconds, srate, nchan);

  waveform = sineFM(0.7, 0, mtof(32, 0), waveform2, 2.3, seconds, srate, nchan);

  waveform = envelope(timeX, ampY, 11, waveform, seconds, srate, nchan);

  waveform = ampMod(waveform, waveform2, 90, seconds, srate, nchan);
		       
  waveform = addBuffers(waveform, waveform2, seconds, srate, nchan);

  waveform = envelope(timeX, ampY, 11, waveform, seconds, srate, nchan);
  
    

  free(waveform2); 

  waveform = transformDecibels(waveform, samples, 96);

  
  float *waveptr;
  waveptr = waveform;

  printf("The peak db of the sound is: %f\n", quickDecibels(waveptr, samples));

  short *output;
  
  output = floatInt(waveform, seconds, srate, nchan);
  
  writeWaveFile(fileName, output, seconds, srate, nchan);

  free(waveform);
  free(output);
  
  return 0;
}
