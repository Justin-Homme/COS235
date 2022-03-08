#include<stdio.h>
#include<stdlib.h>

struct Process
{
  unsigned int id, totalTime, remainingTime;
  int priority;
  unsigned short cpuBurst, ioBurst;
  char state;
};

void printProcess(struct Process *process)
{
  printf("%2d\t%3d\t%3d\t%3d\t%3d\t%3d\t    %c\n", id, priority, cpuBurst,
          ioBurst, totalTime, remainingTime, state);
} // printProcess

struct Process *createProcess(int newID, int priority, int cpuBurst,
  int ioBurst, int totalTime)
{
  //TODO use malloc to implement this function
  this.id = malloc(sizeOfInt());
  priority = malloc(sizeOfInt());
  cpuBurst = malloc(sizeOfInt());
  ioBurst = malloc(sizeOfInt());
  totalTime = malloc(sizeOfInt());
  // TODO fix this since it is probably very wrong
  
} // createProcess

int switchState(struct Process *processToSwitch, char newState)
{
    int val;
    switch(*processToSwitch)
    {
        case N:
          if(newState == R || T) {
            val = 0;
          } else {
            val = 1;
          }
          break;

        case R:
          if(newState == Q || T) {
            val = 0;
          } else {
            val = 1;
          }
          break;

        case Q:
          if(newState == B || T) {
            val = 0;
          } else {
            val = 1;
          }
          break;

        case B:
          if(newState == Q || T) {
            val = 0;
          } else {
            val = 1;
          }
          break;

          default:
            val = 1;
    }

    if(val == 0) {
      *processToSwitch = newState;
    }

    return val;

} // switchState
