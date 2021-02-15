#include <stdio.h>
#include <stdlib.h>

int disassemble(unsigned char *buffer, int program_counter);

/*
 * Docblock
 */
int main(int argc, char **argv) {

	// Get the file from the first argument in command line
	FILE *file = fopen(argv[1], "rb");

	// If the file doesn't exist, return 1 and print an error
	if (file == NULL) {
		printf("Error: couldn't open %s\n", argv[1]);
		return 1;
	}

	fseek(file, 0L, SEEK_END);
	int file_size = ftell(file);
	fseek(file, 0L, SEEK_SET);

	// Allocate a buffer based on the size of the file
	unsigned char *buffer = malloc(file_size);

	// Read the whole file into the buffer
	// Probably buggy if we're working with big files
	fread(buffer, file_size, 1, file);
	fclose(file);

	int program_counter = 0;
	// Disassemble the file one byte at a times
	while (program_counter < file_size) {
		program_counter += disassemble(buffer, program_counter);
	}

	return 0;
}

/*
 * Docblock
 *
 * @return int Number of bytes disassembled.
 */
int disassemble(unsigned char *buffer, int program_counter) {
	unsigned char *opcode = &buffer[program_counter];
	int opbytes = 1;
	printf("0x%04x   ", program_counter);
	switch (*opcode) {
		case 0x00:
        	printf("NOP");
        	break;
    	default:
        	// We encountered an unknown instruction
        	printf("Unknown Instruction: 0x%02x", *opcode);
        	break;
	}

	printf("\n");
	// Return the number of bytes we disassembled
	return opbytes;
}