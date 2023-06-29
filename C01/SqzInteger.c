// On my honor:
//
// - I have not discussed the C language code in my program with
// anyone other than my instructor or the teaching assistants
// assigned to this course.
//
// - I have not used C language code obtained from another student,
// the Internet, or any other unauthorized source, either modified
// or unmodified.
//
// - If any C language code or documentation used in my program
// was obtained from an authorized source, such as a text book or
// course notes, that has been clearly noted with a proper citation
// in the comments of my program.
//
// - I have not designed this program in such a way as to defeat or
// interfere with the normal operation of the Curator System.
//
// Nathaniel Dunlap

/** CS 2505 Fall 2017:  SqzInteger.c
 * 
 *  Supplied framework for squeezing out digits project.  Your task is to
 *  complete the supplied code to satisfy the posted specification for this
 *  assignment.  
 * 
 *  Student:   Nathaniel Dunlap
 *  PID:       nathan925
 */
#include "SqzInteger.h"

/**  Computes a new integer from N by removing all the even (or odd)
 *   digits from N; if no digits remain, the function computes 0.
 * 
 * Pre:  N is initialized
 *       Action is EVEN or ODD
 * Returns:  integer obtained by removing all EVEN (or all ODD) digits
 *           from N; 0 if no digits of N remain
 *
 * Restrictions:
 *   - uses only its parameters and local automatic variables
 *   - does not make any use of character variables or arrays
 *   - does not read input or write output
 *   - does not use math.h
 */
uint32_t SqzInteger(uint32_t N, enum ProcessChoice Action) {

   uint32_t squeezed = 0; //stores the number that will be output
   uint32_t offset = 1; // stores a power of 10 used to place each digit in the correct spot

   //loop through all digits of N
   while(N > 0){
      //if Action == EVEN and N == EVEN are different, then this digit is NOT a number described by the enum and should be included
      if((Action == EVEN) != (N % 2 == 0)){
         //multiplying the digit by a power of 10 places it in the correct number place
         squeezed += N%10*offset;
         offset *= 10;
      }
      N /= 10;
   }
   
   return squeezed;
}

