#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#define _DEBUG 0

// wrapper for the printf function
void PrintDebug(const char * format, ... )
{
#if _DEBUG
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
#endif
}

// checks if the command is one of the 6 valid commands
short isValid(char command) {
	char validChars[] = "+-><.,[]";
	for (short i = 0; i < sizeof(validChars) / sizeof(char); i++) {
		if (command == validChars[i])
			return 1;
	}
	return 0;
}

// executes the code starting at the specified mem address
void brainfuck(const char* code_pointer)
{
	// stores the addresses of the brackets to jump to them when looping
	const char* bracket_pointers[16];
	short bracket_depth = 0;
	char command;
	// give 128MB of space for the data
	char data[1024 * 128] = {0};
	// start the data pointer at the middle of the allocated pool
	char *data_pointer = &data[sizeof(data) / 2];
	
	// read a single command from the memory
	while ( (command = *(code_pointer++)) )
	{
		// execute the command only if it is valid
		if (isValid(command))
			PrintDebug("(0x%x) Executing command %c: ", code_pointer, command);
		else
			PrintDebug("(0x%x) Skipped invalid character 0x%x\n", code_pointer, command);

		switch (command) {
			case '+':
				(*data_pointer)++;
				goto printNewValue;

			case '-':
				(*data_pointer)--;
				
			printNewValue:
				PrintDebug("data at location 0x%x is now 0x%x\n", data_pointer, *data_pointer);
				break;

			case '>':
				data_pointer++;
				goto printNewAddress;

			case '<':
				data_pointer--;
				
			printNewAddress:
				PrintDebug("data pointer is now at address 0x%x\n", data_pointer);
				break;

			case '.':
				PrintDebug("printing the character 0x%x at address 0x%x\n", *data_pointer, data_pointer);
				printf("%c", *data_pointer);
				break;

			case ',':
				*data_pointer = getchar();
				PrintDebug("inserted the character 0x%x at address 0x%x\n", *data_pointer, data_pointer);
				break;

			case '[':
				if (*data_pointer)
				{
					bracket_pointers[++bracket_depth] = code_pointer;
					PrintDebug("Entered a loop at depth %d\n", bracket_depth);
				}
				else
				{
					// set the code pointer to the corresponding closing bracket
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
			
		}
	}
}
