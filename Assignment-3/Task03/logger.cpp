// Predict-the-output program: expected  +A +B -B copyAc use -Ac +P -P end -A
#include <iostream>
#include <string>
using namespace std;

class Logger {
    string name;
public:
    explicit Logger(const string& n) : name(n) { cout << '+' << name << ' '; }
    Logger(const Logger& o) : name(o.name + "c") { cout << "copy" << name << ' '; }
    ~Logger() { cout << '-' << name << ' '; }
};

void use(Logger x) { (void)x; cout << "use "; }

int main() {
    Logger a("A");
    { Logger b("B"); }
    use(a);
    Logger* p = new Logger("P");
    delete p;
    cout << "end ";
}
