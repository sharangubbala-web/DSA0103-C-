#include "../common/billing.h"
#include <memory>
#include <vector>
// ---- NEW bill type and NEW payer: no existing class is modified ----
class Maternity : public Bill {
    double packagePrice, extraDays, perDay;
public:
    Maternity(const std::string& p, double pkg, int d, double r) : Bill(p), packagePrice(chk(pkg)), extraDays(d), perDay(chk(r)) {}
    double total() const noexcept override { return packagePrice + extraDays * perDay; }
    std::string type() const override { return "MAT"; }
};
class CorporateTieUp : public Payer {
    double pct;
public:
    explicit CorporateTieUp(double d) : pct(d) {}
    double amountCovered(const Bill& b) const override { return b.total() * pct / 100.0; }
    std::string label() const override { return "Corporate"; }
};
int main() {
    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatient>("Ravi", 500, 1200));
    bills.push_back(std::make_unique<InPatient>("Meena", 3, 2500, 40000));
    bills.push_back(std::make_unique<Maternity>("Anitha", 45000, 2, 3000));
    std::vector<std::unique_ptr<Payer>> payers;
    payers.push_back(std::make_unique<SelfPay>());
    payers.push_back(std::make_unique<Insurance>(50000, 10));
    payers.push_back(std::make_unique<GovernmentScheme>(std::map<std::string, double>{{"OP", 1200}, {"IP", 40000}}));
    payers.push_back(std::make_unique<CorporateTieUp>(15));
    for (auto& b : bills) for (auto& p : payers) {
        try {
            double c = p->amountCovered(*b);
            std::cout << b->type() << ' ' << b->name() << " total " << b->total() << " | " << p->label() << " covers " << c << " | patient pays " << b->total() - c << '\n';
        } catch (const ClaimError& e) { std::cout << b->name() << '/' << p->label() << " claim rejected: " << e.what() << '\n'; }
        catch (const BillingError& e) { std::cout << b->name() << '/' << p->label() << " error: " << e.what() << '\n'; }
    }
    try { OutPatient bad("Bad", -5, 0); } catch (const BillingError& e) { std::cout << "construction error: " << e.what() << '\n'; }
}
