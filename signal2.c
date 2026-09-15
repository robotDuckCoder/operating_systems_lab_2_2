/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>


bool signal_happened = false;

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  signal_happened = true;
  return; //exit after printing
}

int main(int argc, char * argv[])
{
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  while(1){
    alarm(5); //Schedule a SIGALRM for 5 seconds
    while(!signal_happened); //busy wait for signal to be delivered
    printf("Turing was right!\n");
    signal_happened = false;
  }
  return 0; //never reached
}