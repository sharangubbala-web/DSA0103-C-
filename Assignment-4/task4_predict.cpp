// Task 4 Predict the Output. Expected: 3.5 4 3.5
#include <iostream>
struct Account {
    double rate()  const { return 3.5; }
    virtual double vrate() const { return 3.5; }
    virtual ~Account() = default;
};
struct SeniorAccount : Account {
    double rate()  const { return 4.0; }
    double vrate() const override { return 4.0; }
};
int main() {
    Account* p = new SeniorAccount();
    std::cout << p->rate() << ' ' << p->vrate() << ' ';
    Account copy = SeniorAccount();   // slicing
    std::cout << copy.vrate() << '\n';
    delete p;
}
