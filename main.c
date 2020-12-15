#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "aubsynth.h"
#include "fft.h"

float TWOPI ;/* needed for rfft and cfft */
float PI ; /* needed for rfft and cfft */

// driver main
int main() {

  PI = 4.*atanf(1.) ;
  TWOPI = 8.*atanf(1.) ;

  //relevant to all buffers
  //fft requires a divisibility by 2 or in this case the window is 16 so .2*16
  float seconds = 3.2;
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
  
  //for(int i = 0; i < 2; i++) {
  
  //char pre[30] = "newave";
  
  //char snum[20];
  
  // convert int to string [buf] 
  //snprintf(snum, 20,"%d",i);
  
  //name of sound file output
  //strcat(pre, snum);
  
  //printf("%s", pre);
  
  //fileName = pre;
  
  fileName = "new.wav";
    
  // a fm sound with a trangle for modulation with an eg applied to it
  
  waveform2 = triangleWave(90.0, mtof((32) , 30), 10, seconds, srate, nchan);

  //waveform2 = sineWave(.5, 0, mtof(32, 10), seconds, srate, nchan);
    
  waveform2 = envelope(timeX, ampY, 11, waveform2, seconds, srate, nchan);
  
  waveform2 = sineFM(0.7, 0, mtof((32), 20), waveform2, 50, seconds, srate, nchan);
  
  waveform = sineFM(0.7, 0, mtof((32), 0), waveform2, 2.3, seconds, srate, nchan);
  
  waveform = envelope(timeX, ampY, 11, waveform, seconds, srate, nchan);
  
  waveform = ampMod(waveform, waveform2, 90, seconds, srate, nchan);
  
  waveform = addBuffers(waveform, waveform2, seconds, srate, nchan);
  
  waveform = envelope(timeX, ampY, 11, waveform, seconds, srate, nchan);
  
  waveform = transformDecibels(waveform, samples, 78);

  waveform2 = transformDecibels(waveform2, samples, 78);

  //waveform = movingAverage(waveform, seconds, srate, nchan);
  
  //waveform = averageBuffers(waveform, waveform2, seconds, srate, nchan);

  waveform = toFFT(waveform, 16, seconds, srate);

  waveform = fromFFT(waveform, 16, seconds, srate);
  
  
  /* waveform = sineWave(0.5, 0, mtof((45+i), 10), seconds, srate, nchan); */
  /* waveform2 = sineWave(0.5, 0, mtof((45+i), 35), seconds, srate, nchan); */
  /* waveform = addBuffers(waveform, waveform2, seconds, srate, nchan);         */
  /* waveform = envelope(timeX, ampY, 11, waveform, seconds, srate, nchan);     */
  /* waveform = transformDecibels(waveform, samples, 78); */
  
  //waveform2 = envelope(timeX, ampY, 11, waveform2, seconds, srate, nchan);
  
  //combined buffers to make into channels
  //float **comb = malloc(sizeof(float *) * nchan);
  
  //comb[0] = waveform;
  //comb[1] = waveform2;
  
  //waveform = toNChan(comb, seconds, srate, nchan);
  
  //float *stereoWaveform;
  
  //stereoWaveform = toStereo(waveform, waveform2, seconds, srate, 2);
  
  short *output;
  
  //output = floatInt(stereoWaveform, seconds, srate, 1);
  output = floatInt(waveform, seconds, srate, 1);
  
  writeWaveFile(fileName, output, seconds, srate, 1);
  
  free(output);
  //free(stereoWaveform);
  
  //}

  free(waveform);
  //free(waveform2);
  
  //free(output);
  
  return 0;
}
