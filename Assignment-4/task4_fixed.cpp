// Task 4.3 - Repaired program. Expected output: 3.5 then 4
#include <iostream>
#include <memory>
#include <vector>
class Account {
public:
    virtual double rate() const { return 3.5; }
    virtual ~Account() = default;
};
class SeniorAccount : public Account {
    double* history;
public:
    SeniorAccount() : history(new double[100]{}) {}
    ~SeniorAccount() override { delete[] history; }
    double rate() const override { return 4.0; }
};
int main() {
    std::vector<std::unique_ptr<Account>> accounts;
    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());
    for (const auto& a : accounts) std::cout << a->rate() << '\n';
}
