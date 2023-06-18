#include "Save.h"

void Save::execute(Table*& table) const
{
	if (table == nullptr) throw std::logic_error("No table has been opened!");

	table->saveToFile(table->getTableFilePath());
}
