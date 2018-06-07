#pragma once

#include <map>
#include <string>
#include <vector>
#include <stdint.h>

#include "Instruction.h"

using std::multimap;
using std::map;
using std::string;
using std::vector;


class Format
{
protected:
	multimap<uint8_t, string> opcode_table;
	map<uint8_t, string> funct_table;
	map<string, Instruction> instructions;
	void buildOpcodeTable();
	void buildFunctTable();
public:
	Format();
	~Format();
	bool operationIn(const string &operation);
	bool opcodeIn(const uint8_t opcode);
	bool functIn(const uint8_t funct);
};

