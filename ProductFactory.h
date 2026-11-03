#pragma once
#include <memory>
#include <string>
#include "ConcreteProducts.h"
#include "Attributes.h"       


class ProductFactory {
public:
    // Чисто виртуальный метод для создания товара. Исправлен double на int для цены (price).
    virtual std::unique_ptr<Product> createProduct(
        int id, 
        const std::string& name, 
        int price, 
        int quantity, 
        double weight
    ) = 0;
    
    virtual ~ProductFactory() = default;
};


class SmartphoneFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override {

        return std::make_unique<Smartphone>(id, name, Price(price), Quantity(quantity), Weight(weight));
    }
};

class LaptopFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override {
        return std::make_unique<Laptop>(id, name, Price(price), Quantity(quantity), Weight(weight));
    }
};



class TShirtFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override {
        return std::make_unique<TShirt>(id, name, Price(price), Quantity(quantity), Weight(weight));
    }
};

class JacketFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override {
        return std::make_unique<Jacket>(id, name, Price(price), Quantity(quantity), Weight(weight));
    }
};


class MilkFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override {
        return std::make_unique<Milk>(id, name, Price(price), Quantity(quantity), Weight(weight));
    }
};

class BreadFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override {
        return std::make_unique<Bread>(id, name, Price(price), Quantity(quantity), Weight(weight));
    }
};
