#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Field {
    int t;  // 开垦耗时
    int c;  // 缩短一天所需资源数量
};

struct Compare {
    bool operator()(const Field& a, const Field& b) {
        if (a.t != b.t) {
            return a.t < b.t;
        } else {
            return a.c > b.c;
        }
    }
};

int main() {
    // n 为田地块数，m 为资源数量，k 为最少开垦天数
    int n, m, k;
    cin >> n >> m >> k;

    // 田地信息
    vector<Field> fields(n);

    // 输入田地信息
    for (int i = 0; i < n; ++i) {
        cin >> fields[i].t >> fields[i].c;
        fields[i].t -= k;
    }

    // 创建优先队列，队列中的元素是田地，按照需要开垦的天数从大到小排序，天数相同则资源消耗小的在前
    priority_queue<Field, vector<Field>, Compare> Q(fields.begin(),
                                                    fields.end());

    while (!Q.empty() && m > 0) {
        Field field = Q.top();
        Q.pop();
        if (field.t <= 0) {
            break;
        }
        // 需要的资源数量
        int need = field.c;
        if (m >= need) {
            m -= need;
            field.t -= 1;
            Q.push(field);
        } else {
            break;
        }
    }

    // 输出最大的开垦天数
    cout << (Q.empty() ? k : Q.top().t + k) << endl;

    return 0;
}
