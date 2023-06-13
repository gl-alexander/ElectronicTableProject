#pragma once
#include "Expression.h"

class BinaryExpression : public Expression
{
	Expression* left = nullptr;
	Expression* right = nullptr;
	char operation;
public: 
	BinaryExpression() = default;
	BinaryExpression(Expression* left, Expression* right, char operation);
	double evaluate() const override;
	Expression* clone() const override;
};

