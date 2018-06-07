#pragma once

#include <stdexcept>

using std::exception;

class DisassembleException: public exception
{
public:
	DisassembleException();
	DisassembleException(const char * message);
	~DisassembleException();
};

