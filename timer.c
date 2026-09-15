/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

bool signal_happened = false;
time_t start_time;
int num_signals = 0;

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  signal_happened = true;
  num_signals++;
  return; //exit after printing
}

void interrupt(int signum){
  time_t elapsed = time(NULL) - start_time;
  printf("time elapsed: %ld, alarms occured: %d\n", elapsed, num_signals);
  exit(1);
}

int main(int argc, char * argv[])
{
  start_time = time(NULL);
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  signal(SIGINT,interrupt);
  while(1){
    alarm(5); //Schedule a SIGALRM for 5 seconds
    while(!signal_happened); //busy wait for signal to be delivered
    printf("Turing was right!\n");
    signal_happened = false;
  }
  return 0; //never reached
}