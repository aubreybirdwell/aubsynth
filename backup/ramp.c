/* a simple ramp generator that applies itself to audio buffer
 * less to set up than the adsr
 * Programmer: Aubrey Birdwell
 * When: Summer 2020
 * references: http://soundfile.sapp.org/doc/WaveFormat/, stack exchange, 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

short *ramp(float *data,
	    double startAmp,
	    double endAmp,
	    double duration,
	    int srate,
	    int nchan)
{
  int sampleFrames = (int)(duration * srate) ;
  int samples = sampleFrames * nchan ;
  float *ptrRamp, *p, *d;
  
  double rampIncr;
  
  //ramp increment = (desired amplitude - starting amplitude) / # samples
  rampIncr = ((endAmp - startAmp) / samples);
  
  p = ptrRamp = (float *)malloc(samples * sizeof(float));
  
  if ( ptrRamp == NULL ) {
    printf("Error! Memory not allocated.");
    exit(0);
  }
  
  for (int i = 0; i < samples; i++) {
    *p++ = *d++ * (startAmp + (i * rampIncr));
  }
  
  return ptrRamp;  
}
