#include "FileIO.h"
#include <fstream>
#include <sstream>

void loadData(Warehouse& warehouse, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return; // Файла нет — начинаем с пустой базы
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        int id, qty; double price; std::string name, cat;
        if (std::getline(iss, token, ',') && (id = std::stoi(token)) &&
            std::getline(iss, name, ',') &&
            std::getline(iss, cat, ',') &&
            std::getline(iss, token, ',') && (price = std::stod(token)) &&
            std::getline(iss, token) && (qty = std::stoi(token))) {
            warehouse.addProduct(id, name, cat, price, qty);
        }
    }
}

void saveData(const Warehouse& warehouse, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& p : warehouse.getProducts()) {
        file << p.id << "," << p.name << "," << p.category << "," << p.price << "," << p.quantity << "\n";
    }
}