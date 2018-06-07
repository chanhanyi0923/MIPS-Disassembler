#include "Format.h"

#include <map>
#include <string>

#include "Instruction.h"

using std::string;
using std::map;


Format::Format()
{
}


Format::~Format()
{
}


bool Format::operationIn(const string &operation)
{
	map<string, Instruction>::iterator it = instructions.find(operation);
	return it != instructions.end();
}


bool Format::opcodeIn(const uint8_t opcode)
{
	auto & it = opcode_table.find(opcode);
	return it != opcode_table.end();
}


void Format::buildOpcodeTable()
{
	for (auto & it : instructions) {
		const string & operation = it.first;
		const Instruction & inst = it.second;
		opcode_table.insert(make_pair(inst.opcode, operation));
	}
}


bool Format::functIn(const uint8_t funct)
{
	auto & it = funct_table.find(funct);
	return it != funct_table.end();
}


void Format::buildFunctTable()
{
	for (auto & it : instructions) {
		const string & operation = it.first;
		const Instruction & inst = it.second;
		funct_table.insert(make_pair(inst.funct, operation));
	}
}

