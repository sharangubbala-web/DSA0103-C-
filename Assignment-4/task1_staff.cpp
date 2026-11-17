// Task 1.2 - Repaired payroll design (abstract Staff base class)
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
class Staff {
protected:
    std::string name;
    int id;
public:
    Staff(const std::string& n, int i) : name(n), id(i) {}
    virtual double pay() const = 0;
    virtual void display() const { std::cout << name << " (" << id << ") "; }
    virtual ~Staff() = default;
};
class Professor : public Staff {
    double basic, research;
public:
    Professor(const std::string& n, int i, double b, double r) : Staff(n, i), basic(b), research(r) {}
    double pay() const override { constexpr double allowanceRate = 0.42; return basic + basic * allowanceRate + research; }
};
class LabAssistant : public Staff {
    double basic;
public:
    LabAssistant(const std::string& n, int i, double b) : Staff(n, i), basic(b) {}
    double pay() const override { constexpr double allowanceRate = 0.42; return basic + basic * allowanceRate; }
};
class GuestFaculty : public Staff {
    double hours, rate;
public:
    GuestFaculty(const std::string& n, int i, double h, double r) : Staff(n, i), hours(h), rate(r) {}
    double pay() const override { return hours * rate; }
};
int main() {
    std::vector<std::unique_ptr<Staff>> people;
    people.push_back(std::make_unique<Professor>("Anu", 101, 50000, 5000));
    people.push_back(std::make_unique<LabAssistant>("Bala", 102, 30000));
    people.push_back(std::make_unique<GuestFaculty>("Chitra", 103, 40, 800));
    for (const auto& person : people) {
        person->display();
        std::cout << "Pay = " << person->pay() << '\n';
    }
}
