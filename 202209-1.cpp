#include <iostream>
#include <vector>

using namespace std;

int main() {
    // n 为题目数量，m 为神秘数字
    int n, m;
    cin >> n >> m;
    // a 为选项个数，c 为辅助数组
    vector<int> a(n);
    vector<long long> c(n + 1);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n + 1; i++) {
        if (i == 0) {
            c[0] = 1;
            continue;
        }
        c[i] = 1;
        for (int j = 0; j < i; j++)
            c[i] *= a[j];
    }
    int mx = 0;
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = (m % c[i + 1] - mx) / c[i];
        mx += c[i] * b[i];
    }
    for (int i = 0; i < n; i++)
        cout << b[i] << ' ';
    cout << endl;
    return 0;
}