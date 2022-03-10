#include<stdio.h>
#include<stdlib.h>
#include "Process.h"

/**
* has functions: printProcess, *createProcess, and switchState
*/


void printProcess(struct Process *process)
{
  printf("%2d\t%3d\t%3d\t%3d\t%3d\t%3d\t    %c\n", process->id, process->priority,
    process->cpuBurst, process->ioBurst, process->totalTime, process->remainingTime,
    process->state);
} // printProcess

struct Process *createProcess(int newID, int priority, int cpuBurst,
  int ioBurst, int totalTime)
{
  struct Process *newProcess = (struct Process *)malloc(sizeof(struct Process));

  newProcess->id = newID;
  newProcess->priority = priority;
  newProcess->cpuBurst = cpuBurst;
  newProcess->ioBurst = ioBurst;
  newProcess->totalTime = totalTime;
  newProcess->remainingTime = totalTime;  // new process so full time remains
  newProcess->state = 'N';                // 'N' because it's a new process

  return newProcess;
} // createProcess

int switchState(struct Process *processToSwitch, char newState)
{
    int val;    // 0 means valid and 1 means invalid
    char *curState = processToSwitch->state;
    switch(*curState)
    {
        case 'N':
          if(newState == 'R') {
            val = 0;
          } else {
            val = 1;
          }
          break;

        case 'R':
          if(newState == 'Q' || 'T') {
            val = 0;
          } else {
            val = 1;
          }
          break;

        case 'Q':
          if(newState == 'B' || 'T') {
            val = 0;
          } else {
            val = 1;
          }
          break;

        case 'B':
          if(newState == 'Q' || 'T') {
            val = 0;
          } else {
            val = 1;
          }
          break;

          default:
            val = 1;    // if not one of above cases, any switch invalid
    }

    if(val == 0) {
      processToSwitch->state = newState;  // valid so update process
    }

    return val;   // 0 if valid and 1 if invalid

} // switchState
