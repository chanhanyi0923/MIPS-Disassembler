#include "I_Format.h"

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>
#include <boost/format.hpp>

#include "RegisterList.h"
#include "Instruction.h"

using std::map;
using std::string;
using std::stringstream;
using std::pair;


I_Format::I_Format()
{
	// format: rt, imm(rs)
	instructions[string("lw")] = Instruction(0x23, 0, Instruction::rt, Instruction::imm_rs, Instruction::none);
	instructions[string("lb")] = Instruction(0x20, 0, Instruction::rt, Instruction::imm_rs, Instruction::none);
	instructions[string("lbu")] = Instruction(0x24, 0, Instruction::rt, Instruction::imm_rs, Instruction::none);
	instructions[string("lh")] = Instruction(0x21, 0, Instruction::rt, Instruction::imm_rs, Instruction::none);
	instructions[string("lhu")] = Instruction(0x25, 0, Instruction::rt, Instruction::imm_rs, Instruction::none);
	instructions[string("sw")] = Instruction(0x2B, 0, Instruction::rt, Instruction::imm_rs, Instruction::none);
	instructions[string("sb")] = Instruction(0x28, 0, Instruction::rt, Instruction::imm_rs, Instruction::none);
	instructions[string("sh")] = Instruction(0x29, 0, Instruction::rt, Instruction::imm_rs, Instruction::none);

	// format: rt, rs, imm
	instructions[string("addi")] = Instruction(0x8, 0, Instruction::rt, Instruction::rs, Instruction::imm);
	instructions[string("addiu")] = Instruction(0x9, 0, Instruction::rt, Instruction::rs, Instruction::imm);
	instructions[string("andi")] = Instruction(0xC, 0, Instruction::rt, Instruction::rs, Instruction::imm);
	instructions[string("ori")] = Instruction(0xD, 0, Instruction::rt, Instruction::rs, Instruction::imm);
	instructions[string("xori")] = Instruction(0xE, 0, Instruction::rt, Instruction::rs, Instruction::imm);
	instructions[string("slti")] = Instruction(0xA, 0, Instruction::rt, Instruction::rs, Instruction::imm);
	instructions[string("sltiu")] = Instruction(0xB, 0, Instruction::rt, Instruction::rs, Instruction::imm);

	// format: rt, imm
	instructions[string("lui")] = Instruction(0xF, 0, Instruction::rt, Instruction::imm, Instruction::none);

	// format: rs, rt, label
	instructions[string("beq")] = Instruction(0x4, 0, Instruction::rs, Instruction::rt, Instruction::label);
	instructions[string("bne")] = Instruction(0x5, 0, Instruction::rs, Instruction::rt, Instruction::label);

	// format: rs, label
	instructions[string("blez")] = Instruction(0x6, 0, Instruction::rs, Instruction::label, Instruction::none);
	instructions[string("bgtz")] = Instruction(0x7, 0, Instruction::rs, Instruction::label, Instruction::none);
	instructions[string("bltz")] = Instruction(0x1, 0, Instruction::rs, Instruction::label, Instruction::none);
	instructions[string("bgez")] = Instruction(0x1, 0, Instruction::rs, Instruction::label, Instruction::none);

	buildOpcodeTable();
}


I_Format::~I_Format()
{
}


string I_Format::toText(uint32_t code, int address)
{
	uint8_t opcode, reg_s, reg_t;
	int16_t immediate;

	opcode = (code >> 26);
	reg_s = (code >> 21) & ((1 << 5) - 1);
	reg_t = (code >> 16) & ((1 << 5) - 1);
	immediate = code & ((1 << 16) - 1);

	const auto & it = opcode_table.find(opcode);
	const string & operation = opcode == 1 ? (reg_t == 1 ? "bgez" : "bltz") : it->second;
	const Instruction & inst = instructions[operation];

	string text(operation);

	int operand_size = inst.getOperandSize();
	for (int i = 0; i < operand_size; i++) {
		if (i > 0) {
			text += ",";
		}

		if (inst.type[i] == Instruction::rs) {
			text += " " + RegisterList::getRegisterName(reg_s);
		} else if (inst.type[i] == Instruction::rt) {
			text += " " + RegisterList::getRegisterName(reg_t);
		} else if (inst.type[i] == Instruction::imm) {
			stringstream buffer;
			buffer << boost::format(" 0x%04x") % immediate;
			text += buffer.str();
		} else if (inst.type[i] == Instruction::imm_rs) {
			stringstream buffer;
			buffer << boost::format(" %d(%s)") % immediate % RegisterList::getRegisterName(reg_s);
			text += buffer.str();
		} else if (inst.type[i] == Instruction::label) {
			stringstream buffer;
			buffer << boost::format(" L%08X") % (immediate + (address >> 2) + 1);
			text += buffer.str();
		}
	}

	return text;
}

