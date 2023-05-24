#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

bool compare(pair<int, int> a, pair<int, int> b) {
    return a.second > b.second;
}

bool compareDep(pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
}

int main() {
    // n 为时间要求，m 为科目数量
    int n, m;
    cin >> n >> m;
    vector<vector<int>> subjects(m, vector<int>(2));
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < m; j++)
            cin >> subjects[j][i];
    vector<int> earliest(m);
    bool canfinished = true;
    for (int i = 0; i < m; i++) {
        if (subjects[i][0] == 0)
            earliest[i] = 1;
        else {
            earliest[i] =
                earliest[subjects[i][0] - 1] + subjects[subjects[i][0] - 1][1];
            if (earliest[i] + subjects[i][1] - 1 > n)
                canfinished = false;
        }
    }
    for (int i = 0; i < m; i++)
        cout << earliest[i] << ' ';
    cout << endl;
    if (canfinished) {
        // 最晚开始时间
        vector<int> latest(m, 0);
        // 依赖的最早开始时间
        vector<pair<int, int>> dependency_earliest(m);
        for (int i = 0; i < m; i++) {
            dependency_earliest[i].first = i;
            dependency_earliest[i].second = numeric_limits<int>::max();
        }
        // subjects 的复制品
        vector<pair<int, int>> subjects_copy(m);
        for (int i = 0; i < m; i++) {
            subjects_copy[i].first = i;
            subjects_copy[i].second = subjects[i][0];
        }
        sort(subjects_copy.begin(), subjects_copy.end(), compare);
        for (pair<int, int> subject : subjects_copy) {
            if (subject.second == 0)
                break;
            int start = n - subjects[subject.first][1] + 1;
            if (start < dependency_earliest[subject.second - 1].second)
                dependency_earliest[subject.second - 1].second = start;
        }
        sort(dependency_earliest.begin(), dependency_earliest.end(),
             compareDep);
        for (pair<int, int> dep : dependency_earliest) {
            if (dep.second == numeric_limits<int>::max())
                break;
            int sub_dep = subjects[dep.first][0], current = dep.first,
                next_start = dep.second;
            while (true) {
                if (latest[current] == 0) {
                    // 在最晚开始时间和需要花费的时间之间找平衡
                    if (next_start - subjects[current][1] <=
                        n - subjects[current][1] + 1)
                        latest[current] = next_start - subjects[current][1];
                    else
                        latest[current] = n - subjects[current][1] + 1;
                } else {
                    if (latest[current] > next_start - subjects[current][1])
                        latest[current] = next_start - subjects[current][1];
                }
                if (sub_dep == 0)
                    break;
                next_start = latest[current];
                current = sub_dep - 1;
                sub_dep = subjects[current][0];
            }
        }
        for (int i = 0; i < m; i++) {
            if (latest[i] == 0) {
                latest[i] = n - subjects[i][1] + 1;
            }
        }
        for (int i = 0; i < m; i++)
            cout << latest[i] << ' ';
        cout << endl;
    }
    return 0;
}