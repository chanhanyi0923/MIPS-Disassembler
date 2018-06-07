#include "Code.h"

#include <string>
#include <sstream>
#include <boost/format.hpp>

#include "DisassembleException.h"

using std::string;
using std::stringstream;

Code::Code() : data(0), address(0)
{
}


Code::Code(uint32_t d, int addr) : data(d), address(addr)
{
}


Code::~Code()
{
}


uint32_t Code::get() const
{
	return data;
}


int Code::getAddress() const
{
	return address;
}


string Code::toText() const
{
	uint8_t opcode = data >> 26;

	stringstream buffer;
	buffer << boost::format("L%08X: ") % (address >> 2);

	if (opcode == 0) {
		// R format
		buffer << R.toText(data, address);
	} else if (I.opcodeIn(opcode)) {
		// I format
		buffer << I.toText(data, address);
	} else if (J.opcodeIn(opcode)) {
		// J format
		buffer << J.toText(data, address);
	} else {
		throw DisassembleException("Invalid operation code.");
	}

	buffer << ";";

	return buffer.str();
}

