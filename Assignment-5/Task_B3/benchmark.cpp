#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>
#include <variant>
#include <vector>
struct Bill { virtual ~Bill() = default; virtual double total() const = 0; };
struct OP : Bill { double c, t; OP(double a, double b) : c(a), t(b) {} double total() const override { return c + t; } };
struct IP : Bill { int d; double r, s; IP(int a, double b, double c2) : d(a), r(b), s(c2) {} double total() const override { return d * r + s; } };
enum class Kind { OP, IP };
struct FlatBill { Kind k; double a, b, c; };
double totalSwitch(const FlatBill& f) { switch (f.k) { case Kind::OP: return f.a + f.b; case Kind::IP: return f.a * f.b + f.c; } return 0; }
struct VOP { double c, t; }; struct VIP { int d; double r, s; };
using V = std::variant<VOP, VIP>;
struct Total { double operator()(const VOP& x) const { return x.c + x.t; } double operator()(const VIP& x) const { return x.d * x.r + x.s; } };
template <class F> double timeMs(F f, double& out) {
    auto t0 = std::chrono::steady_clock::now(); out = f();
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
}
bool checkRc(double x) { return x >= 0; }
void checkEx(double x) { if (x < 0) throw std::invalid_argument("neg"); }
int main() {
    std::cout << "== B3.2 virtual vs switch vs variant ==\n";
    for (size_t n : {1000ul, 1000000ul, 10000000ul}) {
        std::mt19937 g(1);
        std::vector<std::unique_ptr<Bill>> vb; std::vector<FlatBill> fb; std::vector<V> vv;
        for (size_t i = 0; i < n; ++i) {
            if (g() % 2) { vb.push_back(std::make_unique<OP>(500, 1200)); fb.push_back({Kind::OP, 500, 1200, 0}); vv.push_back(VOP{500, 1200}); }
            else { vb.push_back(std::make_unique<IP>(3, 2500, 40000)); fb.push_back({Kind::IP, 3, 2500, 40000}); vv.push_back(VIP{3, 2500, 40000}); }
        }
        double a, b, c;
        double t1 = timeMs([&] { double s = 0; for (auto& p : vb) s += p->total(); return s; }, a);
        double t2 = timeMs([&] { double s = 0; for (auto& f : fb) s += totalSwitch(f); return s; }, b);
        double t3 = timeMs([&] { double s = 0; for (auto& v : vv) s += std::visit(Total{}, v); return s; }, c);
        std::cout << n << " virtual " << t1 << " ms, switch " << t2 << " ms, variant " << t3 << " ms, agree=" << (a == b && b == c) << '\n';
    }
    std::cout << "== B3.3 return codes vs exceptions (1,000,000 bills) ==\n";
    for (int pct : {0, 1, 50}) {
        std::mt19937 g(2); std::vector<double> data(1000000);
        for (auto& x : data) x = (int(g() % 100) < pct) ? -1.0 : 100.0;
        long bad1 = 0, bad2 = 0;
        auto t0 = std::chrono::steady_clock::now();
        for (double x : data) if (!checkRc(x)) ++bad1;
        double t1 = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
        t0 = std::chrono::steady_clock::now();
        for (double x : data) { try { checkEx(x); } catch (const std::invalid_argument&) { ++bad2; } }
        double t2 = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
        std::cout << pct << "% invalid: return codes " << t1 << " ms, exceptions " << t2 << " ms, counts " << bad1 << "/" << bad2 << '\n';
    }
}
