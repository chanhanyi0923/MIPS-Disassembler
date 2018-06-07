#include "DisassembleException.h"

#include <stdexcept>

using std::exception;

DisassembleException::DisassembleException()
{
}


DisassembleException::DisassembleException(const char * message) : exception(message)
{
}


DisassembleException::~DisassembleException()
{
}

