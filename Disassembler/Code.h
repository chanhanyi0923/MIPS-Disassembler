#pragma once

#include <stdint.h>
#include <string>

#include "R_Format.h"
#include "I_Format.h"
#include "J_Format.h"

using std::string;

class Code
{
	static R_Format R;
	static I_Format I;
	static J_Format J;

	uint32_t data;
	int address;
public:
	Code();
	Code(uint32_t d, int addr);
	~Code();
	uint32_t get() const;
	int getAddress() const;
	string toText() const;
};

