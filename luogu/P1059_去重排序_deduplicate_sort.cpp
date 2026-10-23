#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long a;
    cin >> a;

    vector<int> v(a);

    for (int i = 0; i < a; i++) {
        cin >> v[i];
    }

    set<int> s(v.begin(), v.end());

    cout << s.size() << '\n';

    for (int x : s) {
        cout << x << " ";
    }

    return 0;
}
