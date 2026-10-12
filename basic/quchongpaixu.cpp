
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // vector 转 set，去重并排序
    set<int> s(a.begin(), a.end());

    // set 转回 vector
    vector<int> b(s.begin(), s.end());

    if (k > b.size()) {
        cout << "NO\n";
    } 
    else {
        cout << b[k - 1] << '\n';
    }

    return 0;
}
