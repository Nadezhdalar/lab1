#pragma once
#include <stdexcept>
#include <string>

class Price {
private:
    int value_; 
public:
    Price(int val) {
        if (val < 0) throw std::invalid_argument("Цена не может быть отрицательной");
        value_ = val;
    }
    int getValue() const { return value_; }
    void setValue(int newVal) {
        if (newVal < 0) throw std::invalid_argument("Цена не может быть отрицательной");
        value_ = newVal;
    }
};

class Quantity {
private:
    int value_;
public:
    Quantity(int val) {
        if (val < 0) throw std::invalid_argument("Количество не может быть отрицательным");
        value_ = val;
    }
    int getValue() const { return value_; }
    void setValue(int newVal) {
        if (newVal < 0) throw std::invalid_argument("Количество не может быть отрицательным");
        value_ = newVal;
    }

    void change(int delta) {
        if (value_ + delta < 0) {
            throw std::invalid_argument("Количество после изменения не может быть отрицательным");
        }
        value_ += delta;
    }
};


class Weight {
private:
    double value_;
public:
    Weight(double val) {
        if (val < 0.0) throw std::invalid_argument("Вес не может быть отрицательным");
        value_ = val;
    }
    double getValue() const { return value_; }
    void setValue(double newVal) {
        if (newVal < 0.0) throw std::invalid_argument("Вес не может быть отрицательным");
        value_ = newVal;
    }
};
