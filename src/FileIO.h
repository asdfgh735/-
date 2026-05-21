#pragma once
#include "Warehouse.h"

void loadData(Warehouse& warehouse, const std::string& filename);
void saveData(const Warehouse& warehouse, const std::string& filename);