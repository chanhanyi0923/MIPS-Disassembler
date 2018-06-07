#include <iostream>
#include <fstream>

#include "BinaryData.h"
#include "DisassembleException.h"

R_Format Code::R;
I_Format Code::I;
J_Format Code::J;

int main(int argc, char *argv[])
{
	if (argc != 4) {
		std::cerr << "Invalid number of arguments." << std::endl;
		return 1;
	}

	const char *input_filename = argv[1];
	const char *input_type = argv[2];
	const char *output_filename = argv[3];

	BinaryData data;

	if (string(input_type) == string("-bin")) {
		data.setInputType(BinaryData::bin);
	} else if (string(input_type) == string("-coe")) {
		data.setInputType(BinaryData::coe);
	} else {
		std::cerr << "Unknown output type." << std::endl;
		return 1;
	}

	std::fstream input, output;

	input.exceptions(std::fstream::badbit);
	output.exceptions(std::fstream::badbit);

	try {
		input.open(input_filename, std::fstream::in | std::fstream::binary);
		if (!input) {
			throw std::system_error{ errno, std::generic_category() };
		}
		input >> data;
	} catch (DisassembleException const & e) {
		std::cerr << e.what() << std::endl;
		return 1;
	} catch (std::system_error const & e) {
		std::cerr << "Input: " << e.code() << " - " << e.what() << std::endl;
		return 1;
	} catch (std::exception const & e) {
		std::cerr << "Input: " << e.what() << std::endl;
		return 1;
	}

	input.close();

	try {
		data.process();
	} catch (DisassembleException const & e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	try {
		output.open(output_filename, std::fstream::out | std::fstream::binary);
		if (!output) {
			throw std::system_error{ errno, std::generic_category() };
		}
		output << data;
	} catch (DisassembleException const & e) {
		std::cerr << e.what() << std::endl;
		return 1;
	} catch (std::system_error const & e) {
		std::cerr << "Output: " << e.code() << " - " << e.what() << std::endl;
		return 1;
	} catch (std::exception const & e) {
		std::cerr << "Output: " << e.what() << std::endl;
		return 1;
	}

	output.close();

	return 0;
}
