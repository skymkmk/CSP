#include <iostream>
#include <vector>

using namespace std;

struct Square {
    int x1, y1, x2, y2;
};

int trunc(int value, int limit) {
    if (value < 0)
        return 0;
    if (value > limit)
        return limit;
    return value;
}

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    vector<Square> locs;
    for (int i = 0; i < n; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        locs.push_back({ x1, y1, x2, y2 });
    }
    int area = 0;
    for (const Square &i : locs) {
        int x1 = trunc(i.x1, a), x2 = trunc(i.x2, a), y1 = trunc(i.y1, b), y2 = trunc(i.y2, b);
        area += abs(x1 - x2) * abs(y1 - y2);
    }
    cout << area << endl;
    return 0;
}