//function to create a riff header and write a wave file to the current directory

extern void cfft(float *x, int  NC, int forward) ;

extern void rfft(float *x, int  N, int forward) ;


extern float *toCFFT(float *data,		
		    int window,
		    double duration,
		    int srate) ;


extern float *toRFFT(float *data,		
		      int window,
		      double duration,
		      int srate) ;


extern float *toNChan(float **data,		
		      double duration,
		      int srate,
		      int nchan) ;


extern float *toStereo(float *data,
		       float *data2,
		       double duration,
		       int srate,
		       int nchan) ;


extern float *averageBuffers(float *data,
			     float *data2,
			     double duration,
			     int srate,
			     int nchan) ;


extern float *movingAverage(float *data,
			    double duration,
			    int srate,
			    int nchan) ; 


extern void display_wave(float *data,
			 double duration,
			 int srate) ;  


extern void writeWaveFile( char *fileName,
			   short *data,
			   double duration,
			   int srate,
			   short nchan) ;


extern void writeBin(char *fileName, 
		     short *data, 
		     double duration,
		     int srate, 
		     short nchan) ;


//function to produce note freqency of midi note; takes args midi_note and tune_in_cents


extern float mtof(int midi_note, int tune_in_cents) ;

/* Function for dynamically generating a sine wave 
 * A: amplitude 0.0 - 0.9
 * desiredPhase: usually 0 unless waveform used as an lfo or control signal 
 * F: frequency in hz 0.1 - 20.0 khz -ish 
 * duration: seconds in 0.0 floats
 * srate: usually 44100 for cd quality but will use higher in the future
 * nchan: audio channels, 1 for now
 */ 

extern float *sineWave(double A,
		       double desiredPhase, 
		       double F,
		       double duration,
		       int srate,
		       int nchan) ;


// new experiement with fm wavetable modulated sine function

float *sineFM(double A,
	      double desiredPhase, 
	      double F,
	      float *mod,
	      double mi,
	      double duration,
	      int srate,
	      int nchan) ;

//square partial generator that passes on a modulation source to be used with additiveFM

float *squareFM(float db,
		float fund,
		int partials,
		float *mod,
		float mi,
		float dur,
		int srate,
		int nchan) ;
  
//additive function that frequency modulates each partial indepentantly

float *additiveFM(float flist[],
		float phlist[],
		float alist[],
	        int nPartials,
		float *mod,
		float mi,
		float dur,
		int srate,
		int nchan) ;

  
//amplitude modulation feed it standin wavetable for cf and modulation wave for mf

extern float *ampMod(float *cf,
		     float *mf,
		     float db,
		     float dur,
		     int srate,
		     int nchan) ;


//simple additive oscilator stack... takes list of freq and amp ratios
//needs full overhaul

extern float *addsyn(float A,
		     float desiredPhase,
		     float fund,
		     float dur,
		     int srate,
		     int nchan,
		     int nPartials,
		     float flist[],
		     float alist[]) ;

//adds frequency list phlist and amplitude list ... clean and works. 
float *addfreqs(float flist[],
		float phlist[],
		float alist[],
	        int nPartials,
		float dur,
		int srate,
		int nchan) ;

// build a squarewave using the addsyn and sineWave functions

extern float *squareWave(float A,
			 float fund,
			 int partials,
			 float dur,
			 int srate,
			 int nchan) ;

// build a squarewave using the addfreqs and sineWave functions 

extern float *sawtoothWave(float db,
			   float fund,
			   int partials,
			   float dur,
			   int srate,
			   int nchan) ;

// build a triangle wave using the addfreqs and sinWave functions

extern float *triangleWave(float db,
			  float fund,
			  int partials,
			  float dur,
			  int srate,
			  int nchan) ;
  
// convert a buffer from int +- to float 0.0-1.0

extern float *intFloat(short *data,
		       double duration,
		       int srate,
		       int nchan) ;

// convert a float buffer back to int

extern short *floatInt(float *data,
		       double duration,
		       int srate,
		       int nchan) ;
  
// get decibles from a short buffer with full description of buffer

extern float getDecibels(float *data, double duration, int srate, int nchan) ;


// less args version of getDecibels for when you are inside a function

extern float quickDecibels(float *data, int samples) ;


// function to transform db of a short buffer

extern float *transformDecibels(float *data, int samples, float desiredDecibels) ;


//function to multiply two buffers with same length

extern float *multiplyBuffers(float *data,
			      float *data2,
			      double duration,
			      int srate,
			      int nchan) ;


//function to add two buffers with same length

extern float *addBuffers(float *data,
			 float *data2,
			 double duration,
			 int srate,
			 int nchan) ;

//function to apply a simple ramp with a start and end amplitude accross entire buffer

extern short *ramp(short *data,
		     double startAmp,
		     double endAmp,
		     double duration,
		     int srate,
		     int nchan) ;

//simple adsr envelope which applies double x[5],y[5] to any buffer start must be 0 and end must be 1

extern float *adsr(double timePoints[],
		   double ampPoints[],
		   float *data,
		   double duration,
		   int srate,
		   int nchan) ;

//multipoint envelope

extern float *envelope(double timePoints[],
		       double ampPoints[],
		       int points,
		       float *data,
		       double duration,
		       int srate,
		       int nchan) ;
  

