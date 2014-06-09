#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>
using namespace std;

const int N = 100000 + 100;

int par[N], x[N], y[N], black[N];
bool vis[N];

int Getp(int u){
    if(u == par[u]){
        return u;
    }
    return par[u] = Getp(par[u]);
}

void Union(int u, int v){
    int fu = Getp(u), fv = Getp(v);
    if(fu == fv) return;
    black[fu] ^= black[fv];
    par[fv] = fu;
}

int n, m;
string s;
vector<int> ans;
vector<int> adj[N];

int dfs(int u){
    int ret = (s[u] == 'B');
    vis[u] = true;
    for(int i = 0; i < adj[u].size(); i ++){
        int v = (u ^ x[adj[u][i]] ^ y[adj[u][i]]);
        if(vis[v]) continue;
        
        int b = dfs(v);
        if(b & 1) ans.push_back(adj[u][i] + 1);
        ret += b;
    }
    return ret;
}
int main(){
//  freopen("in.txt", "r", stdin);
//  freopen("out.txt", "w", stdout);
    freopen("uprtoff.in", "r", stdin);
    freopen("uprtoff.out", "w", stdout);
    
    cin>> n>> m>> s;
    for(int i = 0; i < n; i ++){
        black[i] = (s[i] == 'B');
        par[i] = i;
    }
    for(int i = 0; i < m; i ++){
        cin>> x[i]>> y[i];
        x[i] --, y[i] --;
    }
    
    int cntb = count(black, black + n, 1);
    
    
    for(int i = m - 1; i >= 0; i --){
        int fx = Getp(x[i]), fy = Getp(y[i]);
        
        if(fx == fy) continue;//do not need cycle
        if(black[fx] + black[fy] == 2) cntb -= 2;//pair two black
        
        Union(fx, fy);
        adj[x[i]].push_back(i);
        adj[y[i]].push_back(i);
    }
    
    if(cntb > 0){
        puts("0");
        return 0;
    }
    for(int i = 0; i < n; i ++)
        if(!vis[i])
            dfs(i);
    
    sort(ans.begin(), ans.end());
    for(int i = 0; i < ans.size(); i ++){
        if(i) cout<<' ';
        cout<<ans[i];
    }cout<<endl;
        
}
