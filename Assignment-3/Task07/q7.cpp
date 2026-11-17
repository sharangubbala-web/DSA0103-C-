#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

class Complex {
    double re, im;
public:
    Complex() : re(0), im(0) {}
    Complex(double real) : re(real), im(0) {}
    Complex(double real, double imag) : re(real), im(imag) {}
    Complex operator+(const Complex& z) const { return Complex(re + z.re, im + z.im); }
    Complex operator-(const Complex& z) const { return Complex(re - z.re, im - z.im); }
    Complex operator*(const Complex& z) const {
        return Complex(re*z.re - im*z.im, re*z.im + im*z.re);
    }
    Complex operator/(const Complex& z) const {
        double denominator = z.re*z.re + z.im*z.im;
        if (denominator == 0.0) throw domain_error("Division by zero impedance");
        return Complex((re*z.re + im*z.im)/denominator,
                       (im*z.re - re*z.im)/denominator);
    }
    bool operator==(const Complex& z) const { return re == z.re && im == z.im; }
    double magnitude() const { return sqrt(re*re + im*im); }
    friend ostream& operator<<(ostream& out, const Complex& z) {
        out << z.re;
        if (z.im >= 0) out << " + j" << z.im;
        else out << " - j" << -z.im;
        return out;
    }
};

int main() {
    try {
        Complex resistor(10, 0), inductor(0, 5), capacitor(0, -2);
        Complex series = resistor + inductor + capacitor;
        cout << "Series impedance: " << series << '\n';
        cout << "Magnitude: " << series.magnitude() << '\n';

        Complex z1(10, 5), z2(20, -5);
        Complex parallel = (z1 * z2) / (z1 + z2);
        cout << "Parallel impedance: " << parallel << '\n';

        Complex zero(0, 0);
        Complex invalid = z1 / zero;
        cout << invalid << '\n';
    } catch (const domain_error& e) {
        cout << "Error: " << e.what() << '\n';
    }
}
