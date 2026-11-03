#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Product.h"
#include "Attributes.h"

class Warehouse;


class WarehouseIterator {
private:
    std::vector<std::unique_ptr<Product>>::iterator current_;
    std::vector<std::unique_ptr<Product>>::iterator end_;

public:
    WarehouseIterator(std::vector<std::unique_ptr<Product>>::iterator start, 
                      std::vector<std::unique_ptr<Product>>::iterator finish) 
        : current_(start), end_(finish) {}

    WarehouseIterator& operator++() {
        if (current_ != end_) { ++current_; }
        return *this;
    }

    Product& operator*() const { return **current_; }
    bool operator!=(const WarehouseIterator& other) const { return current_ != other.current_; }
    bool operator==(const WarehouseIterator& other) const { return current_ == other.current_; }
};

class WarehouseConstIterator {
private:
    std::vector<std::unique_ptr<Product>>::const_iterator current_;
    std::vector<std::unique_ptr<Product>>::const_iterator end_;

public:
    WarehouseConstIterator(std::vector<std::unique_ptr<Product>>::const_iterator start, 
                           std::vector<std::unique_ptr<Product>>::const_iterator finish) 
        : current_(start), end_(finish) {}

    WarehouseConstIterator& operator++() {
        if (current_ != end_) { ++current_; }
        return *this;
    }

    // возвращает константную ссылку,товар нельзя изменить
    const Product& operator*() const { return **current_; }
    bool operator!=(const WarehouseConstIterator& other) const { return current_ != other.current_; }
    bool operator==(const WarehouseConstIterator& other) const { return current_ == other.current_; }
};

class Warehouse {
private:
    std::vector<std::unique_ptr<Product>> products_; 
    size_t maxSize_;                                 
    size_t currentSize_;                             

public:
    Warehouse(size_t maxSize);

    ~Warehouse() = default;                                     
    Warehouse(const Warehouse& other);                         
    Warehouse& operator=(const Warehouse& other);              
    Warehouse(Warehouse&& other) noexcept;                      
    Warehouse& operator=(Warehouse&& other) noexcept;           

    size_t getMaxSize() const { return maxSize_; }
    size_t getCurrentSize() const { return currentSize_; }

    bool addProduct(std::unique_ptr<Product> product);
    bool removeById(int id);
    bool removeByIndex(size_t index);
    Product* findById(int id) const;
    std::vector<Product*> findByCategory(const std::string& cat) const;
    std::vector<Product*> findByPrice(const Price& price) const;


    WarehouseIterator begin();
    WarehouseIterator end();

    WarehouseConstIterator begin() const;
    WarehouseConstIterator end() const;
};
