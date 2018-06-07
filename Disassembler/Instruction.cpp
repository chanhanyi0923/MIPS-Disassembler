#include "Instruction.h"

#include <stdint.h>

Instruction::Instruction()
{
}


Instruction::~Instruction()
{
}


Instruction::Instruction(uint8_t o, uint8_t f, OperandType t0, OperandType t1, OperandType t2)
{
	opcode = o;
	funct = f;
	type[0] = t0;
	type[1] = t1;
	type[2] = t2;
}


int Instruction::getOperandSize() const
{
	// calculate size of operands
	int size = 0;
	for (int i = 0; i < 3; i++) {
		if (type[i] == none) {
			break;
		}
		size = i + 1;
	}
	return size;
}

