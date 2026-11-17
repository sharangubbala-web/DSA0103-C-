// Task 4.1/4.2 - Reconstructed defective program (original listing not in report).
// Build with: g++ -std=c++17 -Wall -Wextra -fsanitize=address -fno-omit-frame-pointer task4_buggy.cpp
// DEFECTS: non-virtual rate(), non-virtual destructor, slicing, missing 'override'.
#include <iostream>
class Account {
public:
    double rate() const { return 3.5; }
    ~Account() {}
};
class SeniorAccount : public Account {
    double* history;
public:
    SeniorAccount() : history(new double[100]{}) {}
    ~SeniorAccount() { delete[] history; }
    double rate() const { return 4.0; }
};
int main() {
    Account* p = new SeniorAccount();
    std::cout << p->rate() << '\n';   // prints 3.5 (static dispatch)
    delete p;                          // UB: derived dtor not run -> leak reported by ASan
    Account copy = SeniorAccount();    // slicing
    std::cout << copy.rate() << '\n';
}
