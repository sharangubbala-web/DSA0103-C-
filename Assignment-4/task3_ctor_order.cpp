// Task 3 Predict the Output. Expected: "Vehicle Engine Car | ~Car ~Engine ~Vehicle"
#include <iostream>
struct Vehicle { Vehicle() { std::cout << "Vehicle "; } ~Vehicle() { std::cout << "~Vehicle"; } };
struct Engine  { Engine()  { std::cout << "Engine ";  } ~Engine()  { std::cout << "~Engine ";  } };
struct Car : Vehicle {
    Engine e;
    Car()  { std::cout << "Car | "; }
    ~Car() { std::cout << "~Car "; }
};
int main() { { Car c; } std::cout << '\n'; }
