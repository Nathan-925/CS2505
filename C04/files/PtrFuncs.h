#ifndef PTRFUNCS_H
#define PTRFUNCS_H
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

//  DO NOT MODIFY THIS FILE!! //

/**  Uses pointer-based logic to access a specified portion of a region of
 *   memory and copy the corresponding bytes to a supplied array.
 * 
 *   Pre:   pDest points to an array of dimension nBytes + 1, or greater
 *          baseAddr points to the first byte of the memory region
 *          Offset is the location, relative to baseAddr, of the first
 *             relevant byte of the memory region
 *          nBytes is the number of bytes to be copied
 *   Restrictions:
 *      You must use only pointer syntax in accessing the data.
 */
void getBytesAtOffset(uint8_t* const pDest, const uint8_t* const baseAddr, 
		                 uint16_t Offset, uint8_t nBytes);

/**  Uses pointer-based logic to search a specified portion of a region of
 *   memory for occurrences of a specified one-byte value.
 * 
 *   Pre:  pOffsets points to an array of dimension at least 256
 *         baseAddr points to the first byte of the memory region
 *         Length is number of bytes in the memory region
 *         Byte is the value to be found
 *         pOffsets points to an array of dimension at least 256
 *   Post: The offsets of up to 256 occurrences of Byte have been stored
 *            in pOffsets, in ascending order, starting at index 0.
 *            index 0.
 *   Returns:  the number of occurrences of Byte found in the memory region
 *             (which may be less than the actual number of occurrences)
 *   Restrictions:
 *      You must use only pointer syntax in accessing the data.
 */
uint8_t findOccurrencesOfByte(uint16_t* const pOffsets, const uint8_t* const baseAddr,
                                                         uint32_t Length, uint8_t Byte);

/**  Enumerated type used in interface of showValue()
 */
enum _Sign {SIGNED, UNSIGNED};
typedef enum _Sign Sign;

/**  Uses pointer-based logic to compute the sum of two values taken from a region
 *   of memory, using pointer typecasts to control the number of bytes that are
 *   summed, and the way those bytes are interpreted.
 * 
 *   Pre:   pDest points to a memory region large enough to hold the requested value
 *          baseAddr points to the first byte of the memory region
 *          Offset1 is the location, relative to baseAddr, of the first
 *             byte of the first operand
 *          Offset2 is the location, relative to baseAddr, of the second
 *             byte of the first operand
 *          Sign indicates whether the bytes are to be interpreted as representing a
 *             signed or unsigned integer
 *          nByte is the number of bytes to be considered (1, 2, 4, or 8 only)
 *   Post:  *pDest holds the sum of the two specified values
 *   Returns:  false if either of the requested values could not be obtained;
 *             true otherwise
 *   Restrictions:
 *      You must use only pointer syntax in accessing the data.
 */
bool sumValuesAtOffsets(void* pDest, const uint8_t* const baseAddr, uint32_t Offset1,
                                          uint32_t Offset2, Sign Sgn, uint8_t nBytes);

#endif
