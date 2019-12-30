#ifndef HEXM_H
#define HEXM_H

#define ALLOCATE 		0x00
#define SET_VINDEX 		0x01
#define ADDITION 		0x02
#define INPUT			0x03
#define OUTPUT			0x04

typedef struct Instruction {
	unsigned short int interrupt;
	unsigned short int arg;
	struct Instruction *next;
	struct Instruction *prev;
}Instruction;

typedef struct InstructionList {
	Instruction *root;
}InstructionList;

typedef struct Program {
	InstructionList *list;
	unsigned short int *variables;
	unsigned short int vlen;
	unsigned short int vindex;
}Program;

Instruction *init_instruction(unsigned short int, unsigned short int, Instruction *, Instruction *);

InstructionList *init_instructionlist(Instruction *);

Program *init_program(InstructionList *);

Program *parse_stream(FILE *);

Instruction *parse_string(char *);

int core(Program *);

#endif // HEXM_H
