#pragma once
#include <string>

class Product {
public:
    int id;
    std::string name;
    std::string category;
    double price;
    int quantity;

    Product() : id(0), name(""), category(""), price(0.0), quantity(0) {}
    Product(int id, const std::string& name, const std::string& category, double price, int quantity)
        : id(id), name(name), category(category), price(price), quantity(quantity) {}
};