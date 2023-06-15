#pragma once
#include <iostream>
#include "Cell.h"
#include "../Utilities/MyVector.hpp"
#include "../Expression/Expression.h"


class CellFormula : public Cell
{
	MyString _expressionString;

	Expression* _expression = nullptr; // dynamic data, needs to be managed by CellFormula

	void copyFrom(const CellFormula& other);
	void moveFrom(CellFormula&& other);
	void free();
public:
	CellFormula();
	CellFormula(const CellFormula& other);
	CellFormula(CellFormula&& other);
	CellFormula& operator=(const CellFormula& other);
	CellFormula& operator=(CellFormula&& other);
	~CellFormula();

	CellFormula(const MyString& expression);

	void printCell(size_t len, std::ostream& os) const override;
	void saveToFile(std::ofstream& ofs) const override;

	Cell* clone() const override;

	size_t getLenght() const;


	double evaluate() const override;

	const MyString& getExpressionString() const;

	void setExpressionString(const MyString& value);
	void setExpressionString(MyString&& value);

	void setExpressionObject(Expression* expr);

};

