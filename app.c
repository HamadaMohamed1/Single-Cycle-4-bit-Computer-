/*
 * app.c
 *
 *  Created on: Nov 4, 2023
 *      Author: hamada
 */

#include "app.h"


// Define the registers and their corresponding machine codes
typedef struct {
  char* name;
  unsigned char code;
  char* operand;
} Register;

Register registers[] = {
  {"R0", 0x00 , "0X0"},
  {"R1", 0x01 , "0X1"},
  {"R2", 0x02 , "0X2"},
  {"R3", 0x03 , "0X3"},
};

// Define the instructions and their corresponding machine codes
typedef struct {
  char* name;
  unsigned char code;
} Instruction;

Instruction instructions[] = {
  {"MOV", 0x00},
  {"NOP", 0x00},
  {"INC", 0x01},
  {"ADD", 0x02},
  {"SUB", 0x05},
  {"DEC", 0x06},
  {"AND", 0x08},
  {"OR",  0x0A},
  {"XOR", 0x0C},//0000 1100
  {"NOT", 0x0F},
  {"LD",  0x10},
  {"ST",  0x20},
  {"SHL", 0x39},
  {"LDI", 0x32},
  {"ADI", 0x32},
  {"SUBI",0x35}//0011 0101
};

// Function to find the machine code of a register
unsigned char findRegisterCode(char* name) {
  for (char i = 0; i < sizeof(registers) / sizeof(Register); i++)
  {
      if (strcmp(name, registers[i].name) == 0) {
          return registers[i].code;
      }
  }

  for (char i = 0; i < sizeof(registers) / sizeof(Register); i++)
  {
       if (strcmp(name, registers[i].operand) == 0) {
           return registers[i].code;
       }
  }

  return -1; // Return -1 if the register is not found
}

// Function to find the machine code of an instruction
unsigned char findInstructionCode(char* name) {
  for (char i = 0; i < sizeof(instructions) / sizeof(Instruction); i++) {
      if (strcmp(name, instructions[i].name) == 0) {
          return instructions[i].code;
      }
  }
  return -1; // Return -1 if the instruction is not found
}


pin_config_t RW_pin;
pin_config_t CLK_pin;

int main(void)
{
	components_init();
	uart_initialize();
	unsigned char address_counter =0;

	while(1)
	{


	  char instruction[14];
	  char* operation;
	  char* reg1;
	  char* reg2;
	  char* reg3 = NULL; // This will be NULL if the instruction has only 2 registers

	  //printf("Enter an assembly instruction: ");
	  //fgets(instruction, sizeof(instruction), stdin);
		  uart_receive_string(instruction);

	  // Remove the newline character at the end of the string
	  instruction[strcspn(instruction, "\n")] = '\0';

	  // Split the instruction into parts
	  operation = strtok(instruction, " ");
	  reg1 = strtok(NULL, ",");
	  reg2 = strtok(NULL, ",");
	  reg3 = strtok(NULL, ",");

	 /* printf("Operation: %s\n", operation);
	  printf("Destnation Register : %s\n", reg1);
	  printf("Source Register 1 : %s\n", reg2);
	*/
	  // If the instruction has 3 registers, print the third register
	/* if (reg3 != NULL) {
	      printf("Source Register 2 : %s\n", reg3);
	  }
	*/
	  // Convert the operation and registers to machine code
	  unsigned char operationCode = findInstructionCode(operation);
	  unsigned char reg1Code = findRegisterCode(reg1);
	  unsigned char reg2Code = findRegisterCode(reg2);
	  unsigned char reg3Code = reg3 != NULL ? findRegisterCode(reg3) : 0;


	  //printf("Operation Code: 0x%X\n", operationCode);
	  //printf("Destnation Register  Code: 0x%X\n", reg1Code);
	  //printf("Source Register 1 Code : 0x%X\n", reg2Code);

	  // If the instruction has 3 registers, print the third register code


	  gpio_port_write_logic(PORTA_INDEX,operationCode>>2); // 0B0000 0011

	  if(0x39 == operationCode)
	  {
		  reg3Code = reg2Code;
		  unsigned char value ;
		  value = (operationCode<<6)|(reg1Code<<4)|(reg2Code<<2);
		  value = value|(reg3Code);
		  //port a    port b
		  //0000 1100 10xx xxxx
		  gpio_port_write_logic(PORTB_INDEX,value);
	  }
	  else if(!strcmp("LDI",operation))
	  {
		  reg3Code =reg2Code;
		  reg2Code = reg1Code;
		  unsigned char value ;
		  value = (operationCode<<6)|(reg1Code<<4)|(reg2Code<<2);
		  value = value|(reg3Code);
		  //port a    port b
		  //0000 1100 10xx xxxx
		  gpio_port_write_logic(PORTB_INDEX,value);
	  }
	  else if(!strcmp("NOP",operation))
	  {

		  reg1Code = 0x00;
		  reg2Code = 0x00;
		  reg3Code = 0x00;
		  unsigned char value ;
		  value = (operationCode<<6)|(reg1Code<<4)|(reg2Code<<2);
		  value = value|(reg3Code);
		  //port a    port b
		  //0000 1100 10xx xxxx
		  gpio_port_write_logic(PORTB_INDEX,value);
	  }
	  else if(0x20 == operationCode)
	  {
		  reg3Code =reg2Code;
		  reg2Code = reg1Code;
		  unsigned char value ;
		  value = (operationCode<<6)|(reg1Code<<4)|(reg2Code<<2);
		  value = value|(reg3Code);
		  //port a    port b
		  //0000 1100 10xx xxxx
		  gpio_port_write_logic(PORTB_INDEX,value);
	  }
	  else
	  {
		  unsigned char value ;
		  value = (operationCode<<6)|(reg1Code<<4)|(reg2Code<<2);
		  if (reg3 != NULL) {
			  //printf("Source Register 2 Code: 0x%X\n", reg3Code);
			  value = value|(reg3Code);
		  }			   //port a    port b
					  //0000 1100 10xx xxxx
		  gpio_port_write_logic(PORTB_INDEX,value);
	  }











	  _delay_ms(200);
	  gpio_port_write_logic(PORTC_INDEX,address_counter);
	  ++address_counter;
	  gpio_pin_write_logic(&RW_pin , GPIO_LOW);
	  gpio_pin_write_logic(&CLK_pin , GPIO_HIGH);
	  _delay_ms(1000);
	  gpio_pin_write_logic(&CLK_pin , GPIO_LOW);
	  gpio_pin_write_logic(&RW_pin , GPIO_HIGH);


	}























	return 0 ;
}

void components_init(void)
{
	gpio_port_direction_intialize(PORTA_INDEX,0xff);
	gpio_port_direction_intialize(PORTB_INDEX,0xff);
	gpio_port_direction_intialize(PORTC_INDEX,0xff);

	{
		CLK_pin.direction = GPIO_DIRECTION_OUTPUT;
		CLK_pin.port = PORTD_INDEX;
		CLK_pin.pin = GPIO_PIN6;
		CLK_pin.logic = GPIO_LOW;
		gpio_pin_intialize(&CLK_pin);
	}
	{
		RW_pin.direction = GPIO_DIRECTION_OUTPUT;
		RW_pin.port = PORTD_INDEX;
		RW_pin.pin = GPIO_PIN7;
		RW_pin.logic = GPIO_HIGH;
		gpio_pin_intialize(&RW_pin);
	}
}

