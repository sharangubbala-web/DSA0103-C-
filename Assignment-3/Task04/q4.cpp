#include <iostream>
#include <iomanip>
using namespace std;

class Money {
    long long paise;
public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}
    Money operator+(const Money& other) const {
        Money result;
        result.paise = paise + other.paise;
        return result;
    }
    bool operator==(const Money& other) const { return paise == other.paise; }
    friend ostream& operator<<(ostream& out, const Money& m) {
        long long whole = m.paise / 100;
        long long fraction = m.paise % 100;
        if (fraction < 0) fraction = -fraction;
        out << "Rs " << whole << '.' << setw(2) << setfill('0') << fraction;
        return out;
    }
};

int main() {
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    cout << c << '\n' << boolalpha << (c == Money(200)) << '\n';
    Money x(0, 75), y(0, 50);
    cout << (x + y) << '\n';
}
