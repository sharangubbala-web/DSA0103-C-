# DSA01-192425152-Assignment5
Name: G J D Sai Sharan | Register Number: 192425152 | Department: AIML
Compiler/version: (paste `g++ --version`)

Compile:     g++ -std=c++17 -Wall -Wextra <file>.cpp -o <name>
Sanitizer:   g++ -std=c++17 -Wall -Wextra -fsanitize=address -g <file>.cpp -o <name>_asan
Benchmark:   g++ -std=c++17 -O2 Task_B3/benchmark.cpp -o bench

| Folder | File | Purpose |
|---|---|---|
| Task_A2 | predict.cpp | Predict output; then remove `virtual` from ~Bill (add a std::string member to OPBill to see ASan) |
| Task_A5 | predict.cpp | Predict output (stack unwinding) |
| Task_B1 | complete_code.cpp | TODO 1-3; then remove `virtual` from total() and record the compiler error |
| Task_B1 | payers_test.cpp | B1.1 bills x payers (hand-verify totals) |
| Task_B2 | predict.cpp | Predict output |
| Task_B2 | complete_code.cpp | TODO 1-2; replace `throw;` by `throw e;` and compare |
| Task_B2 | errors_test.cpp | B2 error conditions incl. bad_alloc and stod |
| Task_B3 | benchmark.cpp | B3.2 and B3.3 timings (record on your machine) |
| Task_B4 | extension.cpp | New bill (Maternity) + new payer (Corporate); run with ASan |
| common | billing.h | Shared hierarchy, payers, exception classes |

Commit at least once per task. Add output screenshots to each folder and a result note per task here.

Note (B2.5 bad_alloc): run errors_test WITHOUT -fsanitize=address. ASan aborts on the huge allocation instead of letting new throw std::bad_alloc. Use the sanitizer for the other tests.
