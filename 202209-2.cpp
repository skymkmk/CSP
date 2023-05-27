#include <iostream>
#include <vector>

using namespace std;

int main() {
    // n 为图书数量，x 为包邮条件
    int n, x;
    cin >> n >> x;
    int sum = 0;
    // a 为图书价格
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        sum += a[i];
    vector<vector<int>> dp(n + 1, vector<int>(sum + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j >= a[i]) {
                int current = dp[i - 1][j - a[i]] + a[i];
                if (current == x)
                    dp[i][j] = x;
                else if (current > x) {
                    if (dp[i - 1][j] >= x) {
                        if (dp[i][j - 1] >= x)
                            dp[i][j] =
                                min(min(current, dp[i - 1][j]), dp[i][j - 1]);
                        else
                            dp[i][j] = min(current, dp[i - 1][j]);
                    } else {
                        if (dp[i][j - 1] >= x)
                            dp[i][j] = min(current, dp[i][j - 1]);
                        else
                            dp[i][j] = current;
                    }
                } else {
                    if (dp[i - 1][j] >= x) {
                        if (dp[i][j - 1] >= x)
                            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]);
                        else
                            dp[i][j] = dp[i - 1][j];
                    }
                    else {
                        if (dp[i][j - 1] >= x)
                            dp[i][j] = dp[i][j - 1];
                            else
                            dp[i][j] = max(current, dp[i - 1][j]);
                    }
                }
            } else
                dp[i][j] = dp[i - 1][j];
        }
    }
    cout << dp[n][sum] << endl;
    return 0;
}