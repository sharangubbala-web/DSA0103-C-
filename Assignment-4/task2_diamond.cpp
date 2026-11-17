// Task 2.3 - Person / Student / Staff / TeachingAssistant / ResearchScholar (virtual inheritance)
#include <iostream>
#include <string>
class Person {
protected:
    std::string name; int id; std::string phone;
public:
    Person(const std::string& n, int i, const std::string& p) : name(n), id(i), phone(p) {}
    virtual ~Person() = default;
};
class Student : virtual public Person {
protected:
    std::string programme; double cgpa;
public:
    Student(const std::string& n, int i, const std::string& p, const std::string& prog, double c)
        : Person(n, i, p), programme(prog), cgpa(c) {}
};
class Staff : virtual public Person {
protected:
    std::string department; double salary;
public:
    Staff(const std::string& n, int i, const std::string& p, const std::string& dept, double s)
        : Person(n, i, p), department(dept), salary(s) {}
};
class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const std::string& n, int i, const std::string& p, const std::string& prog, double c,
                      const std::string& dept, double s)
        : Person(n, i, p), Student(n, i, p, prog, c), Staff(n, i, p, dept, s) {}
    void show() const { std::cout << name << " " << id << " " << programme << " " << department << '\n'; }
};
class ResearchScholar : public Student {
    double fellowship;
public:
    ResearchScholar(const std::string& n, int i, const std::string& p, const std::string& prog, double c, double f)
        : Person(n, i, p), Student(n, i, p, prog, c), fellowship(f) {}
};
int main() {
    TeachingAssistant ta("Divya", 7, "9876543210", "MTech", 8.9, "CSE", 25000);
    ta.show();
    ResearchScholar rs("Eswar", 8, "9123456780", "PhD", 9.1, 31000);
    std::cout << "sizeof(TeachingAssistant) = " << sizeof(ta) << '\n';
    (void)rs;
}
