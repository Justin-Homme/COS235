/*
 * Main driver method - provided for your use by Dr. A.
 * Be sure to READ this carefully and understand what it is doing.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ProcessTable.h"

// a global pointer to the process table
struct ProcessTable *processTable;

// global flags
//     for output options:  (needed for phase 2)
//     verbose - tell about every change
//     time-verbose - timestamp every clock tick
int verbose, timeverb;
//     for scheduler choice: one of R,S,F
char sched = 'R';		// default: round robin

void
usagexit(char *prog)
{
    fprintf(stderr, "Usage: %s [-t | -v] nlines filename [F | S |R]\n",
	   prog);
    exit(2);
}

/*
 * Method to read initial process information from a file
 *   Open the file
 *   Loop through items
 *   - Use malloc to initialize Process space
 *   - Initialize values by reading from file using fscanf
 */
void readFile(struct ProcessTable *table, char *fileName)
{
	FILE *fd;
	int id, pri, cpu, io, total;
	int i;

	fd = fopen(fileName, "r");
	for (i=0; fd >= 0; i++) {
	    fscanf(fd, "%d %d %d %d %d\n", &id, &pri, &cpu, &io, &total);
	    table->processes[i] = createProcess(id, pri, cpu, io, total);
	    // fprintf(stderr, "%d, %d\n", i, id);
	    if (feof(fd)) { break; }
	} // endwhile
}  // readFile

int
main(int argc, char *argv[])
{
    char opt;
    char *numlines, *filename, *tsl;
    int i, sliceval, numP;

    if (argc < 4) {
	usagexit(argv[0]);
    }

    while ((opt = getopt(argc, argv, "vt")) != -1) {
       switch (opt) {
       case 'v':
	   verbose = 1;
	   break;
       case 't':
	   timeverb = 1;
	   break;
       default: /* '?' */
	   usagexit(argv[0]);
	}
    }
    numlines = argv[optind++];
    filename = argv[optind++];
    if (optind < argc) {
        sched = argv[optind][0];
	// DEBUG
	printf("sched alg: [%c]\n", sched);
    }

    // we can set the value of time slice via Environment Variable
    if (tsl = getenv("TimeSlice")) {
	sliceval = atoi(tsl);
    } else {
	sliceval = 4;
    }

    // -- done with arg parsing; read up our initial state --

    numP = atoi(numlines);
    processTable = createInitialTable(numP, sliceval);

    readFile(processTable, filename);

    /*
     * show the starting state of affairs
     */
    printTable(processTable);

    /*
     * check on state transitions:
     */
    char nxstate;
    int  apid, indx, errors = 0;

    while (scanf(" %d %c\n", &apid, &nxstate) != EOF) {
	indx = findpid(processTable, apid);
	if (indx >= 0) {
	    errors += switchState(processTable->processes[indx],
						nxstate);
	} else {
	    printf("pid: %d not found.\n", apid);
	    // TODO: errors++  ??
	}
    }
    printf("Number of errors: %d\n", errors);

    return 0;
} // main
