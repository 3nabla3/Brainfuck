#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

#define _DEBUG 0

void PrintDebug(const char * format, ... )
{
#if _DEBUG
  printf(format);
#endif
}

int brainfuck(const char* code_pointer)
{
  const char* bracket_pointers[16];
  short bracket_depth = 0;
  char command;
  char data[1024 * 128] = {0};
  unsigned char *data_pointer = &data[512];

  while (command = *(code_pointer++))
  {
    PrintDebug("(%x) Executing command %c: ", code_pointer, command);
    switch (command) {
      case '+':
        (*data_pointer)++;
        PrintDebug("data at location %x is now %x\n", data_pointer, *data_pointer);
        break;

      case '-':
        (*data_pointer)--;
        PrintDebug("data at location %x is now %x\n", data_pointer, *data_pointer);
        break;

      case '>':
        data_pointer++;
        PrintDebug("data pointer is now at address %x\n", data_pointer);
        break;

      case '<':
        data_pointer--;
        PrintDebug("data pointer is now at address %x\n", data_pointer);
        break;

      case '.':
#if _DEBUG == 0
        printf("%c", *data_pointer);
#endif
        PrintDebug("printing the character %x at address %x\n", *data_pointer, data_pointer);
        break;

      case ',':
        *data_pointer = getchar();
        PrintDebug("inserted the character %x at address %x\n", *data_pointer, data_pointer);
        break;

      case '[':
        if (*data_pointer)
        {
          bracket_depth++;
          bracket_pointers[bracket_depth] = code_pointer;
          PrintDebug("Entered a loop at depth %d\n", bracket_depth);
        }
        else
        {
          short brackets_to_close = 1;
          while (brackets_to_close) 
          {
            char temp = *(code_pointer++);
            if (temp == ']') brackets_to_close--;
            else if (temp == '[') brackets_to_close++;
          }
          PrintDebug("Skipped the loop!\n");
        }
        break;

      case ']':
        if (*data_pointer)
        {
          code_pointer = bracket_pointers[bracket_depth];
          PrintDebug("Restarted a loop at depth %d\n", bracket_depth);
        }
        else
        {
          PrintDebug("Exited a loop at depth %d\n", bracket_depth);
          bracket_depth--;
        }
        break;

      default:
        PrintDebug("Skipped character %x\n", command);
    }
  }
  return 0;
}
