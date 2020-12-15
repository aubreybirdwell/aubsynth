/* combine two buffers into a stereo buffer
 * Programmer: Aubrey Birdwell
 * When: fall 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float *toNChan(float **data,		
		double duration,
		int srate,
		int nchan
		)
{
  
  int sampleFrames = (int)(duration * srate) ;
  int samples = sampleFrames * nchan ;

  float *ptrCombined, *pC;

  //d1 = data;
  //d2 = data2;
   
  pC = ptrCombined = (float *)malloc(samples * sizeof(float));
  
  if ( ptrCombined == NULL ) {
    printf("Error! Memory not allocated.");
    exit(0);
  }

  
  for ( int i = 0; i < sampleFrames; i++) {
    for ( int j = 0; j < nchan; j++) {
      
      //interleave buffers contains at each nchan position in **arr
      //too bad about the col major thing. Perhaps I can fix this memory access blunder?
      *pC++ = data[j][i];
      //this takes the array of pointers to buffers
      //and interleaves the data, arr1[n] followed by arr2[n]
      //into a single flattened array.
    }
  }

  //remember to free the buffers

  //will this free both buffers?
  //free(data);
  //free(data);

  return ptrCombined;
}
