#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

  //int i = 10;
    
  for(int i = 0; i < 12; i++) {

    char pre[30] = "synth";
    char post[4] = ".wav";    
    
    char snum[20];
    
    // convert int to string [buf] 
    snprintf(snum, 20,"%d",i);
  
    //name of sound file output
    strcat(pre, snum);

    
    printf("%s\n", pre);
    
  }
  return 0;
}
