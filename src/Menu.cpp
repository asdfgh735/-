#include "Menu.h"
#include "FileIO.h"
#include <iostream>
#include <limits>
#include <vector>

void printTable(const std::vector<Product>& list) {
    std::cout << "ID | Название          | Категория      | Цена   | Остаток\n";
    std::cout << "----------------------------------------------------------\n";
    for (const auto& p : list) {
        std::cout << p.id << "  | " << p.name << " | " << p.category << " | " 
                  << p.price << "  | " << p.quantity << "\n";
    }
    std::cout << "\n";
}

template<typename T>
T getInput(const std::string& prompt) {
    T val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) { std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); return val; }
        std::cout << "Ошибка ввода. Повторите.\n";
        std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string getStringInput(const std::string& prompt) {
    std::cout << prompt;
    std::string s; std::getline(std::cin, s); return s;
}

void run(Warehouse& warehouse) {
    while (true) {
        std::cout << "\n=== СКЛАД ===\n1. Добавить\n2. Редактировать\n3. Удалить\n4. Поиск/Фильтр\n5. Сортировка\n6. Аналитика\n7. Сохранить\n8. Выход\nВыберите: ";
        int choice; if (!(std::cin >> choice)) { std::cin.clear(); std::cin.ignore(1000, '\n'); continue; }
        std::cin.ignore(1000, '\n');

        switch (choice) {
            case 1: {
                int id = getInput<int>("ID: "); std::string n = getStringInput("Название: "); std::string c = getStringInput("Категория: ");
                double pr = getInput<double>("Цена: "); int q = getInput<int>("Количество: ");
                if (warehouse.addProduct(id, n, c, pr, q)) std::cout << "Добавлено!\n"; else std::cout << "Ошибка (дубликат ID или неверные данные)\n";
                break;
            }
            case 2: {
                int id = getInput<int>("ID для редактирования: "); std::string n = getStringInput("Новое название: "); std::string c = getStringInput("Новая категория: ");
                double pr = getInput<double>("Новая цена: "); int q = getInput<int>("Новое количество: ");
                if (warehouse.editProduct(id, n, c, pr, q)) std::cout << "Обновлено!\n"; else std::cout << "Не найдено или ошибка данных\n";
                break;
            }
            case 3: {
                std::cout << "1. По ID\n2. По названию\nВыберите: "; int t; std::cin >> t; std::cin.ignore();
                if (t == 1) { int id = getInput<int>("ID: "); warehouse.deleteProduct(id); }
                else { std::string n = getStringInput("Название: "); warehouse.deleteProductByName(n); }
                std::cout << "Запись удалена (если существовала)\n"; break;
            }
            case 4: {
                std::cout << "1. По имени\n2. По категории\n3. По цене\nВыберите: "; int t; std::cin >> t; std::cin.ignore();
                if (t == 1) { std::string q = getStringInput("Часть названия: "); printTable(warehouse.searchByName(q)); }
                else if (t == 2) { std::string c = getStringInput("Категория: "); printTable(warehouse.filterByCategory(c)); }
                else { double mn = getInput<double>("Мин цена: "); double mx = getInput<double>("Макс цена: "); printTable(warehouse.filterByPriceRange(mn, mx)); }
                break;
            }
            case 5: {
                std::cout << "1. Цена (↑)\n2. Цена (↓)\n3. Количество (↑)\n4. Количество (↓)\n5. Алфавит\nВыберите: "; int t; std::cin >> t;
                if (t == 1) warehouse.sortByPrice(true); else if (t == 2) warehouse.sortByPrice(false);
                else if (t == 3) warehouse.sortByQuantity(true); else if (t == 4) warehouse.sortByQuantity(false);
                else if (t == 5) warehouse.sortByName();
                printTable(warehouse.getProducts()); break;
            }
            case 6: {
                std::cout << "Общая стоимость: " << warehouse.getTotalValue() << " руб.\n";
                std::cout << "Мало остатков (<=5):\n"; printTable(warehouse.getLowStock(5));
                std::cout << "Топ-3 дорогих:\n"; printTable(warehouse.getTop3Expensive());
                break;
            }
            case 7: { saveData(warehouse, "data/products.txt"); std::cout << "Сохранено в data/products.txt\n"; break; }
            case 8: { std::cout << "Выход...\n"; return; }
            default: std::cout << "Неверный пункт\n";
        }
    }
}