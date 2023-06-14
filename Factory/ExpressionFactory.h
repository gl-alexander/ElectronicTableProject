#pragma once
#include "../Expression/BinaryExpression.h"
#include "../Expression/SimpleExpression.h"
#include "../Utilities/MyString.h"
#include "../Utilities/Validation/Validation.h"
#include <sstream>

class Table;

using FunctionPointer = const Cell* (Table::*)(size_t row, size_t col) const;


class ExpressionFactory
{
	FunctionPointer getCellFunction = nullptr;
	Table* obj;

	static ExpressionFactory* instance;
	ExpressionFactory();
	const Cell* getCell(const StringView& str) const;
public:
	ExpressionFactory(const ExpressionFactory& other) = delete;
	ExpressionFactory& operator=(const ExpressionFactory& other) = delete;
	static void freeInstance();
	static ExpressionFactory* getInstance();

	void passGetCellFunction(FunctionPointer func, Table* obj);

	Expression* createExpression(const StringView& str) const;
	
};

