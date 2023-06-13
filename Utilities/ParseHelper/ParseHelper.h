#pragma once
#include <iostream>
#include <sstream>

static void skipWhiteSpeces(std::istream& is)
{
	while (is.peek() == ' ')
		is.ignore();
}