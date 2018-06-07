#pragma once

#include "Format.h"
#include <stdint.h>

class J_Format: public Format
{
public:
	J_Format();
	~J_Format();
	string toText(uint32_t code, int address);
};

