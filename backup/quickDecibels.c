/* get the decibles from short buffer and return the decibles
 * Programmer: (using Arun Chandra's code example)
 * When: Summer 2020
 * references: http://soundfile.sapp.org/doc/WaveFormat/
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define a0 (pow(10, -5))

float quickDecibels(float *data, int samples)
{
  
  //float *fdata, *fp;
  float *pd, db;
  float smax, smin;
  pd = data ;
  
  //grab min and max + and - values
  smax = smin = *data ;
  for ( int i = 0 ; i < samples ; i++, pd++ ) {
    if ( *pd > smax ) smax = *pd ;
    else if ( *pd < smin ) smin = *pd ; // changed to make min negative
  }

  //debug test print
  // printf("smax = %f and smin = %f\n", smax, smin);

  //create average of peak min and max  
  float peakAverage;
  peakAverage = (smax + fabsf(smin))/2;
  
  db = 20 * log10(peakAverage/a0) ;  // value in decibels of waveform
  printf("decibels = %f; and a0 = %f\n", db, a0);
  
  // save this stuff for later...
  // not sure why yet...
  // turning decibels into linear values:
  // pow(10.0, db/20) / 2
  
  // while ( samples-- ) {
  //  *fp++ = *pd++ / 32768.0 ;
  // }
  
  return db;
}
