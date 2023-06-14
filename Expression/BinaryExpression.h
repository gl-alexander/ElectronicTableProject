#pragma once
#include "Expression.h"

class BinaryExpression : public Expression
{
	Expression* left = nullptr;
	Expression* right = nullptr;
	char operation;
public: 
	BinaryExpression() = default;
	BinaryExpression(char operation, Expression* left, Expression* right);
	double evaluate() const override;
	Expression* clone() const override;

	~BinaryExpression();
};

