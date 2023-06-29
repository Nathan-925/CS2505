#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
   
   if ( argc != 2 ) {
      printf("Invocation: q1 <PID>\n");
      return 1;
   }
   
   int limit = (int)(*(int*)argv[1]);
   int check = limit;
   int addend = limit & 0xFF;
   
   for (int iter = 1; iter <= limit; iter++) {
      check = (check & 0x0FFFFFFF );
      check += addend; 
   }
   return 0;
}
