// Test driver for the SqzInteger() function.
// Invoke as:
//             driver [-repeat]
//
// The driver calls a test-case generator, which creates an input file
// containing a fixed number of test cases.  Then, your version of the
// function SqzInteger() is applied to each test case, and the results
// are passed to a check tool.  The check tool uses a reference version
// of the function to compute the correct solution, and compare that to
// the results from your solution.
//
// The grading results are written to a file, results.txt.
//
// You may modify this file as you like, but this version of the file
// will be used in testing your submission.

// Inclusions for Standard Library elements:
#include <stdio.h>       // for Standard I/O functionality
#include <stdlib.h>      // for common Standard functionality
#include <string.h>      // for Standard string library
#include <time.h>        // for Standard time function; used in randomization
#include <inttypes.h>    // for C99 Standard exact width integer types

// Inclusions for "local" elements:
#include "SqzInteger.h"   // declaration of specified function
#include "Generator.h"    // declaration of test case generator
#include "checkAnswer.h"  // declaration of results checker

// The test case generator writes the cases to a file; this is the name
// used for that file:
char* testsFile = "TestCases.txt";

// This function writes output to a file; this is the name of that file:
char* resultsFile = "Results.txt";

// We will expect the longest line in the input file to contain no more
// than 100 characters (which is generous in this case).
const uint32_t MAX_LINE_LENGTH = 101;

int main(int argc, char* argv[]) {
   
   // This program expects the user to supply his/her VT email PID on
   // the command line.  Therefore, it checks for that and exits with
   // a diagnostic message if the number of command line tokens is
   // incorrect:
   if ( argc != 1 && argc != 2) {
      printf("Invocation:  %s [-repeat]\n", argv[0]);
      return 1;
   }
   
   // These will store grading parameters:
   uint32_t nCases     =  0;
   uint32_t ptsPerCase = 10;
   uint32_t totalPts   =  0;
   uint32_t maxPts     =  0;
   uint32_t seed       =  0;
   
   // If -repeat was not specified, generate a random test input file;
   // otherwise, look for the left-over seed file and recreate the
   // earlier test.
   if ( argc == 2 && strcmp(argv[1], "-repeat") == 0 ) {
		FILE* fp = fopen("seed.txt", "r");
		if ( fp == NULL ) {
			printf("Could not find old seed file. Run first w/o -repeat.\n");
			return 2;
		}
		fscanf(fp, "%"SCNu32, &seed);
		fclose(fp);
	}
	else if ( argc == 2 ) {
		printf("Unrecognized option: %s\n", argv[1]);
		return 3;
	}
	else {
		seed = time(NULL);   // randomize data generation with system time
      FILE* fp = fopen("seed.txt", "w");
      fprintf(fp, "%"PRIu32"\n", seed);
      fclose(fp);
	}
	
	// Seed random generator:
   srand(seed);
	
	// Generate test case file:
	nCases = Generate(testsFile);
   
   // Attempt to open the specified input file; exit with a diagnostic
   // if it cannot be opened for reading:   
   FILE* tests = fopen(testsFile, "r");
   if ( tests == NULL ) {
      printf("Could not open input file: %s\n", testsFile);
      printf("You must run first without -repeat.\n");
      return 2; 
   }

   // Attempt to open the specified output file; exit with a diagnostic
   // if it cannot be opened for writing:   
   FILE* results = fopen(resultsFile, "w");
   if ( results == NULL ) {
      printf("Could not open output file: %s\n", resultsFile);
      fclose(tests);
      return 3;
   }
   
   // Set grading variables.
   totalPts   = nCases * ptsPerCase;
   
   char Line[MAX_LINE_LENGTH];         // holds the current input line
   char actionFlag[MAX_LINE_LENGTH];   // holds the current Action
   uint32_t N = 0,                     // holds the integer to be "squeezed"
            squeezedN = 0;             // holds the "squeezed" integer
   
   // The loop uses the read-to-input-failure pattern.  That is, we will
   // attempt to read the next expected input from the file, and then
   // validate that reading, before we attempt to process any data.
   //
   // In the loop test, we take advantage of the fact that fgets() will
   // return NULL If it fails to read any input.  That will force the
   // loop to terminate when the end of the input file is reached.
   while ( fgets(Line, MAX_LINE_LENGTH, tests) != NULL ) {
      
      // Try to read the actionFlag from the input line that was just
      // read into Line; sscanf() will return 0 if nothing was read.
      // In that case, write a diagnostic message, skip the remainder of
      // the loop body and look for another line of input.
      if ( sscanf(Line, "%s", actionFlag) != 1 ) {
         printf("Failed to read an actionFlag value from %s\n", Line);
         continue;
      }
      
      // Try to read an integer value from the input line that was just
      // read into Line.  Here, we encounter one limitation of sscanf();
      // it does not maintain any knowledge of previous calls, so it
      // resumes reading from the beginning of Line.  We could sidestep
      // that issue by reading both the actionFlag and the integer in a
      // single call to sscanf(); but that makes checking the results of
      // the two read operations clumsy.
      //
      // Instead, we take advantage of a C format specifier feature; if
      // we follows the '%' with an asterisk, a value is read and then
      // discarded.
      //
      // In this case we reread the action flag value but don't save it.
      if ( sscanf(Line, "%*s %u", &N) != 1 ) {
         printf("Failed to read an integer value from %s\n", Line);
         continue;
      }
      
      // Determine whether the actionFlag indicates we should squeeze
      // out the even digits, or the odd digits, or that there was
      // something wrong with the actionFlag.
      //
      // strcmp() compares two (C-style) character strings; it returns
      // zero if the strings match, something negative if the first
      // string precedes the second string, and something positive if
      // the first string follows the second string.
      enum ProcessChoice option;
      if ( strcmp(actionFlag, "even") == 0 ) {
         option = EVEN;
      }
      else if ( strcmp(actionFlag, "odd") == 0 ) {
         option = ODD;
      }
      else {
         fprintf(results, "Unrecognized action flag: %s\n", actionFlag);
         continue;
      }
      // Compute the student's answer:
      squeezedN = SqzInteger(N, option);
      
      // Now, check the computed answer:
      if ( checkAnswer(results, N, squeezedN, option) ) {
		  maxPts += ptsPerCase;
	  } 
   }

   // Write the total score to the results file:
   fprintf(results, "Score:  %3"PRIu32" / %3"PRIu32"\n", maxPts, totalPts);
   
   // It's important to explicitly close files when we are finished with
   // them, because:
   //   - the OS needs to know the files are no longer in use 
   //   - output written to a file is buffered and may not actually
   //     reach the file unless it is properly closed
   fclose(tests);
   fclose(results);
   
   // Traditionally, return 0 on successful termination.
   return 0;
}
