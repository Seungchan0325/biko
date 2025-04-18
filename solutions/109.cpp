#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Fenwick2D {
    ll n, m;
    vector<vector<ll>> tree;
    void init(ll _n, ll _m) {
        n = _n;
        m = _m;
        tree.resize(n+1, vector<ll>(m+1));
    }
    void update(ll y, ll x, ll v)
    {
        for(; y <= n; y += y & -y)
            for(ll i = x; i <= m; i += i & -i)
                tree[y][i] += v;
    }
    ll query(ll y, ll x)
    {
        ll ret = 0;
        for(; y > 0; y -= y & -y)
            for(ll i = x; i > 0; i -= i & -i)
                ret += tree[y][i];
        return ret;
    }
};

signed main()
{
    ll n, m, k, q;
    cin >> n >> m >> k >> q;
    
    vector<ll> ans(k+1);
    vector<ll> last(k+1);
    vector<array<tuple<ll, ll, ll, ll>, 4>> Q;
    Q.push_back({});
    for(ll i = 0; i < q; i++) {
        ll op, k, r1, c1, r2, c2;
        cin >> op >> k >> r1 >> c1 >> r2 >> c2;
        ll s = (op == 1 ? 1 : -1);
        Q.push_back({
            tuple{r1, c1, k, s},
            tuple{r2+1, c1, k, -s},
            tuple{r1, c2+1, k, -s},
            tuple{r2+1, c2+1, k, s},
        });
        if(op == 2) ans[k] -= (i - last[k]) * (r2 - r1 + 1) * (c2 - c1 + 1);
        else last[k] = i;
    }
    
    auto query = [&](ll s1, ll s2, ll s3) {
        Fenwick2D f;
        f.init(n, m);
        for(ll i = 1; i <= q; i++) for(auto [r, c, k, s] : Q[i]) {
            ans[k] += s * f.query(r-1, c-1) * (s1 ? -r : 1) * (s2 ? -c : 1) * (s3 ? -i : 1);
            f.update(r, c, s * (s1 ? 1 : r) * (s2 ? 1 : c) * (s3 ? 1 : i));
        }
    };

    query(0, 0, 0);
    query(0, 0, 1);
    query(0, 1, 0);
    query(0, 1, 1);
    query(1, 0, 0);
    query(1, 0, 1);
    query(1, 1, 0);
    query(1, 1, 1);
    
    for(ll i = 1; i <= k; i++) cout << ans[i] << "\n";
}