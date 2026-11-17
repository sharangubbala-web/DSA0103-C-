#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Book {
    string title;
    int copies;
public:
    Book() : Book("Untitled", 0) {}
    explicit Book(const string& t) : Book(t, 1) {}
    Book(const string& t, int c) : title(t), copies(c) {
        if (copies < 0) throw invalid_argument("Copies cannot be negative");
    }
    void display() const {
        cout << "Title: " << title << ", Copies: " << copies << '\n';
    }
};

int main() {
    try {
        Book empty;
        Book donated("C++ Basics");
        Book complete("Data Structures", 5);
        empty.display();
        donated.display();
        complete.display();
        // Book invalid("Invalid Book", -2); // throws invalid_argument
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << '\n';
    }
    return 0;
}
