// Task 2 Predict the Output. Expected: "Person Student Staff TA"
// Compile with -DNONVIRTUAL to see: "Person Student Person Staff TA"
#include <iostream>
#ifdef NONVIRTUAL
#define VIRT
#else
#define VIRT virtual
#endif
struct Person  { Person()  { std::cout << "Person "; } };
struct Student : VIRT Person { Student() { std::cout << "Student "; } };
struct Staff   : VIRT Person { Staff()   { std::cout << "Staff ";   } };
struct TA : Student, Staff   { TA()      { std::cout << "TA\n";     } };
int main() { TA t; std::cout << "sizeof(TA) = " << sizeof(t) << '\n'; }
