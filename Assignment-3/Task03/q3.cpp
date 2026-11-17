#include <iostream>
using namespace std;

class Event {
    int rows, seatsPerRow;
    bool** booked;
public:
    Event(int r, int s) : rows(r), seatsPerRow(s), booked(nullptr) {
        if (rows > 0 && seatsPerRow > 0) {
            booked = new bool*[rows];
            for (int i = 0; i < rows; ++i) booked[i] = new bool[seatsPerRow]{};
        }
        cout << "Event created: " << rows << " rows\n";
    }
    Event(const Event&) = delete;             // owns raw memory: forbid copying
    Event& operator=(const Event&) = delete;
    bool book(int r, int s) {
        if (!booked || r < 0 || r >= rows || s < 0 || s >= seatsPerRow) return false;
        if (booked[r][s]) return false;
        booked[r][s] = true;
        return true;
    }
    bool cancel(int r, int s) {
        if (!booked || r < 0 || r >= rows || s < 0 || s >= seatsPerRow) return false;
        if (!booked[r][s]) return false;
        booked[r][s] = false;
        return true;
    }
    ~Event() {
        if (booked) {
            for (int i = 0; i < rows; ++i) delete[] booked[i];
            delete[] booked;
        }
        cout << "Event closed; seat map released\n";
    }
};

int main() {
    Event collegeEvent(2, 3);
    collegeEvent.book(0, 1);
    collegeEvent.cancel(0, 1);
    {
        Event shortEvent(1, 2);
        shortEvent.book(0, 0);
    }
    Event* specialEvent = new Event(2, 2);
    specialEvent->book(1, 1);
    delete specialEvent;
    Event zeroEvent(0, 4);
}
