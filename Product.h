#pragma once
#include <string>
#include <memory>
#include "Attributes.h" 

class Warehouse;

class Product {
protected:
    int id;                 
    std::string name;       
    Price price_;           
    Quantity quantity_;     
    Weight weight_;         
    std::string category;   

    static int nextId_;    

public:
    Product(int custom_id, const std::string& name, const Price& p, const Quantity& q, const Weight& w, const std::string& cat)
        : id(custom_id == 0 ? nextId_++ : custom_id), name(name), price_(p), quantity_(q), weight_(w), category(cat) {}

    virtual ~Product() = default;

    virtual std::unique_ptr<Product> clone() const = 0;

    int getId() const { return id; }
    std::string getName() const { return name; }
    int getPrice() const { return price_.getValue(); }
    int getQuantity() const { return quantity_.getValue(); }
    double getWeight() const { return weight_.getValue(); }
    std::string getCategory() const { return category; }

    void setPrice(const Price& newPrice) { price_ = newPrice; }
    void changeQuantity(int delta) { quantity_.change(delta); }

    void transferTo(Warehouse& other);
};
