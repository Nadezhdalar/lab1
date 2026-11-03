#include "Warehouse.h"

Warehouse::Warehouse(size_t maxSize) 
    : maxSize_(maxSize), currentSize_(0) {
    if (maxSize == 0) {
        throw std::invalid_argument("Размер склада должен быть больше нуля");
    }
    products_.reserve(maxSize);
}


bool Warehouse::addProduct(std::unique_ptr<Product> product) {
    if (currentSize_ >= maxSize_) {
        return false;
    }

    products_.push_back(std::move(product));
    currentSize_ = products_.size(); 
    return true;
}


bool Warehouse::removeById(int id) {
    for (size_t i = 0; i < products_.size(); ++i) {
        if (products_[i] && products_[i]->getId() == id) {
            products_.erase(products_.begin() + i);
            currentSize_ = products_.size(); 
            return true; 
        }
    }
    return false; 
}


bool Warehouse::removeByIndex(size_t index) {
    if (index >= products_.size()) {
        return false; 
    }
    products_.erase(products_.begin() + index);
    currentSize_ = products_.size(); 
    return true;
}


Product* Warehouse::findById(int id) const {
    for (size_t i = 0; i < products_.size(); ++i) {
        if (products_[i] && products_[i]->getId() == id) {
            return products_[i].get(); 
        }
    }
    return nullptr;
}


std::vector<Product*> Warehouse::findByCategory(const std::string& cat) const {
    std::vector<Product*> result;
    for (size_t i = 0; i < products_.size(); ++i) {
        if (products_[i] && products_[i]->getCategory() == cat) {
            result.push_back(products_[i].get());
        }
    }
    return result;
}

std::vector<Product*> Warehouse::findByPrice(const Price& price) const {
    std::vector<Product*> result;
    for (size_t i = 0; i < products_.size(); ++i) {
        if (products_[i] && products_[i]->getPrice() == price.getValue()) {
            result.push_back(products_[i].get());
        }
    }
    return result;
}


WarehouseIterator Warehouse::begin() {
    return WarehouseIterator(products_.begin(), products_.end());
}

WarehouseIterator Warehouse::end() {
    return WarehouseIterator(products_.end(), products_.end());
}


WarehouseConstIterator Warehouse::begin() const {
    return WarehouseConstIterator(products_.cbegin(), products_.cend());
}


WarehouseConstIterator Warehouse::end() const {
    return WarehouseConstIterator(products_.cend(), products_.cend());
}


//правила пяти


Warehouse::Warehouse(const Warehouse& other) 
    : maxSize_(other.maxSize_), currentSize_(0) {
    
    // Резервируем место
    products_.reserve(other.maxSize_);
    
    // Перебираем товары старого склада и КЛОНИРУЕМ каждый из них
    for (size_t i = 0; i < other.products_.size(); ++i) {
        if (other.products_[i]) {
            products_.push_back(other.products_[i]->clone());
        }
    }
    currentSize_ = products_.size();
}


Warehouse& Warehouse::operator=(const Warehouse& other) {
    // Проверка на самоприсваивание (например, wh = wh;)
    if (this == &other) {
        return *this; 
    }
    

    products_.clear();
    
    maxSize_ = other.maxSize_;
    

    for (size_t i = 0; i < other.products_.size(); ++i) {
        if (other.products_[i]) {
            products_.push_back(other.products_[i]->clone());
        }
    }
    currentSize_ = products_.size();
    
    return *this; 
}


Warehouse::Warehouse(Warehouse&& other) noexcept 
    : products_(std::move(other.products_)), 
      maxSize_(other.maxSize_), 
      currentSize_(other.currentSize_) {
    
    other.maxSize_ = 0;
    other.currentSize_ = 0;
}


Warehouse& Warehouse::operator=(Warehouse&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    

    products_ = std::move(other.products_);
    maxSize_ = other.maxSize_;
    currentSize_ = other.currentSize_;
    
    
    other.maxSize_ = 0;
    other.currentSize_ = 0;
    
    return *this;
}
