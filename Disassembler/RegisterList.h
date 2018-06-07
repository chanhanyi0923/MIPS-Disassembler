#pragma once

#include <string>

using std::string;

namespace RegisterList
{
	const string list_1[32] = {
		"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
		"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
		"$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
		"$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"
	};

	const string list_2[32] = {
		"$0", "$1", "$2", "$3", "$4", "$5", "$6", "$7",
		"$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15",
		"$16", "$17", "$18", "$19", "$20", "$21", "$22", "$23",
		"$24", "$25", "$26", "$27", "$28", "$29", "$30", "$31"
	};

	string getRegisterName(int index);
}

