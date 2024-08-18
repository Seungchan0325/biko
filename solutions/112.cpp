#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 155;
const ll INF = 1e17;

ll N, X[MAXN], A[MAXN], B[MAXN], DP[MAXN][MAXN], subDP[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> X[i];
    for(int i = 1; i <= N; i++) cin >> A[i];
    for(int i = 1; i <= N; i++) cin >> B[i];

    X[0] = 0;
    X[N+1] = X[N] + 1;
    A[0] = INF;
    A[N+1] = INF;

    for(int len = 0; len <= N+1; len++) {
        for(int i = 0; i + len <= N+1; i++) {
            int j = i + len;
            ll h = (A[i] + A[j] - X[j] + X[i]);

            if(h < 0) {
                DP[i][j] = -INF;
                continue;
            }

            subDP[i] = 0;
            for(int k = i+1; k < j; k++) {
                subDP[k] = -INF;
                if(2*A[k] < h) subDP[k] = subDP[k-1] + B[k];
                for(int l = i+1; l < k; l++) {
                    ll nh = (A[l] + A[k] - X[k] + X[l]);
                    if(nh < 0) continue;
                    if(nh < h) subDP[k] = max(subDP[k], subDP[l-1] + DP[l][k] + B[l] * B[k]);
                }
            }

            DP[i][j] = subDP[j-1];
        }
    }

    cout << DP[0][N+1];
}