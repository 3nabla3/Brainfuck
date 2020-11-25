#include <stdlib.h>
#include "brainfuck.h"

/* 
>++++++++[<+++++++++>-]<.>++++[<+++++++>-]
<+.+++++++..+++.>>++++++[<+++++++>-]<++.------------.
>++++++[<+++++++++>-]<+.<.+++.------.--------.>>>++++[<++++++++>-]<+. 
*/

int main(int argc, char const *argv[]) {
  // arg1: bf code
  // arg2: datasize
  char code[256] = {0};
  char c[4] = {0};
  int i = 0;

  if (argc == 1 || argc > 3)
  {
    printf("brainfuck [file] (datasize)\n");
    return 0;
  }

  // give the code to the bf interpreter
  FILE* fptr = fopen(argv[1], "r");
  if (fptr != NULL)
  {
    while(fgets(c, 2, fptr)!=NULL)
    {
      // printf("data[%d]:%s\n", i, c);
      code[i] = *c;
      i++;
    }
  }
  else
  {
    printf("File \"%s\" does not exist!\n", argv[1]);
    exit(1);
  }
  // printf("The code is:\n%s\n", code);s
  return brainfuck(code);
}
