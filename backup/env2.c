#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * With the time segments, there's the possibility of round
 * of error in the total length of the sound.
 *
 * The 'time points' are given as percentages of the whole,
 * and are used to determine the length of each line
 * segments.
 *
 * That's why there's the possibility of error in the 
 * sum of the samples for the envelope: it might not be
 * exactly equal to the total duration of the sound.
 *
 * To avoid that, the length of the final line segment is
 * not calculated as a percentage, but by subtracting the
 * sum of the lines segments up to N-1, from the total
 * length of the data.
 *
 */

int *makeTimeSegments(float TP[], int N, float dur, int sr)
{
    int *TS ;
    int i, sum, totalSamples = dur * sr ;

    TS = (int *)malloc(N * sizeof(int)) ;

    sum = 0 ;
    for ( i = 0 ; i < N - 1 ; i++ ) {
      TS[i] = (( TP[i+1] - TP[i] ) * totalSamples) + 0.5 ;
      sum += TS[i] ;  // keep track of the sum of samples
    }
    // length of final line segment
    TS[N-1] = totalSamples - sum ; // avoid round off error

    return TS ;
}

/*
 * to calculate the amplitude increment for each line
 * segment, one has to take a bit of care.
 *
 * the LAST line segment must end with a zero (to avoid
 * discontinuities in the waveform)
 *
 * the other line segments must end with a value just before
 * their final value (just before a1)
 *
 * to do that, the calculation for the first N-1 line
 * segments has to be:
 *      aInc = (a1 - a0) / length
 *
 * but to ensure that the LAST line segment has a FINAL
 * value of zero, the * calculation has to be:
 *      aInc = (a1 - a0) / ( length - 1 )
 *
 * This ensures that the last value will be that of a1, and
 * that the previous segments will end will a final value of
 * (a1-aInc)
 *
 */

float *makeAmplitudeInc(int *TS, float AP[], int nPoints)
{
    int i ;
    float *AI ;

    AI = (float *)malloc(nPoints * sizeof(float)) ;

    // create the amplitude increments
    for ( i = 0 ; i < nPoints - 2 ; i++ )
        AI[i] = ( AP[i+1] - AP[i] ) / TS[i] ;

    AI[i] = ( AP[i+1] - AP[i] ) / (TS[i] - 1) ; // last increment

    return AI ;
}

void applyEnvelope(short *data, int *TS, float *AI, int nPoints) 
{
    short *pd ;
    float percent, slope ;
    int i, j, samples ;

    pd = data ; // set the pointer to start of data
    percent = 0 ;     // start percent at zero
    for ( i = 0 ; i < nPoints - 1 ; i++ ) {
        samples = TS[i] ;   // duration of line segment
        slope = AI[i] ;    // slope of line segment
        for ( j = 0 ; j < samples ; j++ ) {
            *pd = *pd * percent ;   // multiply data by 'pc'
            percent = percent + slope ; // increment percent
            pd++ ;  // increment data pointer
        }
    }

    return ;
}

void adsr(float timePT[], float ampPT[], int nPoints, 
        short *data, float dur, int sr)
{
    int i, *timeSeg ;
    float *ampInc ;

    /*
     * Create the time segments and the amplitude increments
     */

    timeSeg = makeTimeSegments(timePT, nPoints, dur, sr) ;
    ampInc = makeAmplitudeInc(timeSeg, ampPT, nPoints) ;

    for ( i = 0 ; i < nPoints ; i++ )
        fprintf("\t%f %f  %7d %f\n",
                timePT[i], ampPT[i], timeSeg[i], ampInc[i]);

    /*
     * apply envelope to the data
     */

    applyEnvelope(data, timeSeg, ampInc, nPoints) ; 

    free(timeSeg) ;
    free(ampInc) ;

    return ;
}

short *makeSine(float dur, int sr)
{
    float f = 440 ;
    float twopi = 2 * M_PI ;
    float A, dB = 96 ;
    float ph, phInc ;
    short *pd, *data ;
    int samples = dur * sr ;

    data = (short *)malloc(samples * sizeof(short)) ;

    phInc = twopi * f / sr ;
    ph = 0 ;

    A = pow(10.0, dB/20.0) / 2 ;

    for ( pd = data ; pd < data + samples ; pd++ ) {
        *pd = (short)(A * sin(ph)) ;
        if ( ( ph += phInc ) >= twopi )
            ph -= twopi ;
    }

    return data ;
}

extern void writeWaveFile(
		   char *fileName, 
		   short *data, 
		   double duration,
		   int srate, 
		   short nchan) ;

int main(void)
{
    int sr = 44100 ;
    int N = 6 ;
    float tp[] = {0.0, 0.1, 0.25, 0.6, 0.9, 1.0} ;
    float ap[] = {0.0, 1.0, 0.75, 1.0, 0.5, 0.0} ;
    short *data ;
    float dur = 1 ;

    data = makeSine(dur, sr) ;
    adsr(tp, ap, N, data, dur, sr) ;

    writeWaveFile("env2.wav", data, dur, sr, 1) ;

    return 0 ;
}
