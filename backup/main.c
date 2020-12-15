#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "aubsynth.h"

// driver main
int main() {

  //relevant to all buffers
  float seconds = 1.0;
  int srate = 44100;
  short nchan = 1;
  
  //pointers for buffers and filewrite
  float *waveform; //*waveform2;
  char *fileName; 
  
  //samples var
  //int samples = (int)(seconds * srate * nchan);

  //adsr specific test data:

  double timeX[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
  double ampY[] = {0.0, 0.4, 0.5, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.05, 0.0};

  for(int i = 0; i < 12; i++) {

    //nchan = 1;

    char pre[30] = "synth";
    char post[4] = ".wav";    
    
    char snum[20];
    
    // convert int to string [buf] 
    snprintf(snum, 20,"%d",i);
  
    //name of sound file output
    strcat(pre, snum);

    
    printf("%s", pre);
  
    fileName = pre;
    
    
    waveform = sineWave(0.5, 0, mtof((34+i), 10), seconds, srate, nchan);
    //waveform2 = sineWave(0.5, 0, mtof(65, 10), seconds, srate, nchan);
    
    waveform = envelope(timeX, ampY, 11, waveform, seconds, srate, nchan);
    //waveform2 = envelope(timeX, ampY, 11, waveform2, seconds, srate, nchan);
  
    //nchan = 2;
    
    //combined buffers to make into channels
    //float **comb = malloc(sizeof(float *) * nchan);
    
    //comb[0] = waveform;
    //comb[1] = waveform2;
    
    //waveform = toNChan(comb, seconds, srate, nchan);
    //waveform = toStereo(waveform, waveform2, seconds, srate, nchan);
    
    short *output;
    
    output = floatInt(waveform, seconds, srate, nchan);
    
    writeWaveFile(fileName, output, seconds, srate, nchan);
    
    free(output);
  }
  
  free(waveform);
  
  //free(waveform2);
  //free(output);
  
  return 0;
}
