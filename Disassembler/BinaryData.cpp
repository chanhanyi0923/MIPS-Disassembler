#include "BinaryData.h"

#include <iostream>
#include <sstream>
#include <regex>
#include <boost/algorithm/string/trim_all.hpp>

#include "DisassembleException.h"
#include "Code.h"

using std::istream;
using std::ostream;
using std::stringstream;
using std::regex;

BinaryData::BinaryData()
{
}


BinaryData::~BinaryData()
{
}


void BinaryData::process()
{
	for (const Code & code : data) {
		try {
			text.push_back(code.toText());
		} catch (DisassembleException const & e) {
			stringstream buffer;
			buffer << "Address " << code.getAddress() << ": " << e.what();
			throw DisassembleException(buffer.str().c_str());
		}
	}
}


void BinaryData::setInputType(BinaryData::InputType t)
{
	input_type = t;
}


istream& operator >> (istream & input, BinaryData& data)
{
	if (data.input_type == BinaryData::coe) {
		data.inputCoe(input);
	} else if (data.input_type == BinaryData::bin) {
		data.inputBin(input);
	}
	return input;
}


ostream& operator << (ostream & output, const BinaryData& data)
{
	for (const string & str : data.text) {
		output << str << std::endl;
	}
	return output;
}


void BinaryData::inputCoe(istream & input)
{
	int radix = 0;

	// process with the first line
	string buffer;
	getline(input, buffer);

	std::smatch m;
	if (regex_search(buffer, m, std::regex("^memory_initialization_radix\\s*=\\s*([0-9]*);$"))) {
		const string & radix_string = m[1];
		if (radix_string == "16") {
			radix = 16;
		} else if (radix_string == "10") {
			radix = 10;
		} else if (radix_string == "2") {
			radix = 2;
		}
	}

	if (radix == 0) {
		throw DisassembleException("Invalid coe file.");
	}

	// process with the second line
	getline(input, buffer, '=');
	buffer = boost::trim_all_copy(buffer);

	if (buffer != "memory_initialization_vector") {
		throw DisassembleException("Invalid coe file.");
	}

	bool end = false;
	for (int address = 0; !end && !input.eof(); address += 4) {
		getline(input, buffer, ',');
		buffer = boost::trim_all_copy(buffer);

		if (buffer.back() == ';') {
			end = true;
			buffer.pop_back();
		}

		uint32_t code = 0;
		for (char c : buffer) {
			int number = 0;
			if (c >= '0' && c <= '9') {
				number = c - '0';
			} else if (c >= 'A' && c <= 'F') {
				number = c - 'A' + 10;
			} else if (c >= 'a' && c <= 'f') {
				number = c - 'a' + 10;
			}

			if (number >= radix) {
				throw DisassembleException("Invalid coe file.");
			}

			code = code * radix + number;
		}
		data.push_back(Code(code, address));
	}

	if (!end) {
		throw DisassembleException("Invalid coe file.");
	}
}


void BinaryData::inputBin(istream & input)
{
	uint8_t buf[4] = { 0 };
	for (int address = 0; input.read((char*)buf, 4) && !input.eof(); address += 4) {
		uint32_t code = ((uint32_t)buf[0] << 24) | ((uint32_t)buf[1] << 16) | ((uint32_t)buf[2] << 8) | ((uint32_t)buf[3]);
		data.push_back(Code(code, address));
	}
}

