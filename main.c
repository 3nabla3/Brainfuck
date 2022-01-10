#include <stdlib.h>
#include "brainfuck.h"

int main(int argc, char const *argv[]) {
  // give 32MB of space for the code
  char code[1024 * 32] = {0};

  if (argc == 1 || argc > 2)
  {
    printf("Usage: ./brainfuck [file]\n");
    return 0;
  }

  // read code from file and give it to the bf interpreter
  FILE* fptr = fopen(argv[1], "r");
  if (fptr != NULL)
  {
    char temp[2]; // array that will contain a single char
    int i = 0;	  // index of where the char will be written
    // read file character by character and copy it into the "code" array
    while(fgets(temp, 2, fptr) != NULL)
    {
      PrintDebug("code[%d]: %s\n", i, temp);
      code[i++] = *temp;
    }
  }
  else
  {
    printf("File \"%s\" does not exist!\n", argv[1]);
    return 1;
  }

  // run the code
  PrintDebug("Code is:\n");
  PrintDebug("====================================\n");
  PrintDebug("%s\n", code);
  PrintDebug("====================================\n\n");
  
  brainfuck(code);
  
  return 0;
}
