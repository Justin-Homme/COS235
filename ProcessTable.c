#include<stdio.h>
#include "ProcessTable.h"

struct ProcessTable *createInitialTable(int newNumProcesses, int sliceval)
{
  struct ProcessTable *newTable = (struct ProcessTable *)malloc(sizeof(struct* ProcessTable));

  newTable->numberProc = newNumProcesses;
  newTable->cpuProc = -1;
  newTable->rr_slice = sliceval;

  return newTable;
}

void printTable(struct ProcessTable *tableToPrint)
{
  printf("Number of processes: %d\n", tableToPrint->numberProc);
  printf("ID\tPri\tCPU\tI/O\tTot\tRem\tState\n");

  for(struct Process *curProc = tableToPrint->processes; *curProc != NULL; curProc++)
  {
    printProcess(*curProc);
  }
}

int findpid(ProcessTable *tp, int pid)
{
  int count = 0;
  int curPid;
  for(struct Process *curProc = tp->processes; *curProc != NULL; curProc++)
  {
    curPid = curProc->id;
    if(curPid == pid) {
      return count;
    }
    count++;
  }
  return -1;
}

void freeProcessTable(struct ProcessTable *tableToFree)
{
  for(struct Process *curProc = tableToFree->processes; *curProc != NULL; curProc++)
  {
    free(curProc);
  }
  free(tableToFree); 
}