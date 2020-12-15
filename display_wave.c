#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif /* _MSC_VER */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include "aubsynth.h"


#define WIDTH 1200
#define HEIGHT 600


void sdl_draw(SDL_Window *window, SDL_Surface *surface, int *p)
{
  
  for(int x = 0; x < WIDTH; x++)
    {
      for(int y = 0; y < HEIGHT; y++)
	{

	  //if(scaled < y)
	  int n = *(p+x*HEIGHT+y);
	  //printf("%d", n);

	  ((Uint32*)surface->pixels)[(y*surface->w) + x] = (n > 0)? 0 :
	  SDL_MapRGB( surface->format, 256.0, 256.0, 256.0);
	}
      SDL_UpdateWindowSurface(window);
    }  
}

void display_wave(float *data,
		  double duration,
		  int srate)
{
  
  int length = duration * srate;
  int inc;
  float *p = data;
  
  /* SDL SEtup */
  if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
      fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
      exit(1);
    }
  atexit(SDL_Quit);
  
  SDL_Window *window;
  
  window = SDL_CreateWindow("Waveform Output",
			    SDL_WINDOWPOS_UNDEFINED,
			    SDL_WINDOWPOS_UNDEFINED,
			    WIDTH,
			    HEIGHT,
			    SDL_WINDOW_OPENGL
			    );

  //should allocate the size of my sdl window...
  
  //increment to advance in the buffer
  inc = (int)(length / WIDTH);
  //mid point of window
  int mid = HEIGHT/2;
  //new buffer scaled to window
  int *scaled = (int*)malloc(WIDTH * sizeof(int));
  for(int i = 0; i<WIDTH; i++)
    {      
      if(*(p + i*inc) > 0)
	{
	  *(scaled + i) = ((*(p + i*inc) * mid + mid));
	  //*(scaled + i) = *(scaled + i)%HEIGHT;
	}
      else
	{
	  *(scaled + i) = (mid - (*(p + i*inc) * mid));
	  //*(scaled + i) = *(scaled + i)%HEIGHT;
	}
    }
  
  int *arr = (int *)malloc(HEIGHT * WIDTH * sizeof(int));
  //int i, j;
  //int *p = arr;
  
    if ( arr == NULL ) {
      printf("Error! Memory not allocated.");
      exit(0);
    }

    
    //printf("The matrix elements are:\n");
    for (int i = 0; i < WIDTH; i++) {
      for (int j = 0; j < HEIGHT; j++) {

	//still not satisfactory ...
	//needs a more complicated algorithm...
	if(*(scaled+i) < j)	  	  
	  *(arr + i*HEIGHT + j) = 1;
	else
	  *(arr + i*HEIGHT + j) = 0;

	//printf("%d", *(arr + i*HEIGHT +j));
      }
      //printf("\n");
    }
  
  SDL_Surface* surface = SDL_GetWindowSurface(window);
  
  sdl_draw(window, surface, arr); //draw points
  
  SDL_Event event;
  while(1)
    {
      SDL_PollEvent(&event);
      switch (event.type)
	{
	case SDL_QUIT:
	  exit(0);
	  break;
	}
    }

  
  SDL_DestroyWindow(window);
  SDL_Quit();
  free(scaled);
  free(arr);
}


