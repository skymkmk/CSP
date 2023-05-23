#include <algorithm>
#include <iostream>

using namespace std;

bool compare(pair<int, int> a, pair<int, int> b) {
    return a.second > b.second;
}

int main() {
    // n 为田地块数，m 为资源数量，k 为最少开垦天数
    int n, m, k;
    cin >> n >> m >> k;
    // t 为开垦耗时，c 为缩短一天所需资源数量。
    pair<int, int> t[n];
    int c[n];
    for (int i = 0; i < n; i++) {
        t[i].first = i;
        cin >> t[i].second >> c[i];
        // 只关注需要缩减的天数
        t[i].second -= k;
    }
    sort(t, t + n, compare);
    while (m > 0) {
        int consume = 0;
        if (t[0].second <= 0) break;
        // 首先考虑非平均情况
        if (t[0].second > t[1].second) {
            // 单价
            int price = c[t[0].first];
            // 相较下一个田地所能减去的时间
            consume = t[0].second - t[1].second;
            int cost = consume * price;
            if (cost >= m) {
                t[0].second -= m / price;
                m = m - m / price;
                break;
            } else {
                t[0].second -= consume;
                m -= cost;
            }
        }
        else {
            int same_num = 1, price = c[t[0].first], cost = 0;
            // 获取所有相同项的总单价
            for (int i = 0; i < n - 1; i++) {
                if (t[i].second == t[i + 1].second) {
                    same_num++;
                    price += c[t[i + 1].first];
                }
            }
            if (price > m)
                break;
            else {
                if (same_num < n)
                    consume = t[0].second - t[same_num].second;
                else
                    consume = t[0].second;
                cost = consume * price;
                if (cost >= m) {
                    int real_consume = m / price;
                    for (int i = 0; i < same_num; i++)
                        t[i].second -= real_consume;
                    m -= real_consume * price;
                    break;
                }
                else {
                    for (int i = 0; i < same_num; i++)
                        t[i].second -= consume;
                    m -= cost;
                }
            }
        }
    }
    cout << t[0].second + k << endl;
    return 0;
}