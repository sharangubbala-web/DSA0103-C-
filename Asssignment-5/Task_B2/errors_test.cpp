#include "../common/billing.h"
#include <memory>
struct Guard { std::string n; explicit Guard(std::string s) : n(std::move(s)) {} ~Guard() { std::cout << "~" << n << ' '; } };
struct OddBill : Bill { OddBill() : Bill("Odd") {} double total() const override { return 1; } std::string type() const override { return "XYZ"; } };
template <class F> void run(const char* id, F f) {
    std::cout << id << ": ";
    try { Guard g(id); f(); std::cout << "no error"; }
    catch (const ClaimError& e)          { std::cout << "ClaimError(" << e.what() << ")"; }
    catch (const BillingError& e)        { std::cout << "BillingError(" << e.what() << ")"; }
    catch (const std::invalid_argument& e){ std::cout << "invalid_argument(" << e.what() << ")"; }
    catch (const std::bad_alloc&)        { std::cout << "bad_alloc"; }
    catch (...)                          { std::cout << "unknown"; }
    std::cout << '\n';
}
int main() {
    run("B2.1 negative charge", [] { OutPatient b("X", -1, 100); });
    run("B2.2 claim above cover", [] { OutPatient b("X", 60000, 0); Insurance(50000, 0).amountCovered(b); });
    run("B2.3 unknown package", [] { OddBill b; GovernmentScheme({{"OP", 1}}).amountCovered(b); });
    run("B2.4 stod text", [] { std::stod("abc"); });
    run("B2.5 bad_alloc", [] { std::size_t big = std::size_t(1) << 56; volatile double* p = new double[big]; (void)p; });
    run("B2.6 other type", [] { throw 3.14; });
    std::cout << "program still running\n";
}
