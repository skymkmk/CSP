#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct field {
    int t, c;
};

bool compare(struct field a, struct field b) {
    return a.t > b.t;
}

int main() {
    // n 为田地块数，m 为资源数量，k 为最少开垦天数
    int n, m, k;
    cin >> n >> m >> k;
    // t 为开垦耗时，c 为缩短一天所需资源数量。
    vector<struct field> field(n);
    for (int i = 0; i < n; i++) {
        cin >> field[i].t >> field[i].c;
        // 只关注需要缩减的天数
        field[i].t -= k;
    }
    sort(field.begin(), field.end(), compare);
    while (m > 0) {
        if (field[0].t <= 0)
            break;
        // 考虑有一块以上的田地
        if (field.size() > 1) {
            // 首先考虑非平均情况
            if (field[0].t > field[1].t) {
                int amount = field[0].t - field[1].t;
                int price = field[0].c;
                int cost = amount * price;
                // 首先检查能否一次扣光
                if (cost >= m) {
                    amount = m / price;
                    field[0].t -= amount;
                    break;
                } else {
                    field[0].t -= amount;
                    m -= cost;
                }
            } else {
                field[0].c += field[1].c;
                field.erase(field.begin() + 1);
            }
        } else {
            if (field[0].t * field[0].c > m)
                field[0].t -= m / field[0].c;
            else
                field[0].t = 0;
            break;
        }
    }
    cout << field[0].t + k << endl;
    return 0;
}