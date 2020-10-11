/* program that writes a data block for a wave file
 * Programmer: Aubrey Birdwell
 * When: Summer 2020
 * references: http://soundfile.sapp.org/doc/WaveFormat/
 */

#include <stdio.h>
#include <stdlib.h>

/*function to write the raw sound data for graphical plotting
 * fileName: include .txt for now
 * data: is pointer to the data block to be written.
 * duration: is in seconds or decimal seconds i.e. float values
 * srate: is 44100 or user specifiable but must match to data
 * nchan: is number of channels - sticking to one for now
 */

void writeTxt(
		   char *fileName, 
		   short *data, 
		   double duration,
		   int srate, 
		   short nchan)
{
  // size of data = seconds * rate of sampling * channels * size of data words
  //int dataSize = duration * srate * nchan * sizeof(short) ; // size of data in bites
  int samples = (int)(duration * srate * nchan) ; // will plot funny if stereo to be adressed later  
  //create pointer for file dump
  FILE *raw_file;
  
  //create binary writable file with a name
  raw_file = fopen(fileName, "wb");
  
  //binary write takes 4 paramaters: &ptr, data size in bytes, number of units, ptr or &notation <-> not ptr. 
  fwrite(data, sizeof(short), samples, raw_file);
  
  // closes port to shell
  fclose(raw_file);  
  
  return;
}
