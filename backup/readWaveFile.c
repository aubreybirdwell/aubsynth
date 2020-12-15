// Not worked on yet. I am beginning with the write wave file code. must modify. 


/* program that writes a data block for a wave file
 * Programmer: Aubrey Birdwell
 * When: Summer 2020
 * references: http://soundfile.sapp.org/doc/WaveFormat/
 */

#include <stdio.h>
#include <stdlib.h>
// #include <stdint.h>
// leaving this for later. Will likely switch to uint8_t and uint16_t types for portability
#include <math.h>

#define BITS 16
#define MaxLinearAmp 32512 // +-2^15 or 32768 but I subtracted 256 to leave some headroom

//RIFF WAVE header struct
typedef struct AudioHeader {
  
  // Riff Wave Header
  char chunkID[4]; //1 char * 4 bytes 
  int  chunkSize;  //4 bytes
  char format[4];  //4 bytes
  
  // wave format consists of two subchunks: "fmt" and "data"
  char subChunk1ID[4]; //4 bytes
  int  subChunk1Size;  //4 bytes
  short int audioFormat;  //2 bytes
  short int numChannels;  //2 bytes
  int sampleRate;         //4
  int byteRate;           //4
  short int blockAlign;   //2
  short int bitsPerSample;  //2
  // short int extraParamSize --if PCM, then doesn't exist
  // extraParams -- space for extra params
  
  // "data" subchunk contains the size of the data and the actual sound follows
  char subChunk2ID[4];  //4
  int  subChunk2Size;   //4
  
} AudioHeader;

// included for calculation later
typedef struct ChunkID {
  unsigned char idName[4] ;
  unsigned int size ;
} ChunkID ;


/*function to write a wave file from data set
 * fileName: includes .wav for now
 * data: is pointer to the data block to be written.
 * duration: is in seconds or decimal seconds i.e. float values
 * srate: is 44100 or user specifiable but must match to data
 * nchan: is number of channels - sticking to one for now
 */

void writeWaveFile(
		   char *fileName, 
		   short *data, 
		   double duration,
		   int srate, 
		   short nchan)
{
  // size of data = seconds * rate of sampling * channels * size of data words
  int dataSize = duration * srate * nchan * sizeof(short) ; // size of data in bites
  int fileSize = dataSize + sizeof(AudioHeader) - sizeof(ChunkID) ; // total size
  int sampleFrames = (int)(duration * srate) ; //# sample packets but not # bytes 
  //use constant BITS for bitsPerSample
  
  //generate struct
  AudioHeader newHeader;
  
  //populate ChunkID and Format sections of the header struct
  newHeader.chunkID[0] = 'R';
  newHeader.chunkID[1] = 'I';
  newHeader.chunkID[2] = 'F';
  newHeader.chunkID[3] = 'F';
  
  //4 + (8 + subChunk1Size) + (8 + subChunk2Size) == 36 + calculate size
  //newHeader.chunkSize = 36 + 44100;//(sampleFrames * nchan * sizeof(short));
  newHeader.chunkSize = fileSize ;
  
  newHeader.format[0] = 'W';
  newHeader.format[1] = 'A';
  newHeader.format[2] = 'V';
  newHeader.format[3] = 'E';
  
  //populate SubChunk1ID
  newHeader.subChunk1ID[0] = 'f';
  newHeader.subChunk1ID[1] = 'm';
  newHeader.subChunk1ID[2] = 't';
  newHeader.subChunk1ID[3] = ' ';
  
  //set for pcm which is the number of bytes left in the header
  newHeader.subChunk1Size = 16;
  newHeader.audioFormat = 1; // set to pcm
  newHeader.numChannels = nchan; //set num audio channels from parameters
  newHeader.sampleRate = srate; //set sample rate - 44100 hz for standard
  newHeader.bitsPerSample = BITS; //set bit depth per sample
  
  //set bytes per second...
  newHeader.byteRate = srate * nchan * (int)(BITS/8.0);
  
  //This aligns the data per number of channels
  newHeader.blockAlign = nchan * (int)(BITS/8.0);
  
  //populate subChunk2ID
  newHeader.subChunk2ID[0] = 'd';
  newHeader.subChunk2ID[1] = 'a';
  newHeader.subChunk2ID[2] = 't';
  newHeader.subChunk2ID[3] = 'a';
  
  //manually loading the 30 second buffer
  newHeader.subChunk2Size = sampleFrames * nchan * (int)(BITS/8.0);
  newHeader.subChunk2Size = dataSize ;
  
  //create pointer for file dump
  FILE *wave_file;
  
  //create binary writable file with a name
  wave_file = fopen(fileName, "wb");
  
  //binary write takes 4 paramaters: &ptr, data size in bytes, number of units, ptr or &notation <-> not ptr. 
  fwrite(&newHeader, sizeof(AudioHeader), 1, wave_file);
  fwrite(data, sizeof(short), (sampleFrames * nchan), wave_file);
  
  // closes port to shell
  fclose(wave_file);  
  
  return;
}
