#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class Time {
    int seconds;
public:
    explicit Time(int s = 0) : seconds(s) {}
    Time& operator++() { ++seconds; return *this; }
    Time operator++(int) { Time old = *this; ++seconds; return old; }
    bool operator==(const Time& t) const { return seconds == t.seconds; }
    bool operator<(const Time& t) const { return seconds < t.seconds; }
    void display() const {
        int h = seconds / 3600, m = (seconds % 3600) / 60, s = seconds % 60;
        cout << h << ':' << m << ':' << s;
    }
};

class Playlist {
    vector<string> tracks;
public:
    Playlist(initializer_list<string> list) : tracks(list) {}
    string& operator[](size_t i) {
        if (i >= tracks.size()) throw out_of_range("Track index out of range");
        return tracks[i];
    }
    const string& operator[](size_t i) const {
        if (i >= tracks.size()) throw out_of_range("Track index out of range");
        return tracks[i];
    }
    size_t size() const { return tracks.size(); }
};

int main() {
    Time t(10);
    Time a = t++;
    Time b = ++t;
    cout << "a="; a.display();
    cout << " b="; b.display();
    cout << " t="; t.display(); cout << '\n';

    Playlist p{"Track One", "Track Two"};
    cout << p[0] << '\n';
    try { cout << p[2] << '\n'; }
    catch (const out_of_range& e) { cout << e.what() << '\n'; }
}
