// Counter program: expected output  5 7 7
#include <iostream>
using namespace std;
int main() {
    int c = 5;
    int a = c++;   // a = 5, c = 6
    int b = ++c;   // c = 7, b = 7
    cout << a << ' ' << b << ' ' << c << '\n';
}
