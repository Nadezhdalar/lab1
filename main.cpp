#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <limits>
#include "Attributes.h"
#include "Product.h"
#include "ConcreteProducts.h"
#include "Warehouse.h"
#include "ProductFactory.h"

template <typename T>
T getSafeInput(const std::string& prompt) {
    T value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        } else {
            std::cout << "Ошибка ввода! Введите число.\n";
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
    }
}

void printWarehouse(const Warehouse& wh, const std::string& name) {
    std::cout << "\nСклад: " << name << " (" << wh.getCurrentSize() << "/" << wh.getMaxSize() << ")\n";
    if (wh.getCurrentSize() == 0) {
        std::cout << "Пусто\n";
    } else {
        for (const Product& prod : wh) {
            std::cout << "ID: " << prod.getId() 
                      << " | Категория: " << prod.getCategory() 
                      << " | Название: " << prod.getName() 
                      << " | Цена: " << prod.getPrice() << " руб."
                      << " | Остаток: " << prod.getQuantity() << " шт." 
                      << " | Вес: " << prod.getWeight() << " кг.\n";
        }
    }
}
int main() {
    std::setlocale(LC_ALL, ".UTF8");

    Warehouse mainWarehouse(5); 
    std::unique_ptr<Warehouse> movedWarehouse = nullptr;  
    std::unique_ptr<Warehouse> targetWarehouse = nullptr; 

    SmartphoneFactory phoneFactory;
    TShirtFactory clothFactory;
    MilkFactory milkFactory;

    int choice = 0;
    do {
        std::cout << "\nМеню:\n"
                  << "1. Сценарий 1: Создание склада и добавление товаров\n"
                  << "2. Сценарий 2: Глубокое копирование склада\n"
                  << "3. Сценарий 3: Перемещение склада\n"
                  << "4. Сценарий 4: Поиск и удаление товаров\n"
                  << "5. Сценарий 5: Перемещение товара (transferTo)\n"
                  << "6. Тестирование валидации атрибутов\n"
                  << "0. Выход\n";
        
        choice = getSafeInput<int>("Выберите пункт: ");

        switch (choice) {
            case 1: {
                int size = getSafeInput<int>("Вместимость склада: ");
                try {
                    mainWarehouse = Warehouse(size);
                    std::cout << "Создан склад размером " << mainWarehouse.getMaxSize() << "\n";
                } catch (const std::invalid_argument& e) {
                    std::cout << "Ошибка: " << e.what() << ". Создан склад по умолчанию (размер 5).\n";
                    mainWarehouse = Warehouse(5);
                }

                std::string phoneName;
                std::cout << "\nНазвание смартфона: ";
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); 
                std::getline(std::cin, phoneName);
                int phonePrice = getSafeInput<int>("Цена: ");
                int phoneQty = getSafeInput<int>("Количество: ");
                double phoneWeight = getSafeInput<double>("Вес: ");
                
                std::string shirtName;
                std::cout << "\nНазвание футболки: ";
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                std::getline(std::cin, shirtName);
                int shirtPrice = getSafeInput<int>("Цена: ");
                int shirtQty = getSafeInput<int>("Количество: ");
                double shirtWeight = getSafeInput<double>("Вес: ");

                std::string milkName;
                std::cout << "\nНазвание молока: ";
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                std::getline(std::cin, milkName);
                int milkPrice = getSafeInput<int>("Цена: ");
                int milkQty = getSafeInput<int>("Количество: ");
                double milkWeight = getSafeInput<double>("Вес: ");

                try {
                    mainWarehouse.addProduct(phoneFactory.createProduct(0, phoneName, phonePrice, phoneQty, phoneWeight));
                    mainWarehouse.addProduct(clothFactory.createProduct(0, shirtName, shirtPrice, shirtQty, shirtWeight));
                    mainWarehouse.addProduct(milkFactory.createProduct(0, milkName, milkPrice, milkQty, milkWeight));
                    std::cout << "Товары добавлены.\n";
                } catch (const std::exception& e) {
                    std::cout << "Ошибка при добавлении: " << e.what() << "\n";
                }

                printWarehouse(mainWarehouse, "mainWarehouse");
                break;
            }

            case 2: {
                if (mainWarehouse.getCurrentSize() == 0) {
                    std::cout << "Склад пуст.\n";
                    break;
                }

                Warehouse copyWarehouse = mainWarehouse; 
                std::cout << "Копия создана.\n";

                int targetId = getSafeInput<int>("ID товара в копии для изменения: ");
                Product* copiedProduct = copyWarehouse.findById(targetId);
                
                if (copiedProduct) {
                    int newPrice = getSafeInput<int>("Новая цена в копии: ");
                    int deltaQty = getSafeInput<int>("Изменение количества в копии: ");
                    try {
                        copiedProduct->setPrice(Price(newPrice));
                        copiedProduct->changeQuantity(deltaQty);
                    } catch (const std::exception& e) {
                        std::cout << "Ошибка изменения: " << e.what() << "\n";
                    }
                } else {
                    std::cout << "Товар не найден.\n";
                }

                Product* originalProduct = mainWarehouse.findById(targetId);
                if (originalProduct) {
                    std::cout << "Оригинал: Цена = " << originalProduct->getPrice() << ", Остаток = " << originalProduct->getQuantity() << "\n";
                }
                if (copiedProduct) {
                    std::cout << "Копия: Цена = " << copiedProduct->getPrice() << ", Остаток = " << copiedProduct->getQuantity() << "\n";
                }
                break;
            }
            case 3: {
                Warehouse tempWarehouse = mainWarehouse;
                std::cout << "Размер до перемещения: " << tempWarehouse.getCurrentSize() << "\n";

                movedWarehouse = std::make_unique<Warehouse>(std::move(tempWarehouse));

                std::cout << "Размер старого склада: " << tempWarehouse.getCurrentSize() << "\n";
                std::cout << "Размер нового склада: " << movedWarehouse->getCurrentSize() << "\n";
                printWarehouse(*movedWarehouse, "movedWarehouse");
                break;
            }

            case 4: {
                printWarehouse(mainWarehouse, "mainWarehouse");
                
                int searchId = getSafeInput<int>("ID для поиска: ");
                Product* pId = mainWarehouse.findById(searchId);
                if (pId) {
                    std::cout << "Найдено: " << pId->getName() << " | Категория: " << pId->getCategory() << "\n";
                } else {
                    std::cout << "Товар не найден.\n";
                }
                
                std::cout << "Удаление: 1 - по ID, 2 - по индексу\n";
                int delChoice = getSafeInput<int>("Выбор: ");
                
                if (delChoice == 1) {
                    int idToRemove = getSafeInput<int>("ID для удаления: ");
                    if (mainWarehouse.removeById(idToRemove)) {
                        std::cout << "Удалено.\n";
                    } else {
                        std::cout << "Не найдено.\n";
                    }
                } else if (delChoice == 2) {
                    size_t idxToRemove = getSafeInput<size_t>("Индекс для удаления: ");
                    if (mainWarehouse.removeByIndex(idxToRemove)) {
                        std::cout << "Удалено.\n";
                    } else {
                        std::cout << "Индекс вне диапазона.\n";
                    }
                }
                
                printWarehouse(mainWarehouse, "mainWarehouse после удаления");
                break;
            }
            case 5: {
                if (!movedWarehouse || movedWarehouse->getCurrentSize() == 0) {
                    std::cout << "Склад-источник пуст или не создан.\n";
                    break;
                }
                
                if (!targetWarehouse) {
                    int targetCapacity = getSafeInput<int>("Вместимость склада Б: ");
                    targetWarehouse = std::make_unique<Warehouse>(targetCapacity);
                }
                
                printWarehouse(*movedWarehouse, "Склад А");
                printWarehouse(*targetWarehouse, "Склад Б");
                
                int transferId = getSafeInput<int>("ID товара для переноса из А в Б: ");
                Product* pTransfer = movedWarehouse->findById(transferId);
                
                if (pTransfer) {
                    pTransfer->transferTo(*targetWarehouse);
                    
                    Product* pNewPlace = targetWarehouse->findById(transferId);
                    if (pNewPlace) {
                        int newPrice = getSafeInput<int>("Новая цена: ");
                        int deltaQty = getSafeInput<int>("Изменение количества: ");
                        try {
                            pNewPlace->setPrice(Price(newPrice));
                            pNewPlace->changeQuantity(deltaQty);
                        } catch (const std::exception& e) {
                            std::cout << "Ошибка: " << e.what() << "\n";
                        }
                    }
                    
                    printWarehouse(*movedWarehouse, "Склад А");
                    printWarehouse(*targetWarehouse, "Склад Б");
                } else {
                    std::cout << "Товар не найден на Складе А.\n";
                }
                break;
            }

            case 6: {
                int badPrice = getSafeInput<int>("Отрицательная цена: ");
                try {
                    Price p(badPrice);
                } catch (const std::invalid_argument& e) {
                    std::cout << "Перехвачено: " << e.what() << "\n";
                }
                
                int badQty = getSafeInput<int>("Отрицательное количество: ");
                try {
                    Quantity q(badQty);
                } catch (const std::invalid_argument& e) {
                    std::cout << "Перехвачено: " << e.what() << "\n";
                }
                break;
            }

            case 0:
                break;

            default:
                std::cout << "Неверный пункт.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
