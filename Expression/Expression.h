#pragma once
#include "../Cells/Cell.h"

class Expression
{
public:
	virtual ~Expression() = default;
	virtual Expression* clone() const = 0;
	virtual double evaluate() const = 0;
};

