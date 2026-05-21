#include "Warehouse.h"
#include <algorithm>
#include <cctype>
#include <iostream>

bool Warehouse::addProduct(int id, const std::string& name, const std::string& category, double price, int quantity) {
    if (id <= 0 || price < 0 || quantity < 0 || name.empty() || category.empty()) return false;
    for (const auto& p : products_) if (p.id == id) return false;
    products_.push_back({id, name, category, price, quantity});
    return true;
}

bool Warehouse::editProduct(int id, const std::string& name, const std::string& category, double price, int quantity) {
    for (auto& p : products_) {
        if (p.id == id) {
            if (price < 0 || quantity < 0 || name.empty()) return false;
            p.name = name; p.category = category; p.price = price; p.quantity = quantity;
            return true;
        }
    }
    return false;
}

bool Warehouse::deleteProduct(int id) {
    auto it = std::remove_if(products_.begin(), products_.end(), [id](const Product& p){ return p.id == id; });
    if (it != products_.end()) { products_.erase(it, products_.end()); return true; }
    return false;
}

bool Warehouse::deleteProductByName(const std::string& name) {
    auto it = std::remove_if(products_.begin(), products_.end(), [&name](const Product& p){ return p.name == name; });
    if (it != products_.end()) { products_.erase(it, products_.end()); return true; }
    return false;
}

std::vector<Product> Warehouse::searchByName(const std::string& query) const {
    std::vector<Product> res;
    std::string q = query; std::transform(q.begin(), q.end(), q.begin(), ::tolower);
    for (const auto& p : products_) {
        std::string n = p.name; std::transform(n.begin(), n.end(), n.begin(), ::tolower);
        if (n.find(q) != std::string::npos) res.push_back(p);
    }
    return res;
}

std::vector<Product> Warehouse::filterByCategory(const std::string& category) const {
    std::vector<Product> res;
    std::string c = category; std::transform(c.begin(), c.end(), c.begin(), ::tolower);
    for (const auto& p : products_) {
        std::string pc = p.category; std::transform(pc.begin(), pc.end(), pc.begin(), ::tolower);
        if (pc == c) res.push_back(p);
    }
    return res;
}

std::vector<Product> Warehouse::filterByPriceRange(double min, double max) const {
    std::vector<Product> res;
    for (const auto& p : products_) if (p.price >= min && p.price <= max) res.push_back(p);
    return res;
}

void Warehouse::sortByPrice(bool asc) {
    std::sort(products_.begin(), products_.end(), [asc](const Product& a, const Product& b){
        return asc ? a.price < b.price : a.price > b.price;
    });
}
void Warehouse::sortByQuantity(bool asc) {
    std::sort(products_.begin(), products_.end(), [asc](const Product& a, const Product& b){
        return asc ? a.quantity < b.quantity : a.quantity > b.quantity;
    });
}
void Warehouse::sortByName() {
    std::sort(products_.begin(), products_.end(), [](const Product& a, const Product& b){ return a.name < b.name; });
}

double Warehouse::getTotalValue() const {
    double sum = 0;
    for (const auto& p : products_) sum += p.price * p.quantity;
    return sum;
}
std::vector<Product> Warehouse::getLowStock(int threshold) const {
    std::vector<Product> res;
    for (const auto& p : products_) if (p.quantity <= threshold) res.push_back(p);
    return res;
}
std::vector<Product> Warehouse::getTop3Expensive() const {
    auto temp = products_;
    std::sort(temp.begin(), temp.end(), [](const Product& a, const Product& b){ return a.price > b.price; });
    if (temp.size() > 3) temp.resize(3);
    return temp;
}

const std::vector<Product>& Warehouse::getProducts() const { return products_; }