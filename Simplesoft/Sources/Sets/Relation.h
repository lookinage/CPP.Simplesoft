#pragma once

#include "..\Base.h"

template<typename TInput, typename TOutput>
class Relation
{
	TInput _input;
	TOutput _output;

public:

	Relation() : _input(), _output() { }
	Relation(TInput const input, TOutput const output) : _input(input), _output(output) { }

	TInput GetInput() const { return _input; }
	TOutput GetOutput() const { return _output; }
	void SetInput(TInput const& input)  { _input = input; }
	void SetOutput(TInput const& output)  { _output = output; }
};