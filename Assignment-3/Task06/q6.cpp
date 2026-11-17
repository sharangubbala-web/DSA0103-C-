#include <iostream>
#include <cstring>
using namespace std;

class Text {
    char* data;
public:
    Text(const char* s = "") {
        size_t len = strlen(s);
        data = new char[len + 1];
        strcpy(data, s);
    }
    Text(const Text& other) {
        size_t len = strlen(other.data);
        data = new char[len + 1];
        strcpy(data, other.data);
    }
    Text& operator=(const Text& other) {
        if (this != &other) {
            size_t len = strlen(other.data);
            char* temp = new char[len + 1];
            strcpy(temp, other.data);
            delete[] data;
            data = temp;
        }
        return *this;
    }
    ~Text() { delete[] data; }
    Text operator+(const Text& other) const {
        size_t a = strlen(data), b = strlen(other.data);
        char* temp = new char[a + b + 1];
        strcpy(temp, data);
        strcat(temp, other.data);
        Text result(temp);
        delete[] temp;
        return result;
    }
    bool operator==(const Text& other) const { return strcmp(data, other.data) == 0; }
    bool operator!=(const Text& other) const { return !(*this == other); }
    friend ostream& operator<<(ostream& out, const Text& t) { return out << t.data; }
};

int main() {
    Text a("Hello "), b("World");
    Text c = a + b;
    cout << c << '\n';
    cout << boolalpha << (c != a) << '\n';
    c = c;  // self-assignment test
    Text empty;
    cout << "Empty=[" << empty << "]\n";
}
