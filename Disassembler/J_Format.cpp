#include "J_Format.h"

#include <string>
#include <sstream>
#include <boost/format.hpp>

#include "RegisterList.h"
#include "Instruction.h"

using std::string;
using std::stringstream;

J_Format::J_Format()
{
	instructions[string("j")] = Instruction(0x2, 0, Instruction::label, Instruction::none, Instruction::none);
	instructions[string("jal")] = Instruction(0x3, 0, Instruction::label, Instruction::none, Instruction::none);

	buildOpcodeTable();
}


J_Format::~J_Format()
{
}


string J_Format::toText(uint32_t code, int address)
{
	uint8_t opcode;
	uint32_t immediate;

	opcode = (code >> 26);
	immediate = code & ((1 << 26) - 1);

	const auto & it = opcode_table.find(opcode);
	const string & operation = it->second;
	const Instruction & inst = instructions[operation];

	string text(operation);

	stringstream buffer;
	buffer << boost::format(" L%08X") % immediate;
	text += buffer.str();

	return text;
}

