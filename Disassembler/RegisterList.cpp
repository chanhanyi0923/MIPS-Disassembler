#include "RegisterList.h"

#include "DisassembleException.h"

string RegisterList::getRegisterName(int index)
{
	if (index >= 0 && index <= 31) {
		return list_1[index];
	} else {
		throw DisassembleException("Invalid index of register.");
	}
}

