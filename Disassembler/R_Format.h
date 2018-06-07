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

class R_Format: public Format
{
public:
	R_Format();
	~R_Format();
	string toText(uint32_t code, int address);
};

