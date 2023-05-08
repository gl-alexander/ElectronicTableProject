#pragma once
#include "Cell.h"
#include <fstream>


class Row
{
	Cell* _cells = nullptr;
	size_t _cellCount = 0;

	void copyFrom(const Row& other);
	void free();
	void moveFrom(Row&& other);

	
public:
	Row() = default;
	Row(const Row& other);
	Row& operator=(const Row& other);
	~Row();

	Row(Row&& other);
	Row& operator=(Row&& other);

	void readRowFromFile(std::ifstream& ifs);

	Cell& operator[](int ind);
	const Cell& operator[](int ind) const;
};

