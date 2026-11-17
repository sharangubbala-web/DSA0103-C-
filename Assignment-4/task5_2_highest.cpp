// Task 5.2 - Array of pointers, highest total. Expected: Highest total: 480
#include <iostream>
class Cart {
    double amount;
public:
    explicit Cart(double a) : amount(a) {}
    double total() const { return amount; }
};
int main() {
    Cart a(250), b(480), c(320);
    Cart* carts[] = {&a, &b, &c};
    int best = 0;
    for (int i = 1; i < 3; ++i) if (carts[i]->total() > carts[best]->total()) best = i;
    std::cout << "Highest total: " << carts[best]->total() << '\n';
}
