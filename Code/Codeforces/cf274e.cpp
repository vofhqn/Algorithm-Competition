#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;

const int N = 2020;
typedef pair<int, int> Pos;

int n, m, k;
int maze[N][N], c[N], r[N], result[N];
int up[N][N], down[N][N], lft[N][N], square[N][N];

int solve(int c, int r){
    int ret = 1;
    int u[N], d[N], p[N];
    u[r] = up[c][r], d[r] = down[c][r];
    for(int i = r + 1; i < m; i ++)
        u[i] = min(u[i - 1], up[c][i]), d[i] = min(d[i - 1], down[c][i]);
    for(int i = r - 1; i >= 0; i --)
        u[i] = min(u[i + 1], up[c][i]), d[i] = min(d[i + 1], down[c][i]);
    p[r] = r;
    int cur = 1;
    while(p[r] - 1 >= 0){
        int gap = r - (p[r] - 1) + 1, height = u[p[r] - 1] + d[p[r] - 1] - 1; 
        int len = min(gap, height);
        if(len <= cur) break;
        cur = len;
        p[r] --;
    }
    ret = max(ret, cur);
    for(int i = r + 1; i < m; i ++){
        p[i] = p[i - 1];
        int gap = i - p[i - 1] + 1, 
                height = min(u[p[i]], u[i]) + min(d[p[i]], d[i]) - 1;
        cur = min(gap, height);
        while(p[i] + 1 <= r){
            gap = i - (p[i] + 1) + 1,
                height = min(u[p[i] + 1], u[i]) + min(d[p[i] + 1], d[i]) - 1;
            int len = min(gap, height);
            if(len < cur) break;
            cur = len;
            p[i] ++;
        }
        ret = max(ret, cur);
    }
    return ret;
}

int main(){
    cin>> n>> m>> k;
    for(int i = 0; i < n; i ++){
        string str; cin>> str;
        for(int j = 0; j < m; j ++){
            maze[i][j] = (str[j] == 'X')? 1 : 0;
        }
    }
    for(int i = 0; i < k; i ++){
        cin>> c[i]>> r[i]; c[i] --, r[i] --;
        maze[c[i]][r[i]] = 1;
    }
    for(int i = 0; i < n; i ++){
        lft[i][0] = (!maze[i][0]);
        for(int j = 1; j < m; j ++)if(!maze[i][j])
            lft[i][j] = lft[i][j - 1] + 1;
    }
    for(int i = 0; i < m; i ++){
        up[0][i] = (!maze[0][i]);
        for(int j = 1; j < n; j ++)if(!maze[j][i])
            up[j][i] = up[j - 1][i] + 1;
        down[n - 1][i] = (!maze[n - 1][i]);
        for(int j = n - 2; j >= 0; j --)if(!maze[j][i])
            down[j][i] = down[j + 1][i] + 1;
    }
    for(int i = 0; i < n; i ++)
        square[i][0] = lft[i][0];
    for(int j = 0; j < m; j ++)
        square[0][j] = up[0][j];
    for(int i = 1; i < n; i ++){
        for(int j = 1; j < m; j ++)if(!maze[i][j]){
            square[i][j] = min(square[i - 1][j - 1] + 1, min(up[i][j], lft[i][j]));
        }
    }
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < m; j ++){
            result[k - 1] = max(result[k - 1], square[i][j]);
        }
    }
    
    for(int j = k - 1; j > 0; j --){
        maze[c[j]][r[j]] = 0;

        up[0][r[j]] = (!maze[0][r[j]]);
        for(int i = 1; i < n; i ++)if(!maze[i][r[j]])
            up[i][r[j]] = up[i - 1][r[j]] + 1;

        down[n - 1][r[j]] = (!maze[n - 1][r[j]]);
        for(int i = n - 2; i >= 0; i --)if(!maze[i][r[j]])
            down[i][r[j]] = down[i + 1][r[j]] + 1;

        int cand = solve(c[j], r[j]);
        result[j - 1] = max(result[j], cand);
    }
    
    for(int i = 0; i < k; i ++){
        cout<<result[i]<<endl;;
    }
    
}
