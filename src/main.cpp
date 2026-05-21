#include <iostream>
#include <windows.h>
#include "Warehouse.h"
#include "FileIO.h"
#include "Menu.h"

int main() {
    // Включение кириллицы в Windows
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Warehouse warehouse;
    loadData(warehouse, "data/products.txt");

    run(warehouse);
    return 0;
}