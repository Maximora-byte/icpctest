#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    long long C;
    cin >> n >> C;
    vector<long long> a(n);
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    long long ans = 0;

    for(long long A : a)
    {
        long long B = A - C;

        auto l = lower_bound(a.begin(), a.end(), B);
        auto r = upper_bound(a.begin(), a.end(), B);

        ans += r - l;
    }

    cout << ans << '\n';
    return 0;
}