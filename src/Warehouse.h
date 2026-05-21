#pragma once
#include <vector>
#include <string>
#include "Product.h"

class Warehouse {
public:
    bool addProduct(int id, const std::string& name, const std::string& category, double price, int quantity);
    bool editProduct(int id, const std::string& name, const std::string& category, double price, int quantity);
    bool deleteProduct(int id);
    bool deleteProductByName(const std::string& name);

    std::vector<Product> searchByName(const std::string& query) const;
    std::vector<Product> filterByCategory(const std::string& category) const;
    std::vector<Product> filterByPriceRange(double min, double max) const;

    void sortByPrice(bool ascending = true);
    void sortByQuantity(bool ascending = true);
    void sortByName();

    double getTotalValue() const;
    std::vector<Product> getLowStock(int threshold = 5) const;
    std::vector<Product> getTop3Expensive() const;

    const std::vector<Product>& getProducts() const;

private:
    std::vector<Product> products_;
};