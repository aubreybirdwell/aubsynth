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


#define WIDTH 400
#define HEIGHT 100

int scale_width(int n)
{
  //fix this code
  n = n / WIDTH; 
  return n;
}

int scale_height(int n)
{
  //fix this code
  n = n / HEIGHT;
  return n;
}

void sdl_draw(SDL_Window *window, SDL_Surface *surface, float *p, int len)
{
  len = scale_width(len);
  //printf("increments are %d", len); 
  int scaled;
  
  for(int x = 0; x < WIDTH; x++)
    {
      for(int y = 0; y < HEIGHT; y++)
	{

	  //not scaled correctly. Needs to be centered as well.
	  
	  printf("%f", *(p + (len*x)) * HEIGHT);
	  scaled = *(p + (len*x)) * HEIGHT;
	  
	  if(scaled < y)
	    ((Uint32*)surface->pixels)[(y*surface->w) + x] = SDL_MapRGB( surface->format, 0.0, 0.0, 255.0 );
	  else
	    {
	      ((Uint32*)surface->pixels)[(y*surface->w) + x] = 0;
	    }
	}      
    }  
}

void display_wave(float *data,
		  double duration,
		  int srate)
{
  
  int length = duration * srate;
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
  /* int row = WIDTH; */
  /* int col = HEIGHT; */
  
  /* int *arr = (int *)malloc(row * col * sizeof(int));  */
  /* //int i, j; */
  /* int *p = arr; */
  
  /*   if ( arr == NULL ) { */
  /*     printf("Error! Memory not allocated."); */
  /*     exit(0); */
  /*   } */
  
  
  
  
  /* printf("The matrix elements are:\n"); */
  /* for (i = 0; i < row; i++) { */
  /*   for (j = 0; j < col; j++) { */
  /* 	printf("%d ", *(arr + i*col + j));  */
  /*   } */
  /*   printf("\n"); */
  /* } */
  
  SDL_Surface* surface = SDL_GetWindowSurface(window);
  
  sdl_draw(window, surface, p, length); //draw points
  
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
  
  //return 0;
}


