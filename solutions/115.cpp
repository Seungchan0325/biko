#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll f(ll R, int k)
{
    if(R <= 0) return 0;
    if(R == 1) return k;
    ll lg = 63 - __builtin_clzll(R);
    return f(R - (1LL << lg), k^1) + (1LL << (lg-1));
}

int main()
{
    int T;
    cin >> T;
    while(T--) {
        ll K, L, R;
        cin >> K >> L >> R;
        cout << f(R, K&1) - f(L-1, K&1) << "\n";
    }
}