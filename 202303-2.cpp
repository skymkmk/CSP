#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

bool comparePair(pair<int, float> a, pair<int, float> b) {
    return a.second < b.second;
}

bool compare(int a, int b) {
    return a > b;
}

int main() {
    // n 为田地块数，m 为资源数量，k 为最少开垦天数
    int n, m, k;
    cin >> n >> m >> k;
    // t 为开垦耗时，c 为缩短一天所需资源数量。
    int t[n], c[n];
    for (int i = 0; i < n; i++) {
        cin >> t[i] >> c[i];
        // 只关注需要缩减的天数
        t[i] -= k;
    }
    pair<int, float> cpt[n];
    for (int i = 0; i < n; i++) {
        cpt[i].first = i;
        cpt[i].second = c[i] * 1.0 / t[i];
    }
    while (m > 0) {
        sort(cpt, cpt + n, comparePair);
        if(cpt[0].second == numeric_limits<int>::max()) break;
        int cost = t[cpt[0].first] * c[cpt[0].first];
        if (cost >= m) {
            int consume = m / c[cpt[0].first];
            cost = consume * c[cpt[0].first];
            m -= cost;
            t[cpt[0].first] -= consume;
            break;
        } else {
            m -= cost;
            t[cpt[0].first] = 0;
            cpt[0].second = numeric_limits<int>::max();
        }
    }
    sort(t, t + n, compare);
    cout << t[0] + k << endl;
    return 0;
}