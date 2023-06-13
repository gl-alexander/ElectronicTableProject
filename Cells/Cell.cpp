#include "Cell.h"

Cell::Cell(const CellType& type) : _type(type)
{}

const CellType& Cell::getType() const
{
	return _type;
}
