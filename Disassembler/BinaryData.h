#pragma once

#include <iostream>
#include <vector>

#include "Code.h"

using std::istream;
using std::ostream;
using std::vector;

class BinaryData
{
public:
	enum InputType { coe, bin };
private:
	InputType input_type;
	vector<Code> data;
	vector<string> text;
public:
	BinaryData();
	~BinaryData();

	void process();
	void setInputType(InputType t);
	friend istream& operator >> (istream & input, BinaryData& data);
	friend ostream& operator << (ostream & output, const BinaryData& data);
	void inputCoe(istream & input);
	void inputBin(istream & input);
};

