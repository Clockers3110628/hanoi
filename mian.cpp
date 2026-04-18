#include <iostream>
#include <vector>

using std::vector;

constexpr int layer = 10;

struct stick {
    vector<int> a = vector<int>(layer);
    vector<int> b = vector<int>(layer);
    vector<int> c = vector<int>(layer);
}sticks;

void stick_printf(stick* sticks);
void move(int n, vector<int> &a, vector<int> &b, vector<int> &c);
void stick_int();

int main() {
    stick_int();

    move(layer, sticks.a, sticks.b, sticks.c);

    return 0;
}


void stick_printf(stick* sticks) {
    for (int i = layer; i >= 1; --i) {
        std::cout << sticks->a[i-1] << " " << sticks->b[i-1] << " " << sticks->c[i-1] << std::endl;

    }
    std::cout << "-" << "-" << "-" << std::endl;

}

void move(int n, vector<int> &a, vector<int> &b, vector<int> &c) {
    if (n == 1) {
        //
        auto q = end(a)-1;
        for (; q != begin(a) && *q == 0; --q) {}
        int tag = *q;
        *q = 0;
        auto p = end(c)-1;
        for (; p != begin(c) && *p == 0; --p) {}
        ++p;
        *p = tag;

        stick_printf(&sticks);
    }
    move(n - 1, a, c, b);
    //
    auto q = end(a)-1;
    for (; q != begin(a) && *q != 0; --q) {}
    int tag = *q;
    *q = 0;
    auto p = end(c)-1;
    for (; p != begin(c) && *p != 0; --p) {}
    ++p;
    *p = tag;

    move(n - 1, a, b, c);
}

void stick_int() {
    for (int i = 1; i <= layer; ++i) {
        sticks.a[i - 1] = i;
    }
}

