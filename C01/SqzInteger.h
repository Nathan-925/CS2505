#ifndef SQZINTEGER_H
#define SQZINTEGER_H
#include <inttypes.h>

// DO NOT MODIFY THIS FILE IN ANY WAY!! //

// Rather than use a nondescriptive label, or none at all, we will use
// an enumerated type to make the logic of of the code clearer:
enum ProcessChoice {EVEN, ODD};

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
 */
uint32_t SqzInteger(uint32_t N, enum ProcessChoice Action);

#endif
