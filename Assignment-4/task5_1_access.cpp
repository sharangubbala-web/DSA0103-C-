// Task 5.1 - Four ways to reach an object + method chaining with *this
#include <iostream>
#include <string>
class Cart {
    std::string item; double price;
public:
    Cart(const std::string& item, double price) : item(item), price(price) {}
    void show() const { std::cout << item << ": " << price << '\n'; }
    Cart& setPrice(double price) { this->price = price; return *this; }
};
int main() {
    Cart direct("Book", 100);  direct.show();
    Cart* pointer = &direct;   pointer->show();
    Cart& reference = direct;  reference.show();
    Cart* dynamicCart = new Cart("Pen", 20); dynamicCart->show(); delete dynamicCart;
    direct.setPrice(125).show();
}
