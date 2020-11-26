#include <stdlib.h>
#include "brainfuck.h"

int main(int argc, char const *argv[]) {
  char code[2048 * 16] = {0};

  if (argc == 1 || argc > 2)
  {
    printf("brainfuck [file]\n");
    return 0;
  }

  // read code from file and give it to the bf interpreter
  FILE* fptr = fopen(argv[1], "r");
  if (fptr != NULL)
  {
    char temp[4];
    int i = 0;
    // read file character by character and copy it into the "code" array
    while(fgets(temp, 2, fptr)!=NULL)
    {
      PrintDebug("code[%d]: %s\n", i, temp);
      code[i] = *temp;
      i++;
    }
  }
  else
  {
    printf("File \"%s\" does not exist!\n", argv[1]);
    exit(1);
  }

  // run the code
  PrintDebug("Code is: %s\n", code);
  return brainfuck(code);
}
