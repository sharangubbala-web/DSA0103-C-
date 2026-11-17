#include "../common/billing.h"
#include <memory>
#include <vector>
int main() {
    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatient>("Ravi", 500, 1200));
    bills.push_back(std::make_unique<InPatient>("Meena", 3, 2500, 40000));
    SelfPay s; Insurance ins(50000, 10); GovernmentScheme gov({{"OP", 1200}, {"IP", 40000}});
    const Payer* payers[] = {&s, &ins, &gov};
    for (auto& b : bills) for (const Payer* p : payers) {
        try {
            double c = p->amountCovered(*b);
            std::cout << b->type() << ' ' << b->name() << " total " << b->total() << " | " << p->label()
                      << " covers " << c << " | patient pays " << b->total() - c << '\n';
        } catch (const BillingError& e) { std::cout << p->label() << " rejected: " << e.what() << '\n'; }
    }
}
