#pragma once

#include <stdint.h>

class Instruction
{
public:
	enum OperandType { none, rs, rd, rt, sa, imm, imm_rs, label };
	OperandType type[3];
	uint8_t opcode, funct;

	Instruction();
	~Instruction();
	Instruction(uint8_t o, uint8_t f, OperandType t0, OperandType t1, OperandType t2);
	int getOperandSize() const;
};

