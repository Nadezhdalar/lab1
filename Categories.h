#pragma once
#include "Product.h" 


class Electronics : public Product {
public:
    Electronics(int id, const std::string& name, const Price& p, const Quantity& q, const Weight& w)
        : Product(id, name, p, q, w, "electronics") {}
};


class Clothing : public Product {
public:
    Clothing(int id, const std::string& name, const Price& p, const Quantity& q, const Weight& w)
        : Product(id, name, p, q, w, "clothing") {}
};


class Food : public Product {
public:
    Food(int id, const std::string& name, const Price& p, const Quantity& q, const Weight& w)
        : Product(id, name, p, q, w, "food") {}
};
