#include <bits/stdc++.h>

using namespace std;

vector<int> root;

int find(int x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    root[y] = x;
}

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<bool>> a(N+1);
    for(int i = 1; i <= N; i++) {
        a[i].resize(M);
        for(int j = 1; j <= M; j++) {
            char c;
            cin >> c;
            if(c == 'X') {
                a[i][j] = true;
            }
        }
    }

    int cnt = 0;
    vector<vector<int>> v(N+2, vector<int>(M+2));
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= M; c++) {
            if(a[r][c]) {
                v[r][c] = ++cnt;
            }
        }
    }

    root.resize(cnt+1);
    iota(root.begin(), root.end(), 0);

    vector<vector<bool>> up(N+2, vector<bool>(M+2));
    vector<vector<bool>> down(N+2, vector<bool>(M+2));
    for(int c = 1; c <= M; c++) {
        for(int r = 1; r <= N; r++) {
            if(up[r+1][c-1] && down[r-1][c-1]) {
                merge(v[r+1][c-1], v[r-1][c-1]);
                v[r][c] = v[r+1][c-1];
            }
            else if(up[r+1][c-1]) {
                v[r][c] = v[r+1][c-1];
                up[r][c] = true;
            }
            else if(down[r-1][c-1]) {
                v[r][c] = v[r-1][c-1];
                down[r][c] = true;
            }
            else if(a[r][c]){
                up[r][c] = down[r][c] = true;
            }

            if(down[r-1][c] && up[r][c]) {
                merge(v[r-1][c], v[r][c]);
                down[r-1][c] = false;
                up[r][c] = false;
            }
        }
    }

    stack<int> s;
    for(int r = 1; r <= N; r++) {
        if(up[r][M] && s.size()) {
            merge(s.top(), v[r][M]); s.pop();
        }
        if(down[r][M]) s.push(v[r][M]);
    }

    vector<bool> chk(cnt+1);

    int ans = 0;
    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= M; c++) {
            if(v[r][c] && !chk[find(v[r][c])]) {
                ans++;
                chk[find(v[r][c])] = 1;
            }
        }
    }

    cout << ans << "\n";

    chk = vector<bool>(cnt+1);
    vector<pair<int, string>> paths;
    for(int r = N; r >= 1; r--) {
        for(int c = 1; c <= M; c++) {
            if(v[r][c] && !chk[find(v[r][c])]) {
                string path;
                chk[find(v[r][c])] = true;
                path += string(N-r, 'D');
                int R = r;
                int C = c;
                while(R > 1) {
                    if(find(v[R-1][C-1]) == find(v[r][c])) {
                        path += 'R';
                        R--;
                        C--;
                    } else if(find(v[R-1][C+1]) == find(v[r][c])) {
                        path += 'L';
                        R--;
                        C++;
                    } else {
                        path += 'D';
                        R--;
                    }
                }
                reverse(path.begin(), path.end());
                paths.emplace_back(C, path);
            }
        }
    }
    assert(ans == paths.size());
    for(auto& [s, path] : paths) cout << s << " " << path << "\n";

    // for(int r = 1; r <= N; r++) {
    //     for(int c = 1; c <= M; c++) {
    //         cout << v[r][c] << " ";
    //     }
    //     cout << "\n";
    // }
}