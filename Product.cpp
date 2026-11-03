#include "Product.h"
#include "Warehouse.h" // Теперь подключаем полноценный Warehouse

// Инициализация статического счётчика
int Product::nextId_ = 1;

// Реализация метода перемещения между складами
void Product::transferTo(Warehouse& other) {
    // Создаем глубокую копию (клон) текущего товара и пробуем добавить её на другой склад
    // Метод addProduct на другом складе сам проверит, есть ли там свободное место
    other.addProduct(this->clone());
    
    // После успешного переноса обнуляем количество этого товара на старом месте
    this->changeQuantity(-this->getQuantity());
}
