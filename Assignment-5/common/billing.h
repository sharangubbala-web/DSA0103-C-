#pragma once
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
struct BillingError : std::runtime_error { using std::runtime_error::runtime_error; };
struct InvalidChargeError : BillingError { using BillingError::BillingError; };
struct ClaimError : BillingError { using BillingError::BillingError; };
struct UnknownPackageError : BillingError { using BillingError::BillingError; };
struct RecordNotFoundError : BillingError { using BillingError::BillingError; };

inline double chk(double x) { if (x < 0) throw InvalidChargeError("negative charge"); return x; }

class Bill {
protected:
    std::string patient;
public:
    explicit Bill(std::string p) : patient(std::move(p)) {}
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual std::string type() const { return "Bill"; }
    const std::string& name() const { return patient; }
    void print() const { std::cout << type() << ' ' << patient << ": " << total() << '\n'; }
};
class OutPatient : public Bill {
    double consultation, tests;
public:
    OutPatient(const std::string& p, double c, double t) : Bill(p), consultation(chk(c)), tests(chk(t)) {}
    double total() const noexcept override { return consultation + tests; }
    std::string type() const override { return "OP"; }
};
class InPatient : public Bill {
    int days; double perDay, surgery;
public:
    InPatient(const std::string& p, int d, double r, double s) : Bill(p), days(d), perDay(chk(r)), surgery(chk(s)) {}
    double total() const noexcept override { return days * perDay + surgery; }
    std::string type() const override { return "IP"; }
};

class Payer {
public:
    virtual ~Payer() = default;
    virtual double amountCovered(const Bill&) const = 0;
    virtual std::string label() const = 0;
};
class SelfPay : public Payer {
public:
    double amountCovered(const Bill&) const override { return 0; }
    std::string label() const override { return "SelfPay"; }
};
class Insurance : public Payer {
    double limit, copay;   // copay = percentage paid by the patient
public:
    Insurance(double l, double c) : limit(l), copay(c) {}
    double amountCovered(const Bill& b) const override {
        double covered = b.total() * (100 - copay) / 100;
        if (covered > limit) throw ClaimError("exceeds cover");
        return covered;
    }
    std::string label() const override { return "Insurance"; }
};
class GovernmentScheme : public Payer {
    std::map<std::string, double> rates;
public:
    explicit GovernmentScheme(std::map<std::string, double> r) : rates(std::move(r)) {}
    double amountCovered(const Bill& b) const override {
        auto it = rates.find(b.type());
        if (it == rates.end()) throw UnknownPackageError("unknown package " + b.type());
        return it->second;
    }
    std::string label() const override { return "Govt"; }
};
