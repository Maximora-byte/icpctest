
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {1, 3, 5, 7, 9, 12, 15};

    int x;
    cin >> x;

    int l = 0;
    int r = a.size() - 1;

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (a[mid] == x) {
            cout << mid << '\n';
            return 0;
        }

        if (a[mid] < x) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << -1 << '\n';
    return 0;
}
