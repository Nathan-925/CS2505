#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
/**  Driver for testing PtrFuncs.c
 * 
 *   Invocation:  driver [-all | -get | -find | -sum] [-repeat]
 *   Examples:    driver -get
 *                driver -sum -repeat
 *                driver -all
 * 
 *   Switches: 
 *      -help    display invocation syntax
 *      (none)   run all tests, randomize testing
 *      -all     run tests for all three functions
 *      -get     run test only for getBytesAtOffset()
 *      -find    run test only for findOccurrencesOfByte()
 *      -sum     run test only for sumValuesAtOffsets()
 *      -repeat  repeat with previous test data
 */
#include <string.h>

#include "PtrFuncs.h"
#include "Generator.h"
#include "TestCode.h"

static const char* const outputFileName = "c04Results.txt";
static const char* const dataBlockFileName = "dataBlock.txt";

#define BLOCK_LENGTH 1024   // length in bytes of random data block

int main(int argc, char** argv) {
   
   // Check for help switch:
   if ( argc == 2 && strcmp(argv[1], "-help") == 0 ) {
		printf("Invocation:  driver [-all | -get | -find | -sum] [-repeat]\n");
		exit(1);
	}

	// Create output file:
   FILE* Out = fopen(outputFileName, "w");
   
   // Boolean flags for controlling execution, based on the parameter(s) we
   // received on the command-line:
   bool testGet = false, testFind = false, testSum = false;
   bool randomize = false;
   
   if ( argc == 1 ) {  // run all tests and randomize
      testGet = true;
      testFind = true;
      testSum = true;
      randomize = true;
   }
   else if ( (argc == 2) && (strcmp(argv[1], "-repeat") == 0) ) { // run all tests, do not randomize
      testGet = true;
      testFind = true;
      testSum = true;
   }
   else {  // could be 2 or 3 arguments
      // Determine which tests are to be performed from argv[1]:
      char* modeSelector = argv[1];
      if ( strcmp(modeSelector, "-all") == 0 ) {
		   testGet = testFind = testSum = true;
	   }
	   else if ( strcmp(modeSelector, "-get") == 0 ) {
		   testGet = true;
	   }
	   else if ( strcmp(modeSelector, "-find") == 0 ) {
		   testFind = true;
	   }
	   else if ( strcmp(modeSelector, "-sum") == 0 ) {
		   testSum = true;
	   }
	   else {
	   	printf("Unrecognized mode selector:  %s\n", modeSelector);
	   	exit(2);
	   }
      if ( argc == 2 ) {
         randomize = true;
      }
      if ( (argc == 3) && (strcmp(argv[2], "-repeat") == 0) ) {
         randomize = false;
      }
      else if ( argc == 3 ) {
	   	printf("Unrecognized option:  %s\n", argv[2]);
	   	exit(3);
      }
   }
	
   // In regular mode, we will read a seed value from a file (written by
   // a previous run in randomization mode), and generate the same test
   // data that was used in that previous run.
   unsigned int seed = 0;
   if ( randomize ) {
      seed = time(NULL);
      FILE* fp = fopen("seed.txt", "w");
      fprintf(fp, "%u\n", seed);
      fclose(fp);
   }
   else {
      FILE* fp = fopen("seed.txt", "r");
      if ( fp == NULL ) {
			fprintf(stdout, "Could not find seed file.\n");
			fprintf(stdout, "You can only use -repeat if a seed file already exists.\n");
			exit(4);
		}
      fscanf(fp, "%u", &seed);
      fclose(fp);
   }
   
   // Seed the random generator:
   srand(seed);

   // Generate test data block:   
   uint8_t* dataBlock = genDataBlock( BLOCK_LENGTH );
   
   // Write memory block hex dump to file so students can see it
   FILE* Dump = fopen(dataBlockFileName, "w");
   writeDataBlock(Dump, dataBlock, BLOCK_LENGTH);
   fclose(Dump);

   // Variables to hold scores from individual tests:
   uint32_t scoreGetBytes = 0; 
   uint32_t scoreFindOccurrencesOfByte = 0;
   uint32_t scoreSumValuesAtOffsets = 0;
   
   // Tests that do (should) not modify the content of the data block:
   if ( testGet ) {
		fprintf(Out, "Running test of getBytesAtOffset().\n");
      scoreGetBytes = testGetBytesAtOffset(dataBlock, BLOCK_LENGTH);
	}
   if ( testFind ) {
		fprintf(Out, "Running test of findOccurrencesOfByte().\n");
      scoreFindOccurrencesOfByte = testFindOccurrencesOfByte(dataBlock, BLOCK_LENGTH);
   }
   if ( testSum ) {
		fprintf(Out, "Running test of sumValuesAtOffsets().\n");
      scoreSumValuesAtOffsets = testSumValuesAtOffsets(dataBlock, BLOCK_LENGTH);
	}
   
   // Summarize results:
   fprintf(Out, "\n");
   fprintf(Out, ">>Scores from testing<<\n");
   fprintf(Out, "1 >> Score for getBytesAtOffset:       %3"PRIu32" / 100\n", scoreGetBytes);
   fprintf(Out, "2 >> Score for findOccurrencesOfByte:  %3"PRIu32" / 100\n", scoreFindOccurrencesOfByte);
   fprintf(Out, "3 >> Score for sumValuesAtOffsets:     %3"PRIu32" / 100\n", scoreSumValuesAtOffsets);

   free(dataBlock);
   fclose(Out);
      
   return 0;
}

