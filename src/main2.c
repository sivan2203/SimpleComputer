#include <stdio.h>
#include "func.h"

int main() {
  int value;
  int command = 0;
  int operand = 0;
  printf("Инициализация памяти\n");

  sc_memoryInit();

  printf("Задаем значения\n");

  sc_memorySet(1, 13);
  sc_memorySet(15, 58);
  sc_memorySet(67, 3);


  printf("Возвращение значение указанной ячейки памяти\n");

  sc_memoryGet(67, &value);
  printf("value = %d\n", value);

  sc_memorySave("binary.bin");

  printf("Для проверки memoryLoad выполним заново memoryInit и посмотрим ее
  значения\n");

  sc_memoryInit();
  sc_memoryLoad("binary.bin");


  sc_regInit();
  printf("registr_of_flags = %d\n", register_flags);

  printf("произведем выход за границу памяти\n");
  sc_memorySet(134, 5);
  printf("registr_of_flags = %d\n", register_flags);

  sc_regGet(EXIT_RANGE_MEMORY, &value);

  printf("value = %d\n", value);


  printf("до кодировки value = %d\n", value);

  sc_commandEncode(0x32, 13, &value);
  printf("после value = %d\n", value);

  sc_commandDecode(value, &command, &operand);
  printf("command == %x operand == %d\n", command, operand);