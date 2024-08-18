#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;
const int MAXA = 1000005;

int N, A[MAXN], lst[MAXA];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];

    int ans = 0;
    int len = 0;
    for(int i = 1; i <= N; i++) {
        len = min(i - lst[A[i]], len + 1);
        lst[A[i]] = i;
        ans = max(ans, len);
    }
    cout << ans;
}