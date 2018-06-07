#pragma once

#include <map>
#include <string>
#include <vector>
#include <stdint.h>

#include "Format.h"
#include "Instruction.h"

using std::map;
using std::string;
using std::vector;

class I_Format: public Format
{
public:
	I_Format();
	~I_Format();
	string toText(uint32_t code, int address);
};

