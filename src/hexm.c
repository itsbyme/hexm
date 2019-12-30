#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <hexm.h>

int core(Program *program)
{
	if (program == NULL) {
		return 0;
	}
	Instruction *instruction = program->list->root;
	while (instruction) {
		switch (instruction->interrupt) {
			case ALLOCATE:
				if (program->vlen == 0xFFFF) {
					fprintf(stderr, "Memory Error: too many variables(%#x)\n", program->vlen);
					exit(EXIT_FAILURE);
				}
				program->variables = realloc(program->variables, program->vlen * sizeof(unsigned short int) + sizeof(unsigned short int));
				if (!program->variables) {
					fprintf(stderr, "Memory Error: not enought memory(%#x variables allocated\n", program->vlen);
					exit(EXIT_FAILURE);
				}
				program->variables[program->vlen] = instruction->arg;
				program->vlen++;
				break;
			case SET_VINDEX:
				if (instruction->arg >= program->vlen) {
					fprintf(stderr, "Index Error: variable with index %#x does not exists\n", instruction->arg);
				   exit(EXIT_FAILURE);
				}
				program->vindex = instruction->arg;
				break;
			case ADDITION:
				program->variables[program->vindex] += instruction->arg;
				break;
			case INPUT:
				scanf("%x", program->variables[program->vindex]);
				break;
			case OUTPUT:
				printf("%c", program->variables[program->vindex]);
				break;
			default:
				fprintf(stderr, "Intsruction Error: unknown instruction \"%#x\"\n", instruction->interrupt);
				return EXIT_FAILURE;
		}
		instruction = instruction->next;
	}
	free(program->variables);
	return EXIT_SUCCESS;
}

Program *parse_stream(FILE *file)
{
	Instruction *instruction = NULL;
	InstructionList *list = init_instructionlist(instruction);
	Program *program = init_program(list);
	char buf[100];
	while (fgets(buf, sizeof(buf), file) != NULL) {
		if (!instruction) { 
			instruction = parse_string(buf);
			program->list->root = instruction;
		} else {
			instruction->next = parse_string(buf);
			instruction->next->prev = instruction;
			instruction = instruction->next;
		}
	}
	return program;
}

Instruction *parse_string(char *buf)
{
	unsigned short int interrupt, arg;
	sscanf(buf, "%hx %hx", &interrupt, &arg);
	return init_instruction(interrupt, arg, NULL, NULL);
}

Instruction *init_instruction(unsigned short int interrupt, unsigned short int arg, Instruction *next, Instruction *prev)
{
	Instruction *instruction = malloc(sizeof(Instruction));
	instruction->interrupt = interrupt;
	instruction->arg = arg;
	instruction->next = next;
	instruction->prev = prev;
	return instruction;
}

InstructionList *init_instructionlist(Instruction *root)
{
	InstructionList *list = malloc(sizeof(InstructionList));
	list->root = root;
	return list;
}

Program *init_program(InstructionList *list)
{
	Program *program = malloc(sizeof(Program));
	program->list = list;
	program->vlen = 0;
	program->vindex = 0;
	return program;
}
