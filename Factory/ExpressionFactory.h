#pragma once
#include "../Expression/BinaryExpression.h"
#include "../Expression/SimpleExpression.h"
#include <sstream>

class Table;

class ExpressionFactory
{
	Table& table;
	static ExpressionFactory* instance;
	ExpressionFactory(const Table& table);
public:
	ExpressionFactory(const ExpressionFactory& other) = delete;
	ExpressionFactory& operator=(const ExpressionFactory& other) = delete;
	static void freeInstance();
	static ExpressionFactory* getInstance();

	static Expression* createExpression(std::stringstream& ss);
	
};

