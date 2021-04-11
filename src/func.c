#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "func.h"


int sc_memoryInit() {


	for (int i = 0; i < 100; i++) {
		array[i] = 0;
	}
  return 0;
}

int sc_memorySet(int address, int value) {

	if (address > SIZE_ARRAY || address < 0) {
		sc_regSet(EXIT_RANGE_MEMORY, 1);
		printf("Выход за границу памяти\n");
		return EXIT_MEMORY;
	}

	array[address] = value;

	return 0;
}

int sc_memoryGet(int address, int* value) {

	if (address > SIZE_ARRAY || address < 0) {
		printf("Выход за границу памяти\n");
		sc_regSet(EXIT_RANGE_MEMORY, 1);
		return EXIT_MEMORY; 
	}

	*value = array[address];

	return 0;

}

int sc_memorySave(char* filename) {

	FILE* file;

	if((file = fopen(filename, "wb")) ==  NULL) {
		return ERROR_WB_FILE;
	}

	fwrite(array, sizeof(int), SIZE_ARRAY, file);
	fclose(file);

	return 0;

}

int sc_memoryLoad(char* filename) {

	FILE* file;

	if((file = fopen(filename, "rb")) ==  NULL) {
		return ERROR_RB_FILE;
	}

	if(fread(array, sizeof(int), SIZE_ARRAY, file) != SIZE_ARRAY) {
		if (feof(file))
			return READ_ERROR;
		else
			return ERROR_FILE;
	}
	
	fclose(file);

	return 0;
}

int sc_regInit() {
	register_flags = 0;

	return 0;
}

int sc_regSet(int registr, int value) {

	if (((value == 1) || (value == 0)) == false) {
		return ERROR_VALUE; 
	}

	if (((registr == OVERFLOW || registr == DIVISION_BY_ZERO || registr == EXIT_RANGE_MEMORY || registr == IGNORE_CLOCK_PULSES || registr == INVALID_COMMAND_SPECIFIED)) == false) {
		return ERROR_REGISTER;
	}

	if (value == 1) {
		register_flags = register_flags | registr;
	}
	else if (value == 0){
		register_flags = register_flags & (~registr);
	}

	return 0;

}

int sc_regGet(int registr, int* value) {

	if (((registr == OVERFLOW || registr == DIVISION_BY_ZERO || registr == EXIT_RANGE_MEMORY || registr == IGNORE_CLOCK_PULSES || registr == INVALID_COMMAND_SPECIFIED)) == false)
	return ERROR_REGISTER;

        if ((register_flags & registr) != 0) 
          *value = 1;
        else
          *value = 0;

        return 0;
}

int sc_commandEncode(int command, int operand, int* value) {
  if (command < 0x10 || (command > 0x11 && command < 0x20) ||
      (command > 0x21 && command < 0x30) ||
      (command > 0x33 && command < 0x40) ||
      (command > 0x43 && command < 0x51) || command > 0x76)
    return ERROR_COMMAND;

  if (operand > 0x7F || operand < 0x0) 
  	return ERROR_OPERAND;

  *value = (command << 7) | operand;

  return 0;
}

int sc_commandDecode(int value, int* command, int* operand) {

	int command_temp, operand_temp, check;

	check = value & 0x4000;

	if (check != 0)
		return ERROR_NOT_COMMAND;

	command_temp = (value >> 7) & 0x7F; // получаем код операции
	operand_temp = value & 0x7F; // код операнда 

 if (command_temp < 0x10 || (command_temp > 0x11 && command_temp < 0x20) ||
      (command_temp > 0x21 && command_temp < 0x30) ||
      (command_temp > 0x33 && command_temp < 0x40) ||
      (command_temp > 0x43 && command_temp < 0x51) || command_temp > 0x76)
 	return ERROR_COMMAND;

  *command = command_temp;
  *operand = operand_temp;

  return 0;

}