// Task 6 - Vehicle Rental Fleet (Stage 5 implementation)
#include <iostream>
#include <memory>
#include <string>
#include <vector>
class Vehicle {
protected:
    std::string regNo; double dailyRate; bool rented = false;
public:
    Vehicle(const std::string& r, double rate) : regNo(r), dailyRate(rate) {}
    virtual double rentalCharge(int days) const = 0;
    bool rent() { if (rented) return false; rented = true; return true; }
    double returnVehicle(int lateDays) {
        if (!rented) return 0.0;
        rented = false;
        return rentalCharge(1) * lateDays + rentalCharge(0);
    }
    virtual void display() const {
        std::cout << regNo << " rate/day=" << dailyRate << " rented=" << (rented ? "yes" : "no") << '\n';
    }
    virtual ~Vehicle() = default;
};
class Bicycle : public Vehicle {
public:
    Bicycle(const std::string& r, double rate) : Vehicle(r, rate) {}
    double rentalCharge(int days) const override { return dailyRate * days; }
};
class MotorVehicle : public Vehicle {
protected:
    double fuelLevel; std::string serviceDue;
public:
    MotorVehicle(const std::string& r, double rate, double fuel, const std::string& due)
        : Vehicle(r, rate), fuelLevel(fuel), serviceDue(due) {}
};
class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(const std::string& r, double rate, double fuel, const std::string& due)
        : MotorVehicle(r, rate, fuel, due) {}
    double rentalCharge(int days) const override { return dailyRate * days; }
};
class Car : public MotorVehicle {
protected:
    int seats;
public:
    Car(const std::string& r, double rate, double fuel, const std::string& due, int s)
        : MotorVehicle(r, rate, fuel, due), seats(s) {}
    double rentalCharge(int days) const override { return dailyRate * days; }
};
class ElectricCar : public Car {
    double batteryCapacityKWh, energyRatePerKWh;
public:
    ElectricCar(const std::string& r, double rate, double fuel, const std::string& due, int s,
                double capacity, double energyRate)
        : Car(r, rate, fuel, due, s), batteryCapacityKWh(capacity), energyRatePerKWh(energyRate) {}
    double rentalCharge(int days) const override {
        return dailyRate * days + batteryCapacityKWh * energyRatePerKWh;
    }
};
int main() {
    std::vector<std::unique_ptr<Vehicle>> fleet;
    fleet.push_back(std::make_unique<Bicycle>("BIKE01", 100));
    fleet.push_back(std::make_unique<TwoWheeler>("TW01", 250, 8.0, "2026-12-01"));
    fleet.push_back(std::make_unique<Car>("CAR01", 1200, 30.0, "2026-12-15", 5));
    fleet.push_back(std::make_unique<ElectricCar>("EV01", 1500, 80.0, "2027-01-01", 5, 60, 8));
    for (const auto& v : fleet) {
        v->display();
        std::cout << "Two-day charge = " << v->rentalCharge(2) << '\n';
    }
    if (fleet[0]->rent()) std::cout << "Bicycle rented successfully\n";
    std::cout << "Return charge = " << fleet[0]->returnVehicle(1) << '\n';
}
