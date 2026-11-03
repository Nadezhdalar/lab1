#pragma once
#include "Categories.h" 

class Smartphone : public Electronics {
public:
    Smartphone(int id, const std::string& name, const Price& p, const Quantity& q, const Weight& w)
        : Electronics(id, name, p, q, w) {}

    // Метод clone() создаёт новый объект Smartphone и копирует туда данные текущего (*this)
    std::unique_ptr<Product> clone() const override {
        return std::make_unique<Smartphone>(*this);
    }
};

class Laptop : public Electronics {
public:
    Laptop(int id, const std::string& name, const Price& p, const Quantity& q, const Weight& w)
        : Electronics(id, name, p, q, w) {}

    std::unique_ptr<Product> clone() const override {
        return std::make_unique<Laptop>(*this);
    }
};

class TShirt : public Clothing {
public:
    TShirt(int id, const std::string& name, const Price& p, const Quantity& q, const Weight& w)
        : Clothing(id, name, p, q, w) {}

    std::unique_ptr<Product> clone() const override {
        return std::make_unique<TShirt>(*this);
    }
};

class Jacket : public Clothing {
public:
    Jacket(int id, const std::string& name, const Price& p, const Quantity& q, const Weight& w)
        : Clothing(id, name, p, q, w) {}

    std::unique_ptr<Product> clone() const override {
        return std::make_unique<Jacket>(*this);
    }
};


class Milk : public Food {
public:
    Milk(int id, const std::string& name, const Price& p, const Quantity& q, const Weight& w)
        : Food(id, name, p, q, w) {}

    std::unique_ptr<Product> clone() const override {
        return std::make_unique<Milk>(*this);
    }
};

class Bread : public Food {
public:
    Bread(int id, const std::string& name, const Price& p, const Quantity& q, const Weight& w)
        : Food(id, name, p, q, w) {}

    std::unique_ptr<Product> clone() const override {
        return std::make_unique<Bread>(*this);
    }
};
