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
// interfere with the normal operation of the grading code.
//
// Nathaniel Dunlap
// nathan925
#include "PtrFuncs.h"
#include <stdbool.h>
#include <string.h>

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
                       uint16_t Offset, uint8_t nBytes) {
   //Loop through all the bytes and add i to the pointer to move to the selected address
   for(int i = 0; i < nBytes; i++)
      *(pDest+i) = *(baseAddr+Offset+i);
} //getBytesAtOffset




/**  Uses pointer-based logic to search a specified portion of a region of
 *   memory for occurrences of a specified one-byte value.
 *
 *   Pre:  baseAddr points to the first byte of the memory region
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
uint8_t findOccurrencesOfByte( uint16_t* const pOffsets, const uint8_t* const baseAddr,
                                                            uint32_t Length, uint8_t Byte) {
   uint8_t cnt = 0;
   //Check each position for Byte, if it is found add the value of i to pOffsets and increment cnt
   for(int i = 0; i < Length; i++)
      if(*(baseAddr+i) == Byte)
         *(pOffsets + cnt++) = i;
   return cnt;
} //findOccurrencesOfByte




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
                                          uint32_t Offset2, Sign Sgn, uint8_t nBytes) {
   //The value of Sgn does not affect this function and is ignored
   uint16_t byteSum = 0;
   for(int i = 0; i < nBytes; i++){
      //the two next bytes are added within a 2 byte integer
      byteSum += *((uint8_t*)baseAddr+Offset1+i) + *((uint8_t*)baseAddr+Offset2+i);
      //the smaller part of the 2 byte integer is copied to the output
      *((uint8_t*)pDest+i) = *((uint8_t*)&byteSum);
      //the smaller byte is discarded
      byteSum = byteSum>>8;
   }
   return true;
} //sumValuesAtOffsets
