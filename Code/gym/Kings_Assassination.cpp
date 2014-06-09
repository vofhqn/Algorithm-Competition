#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

const int N = 100000 + 100;

vector<int> adj[N];

bool color[N], onpath[N];
int depth[N], pre[N];

void dfs1(int u, int f, int d){
    color[u] = true;
    pre[u] = f;
    depth[u] = d;
    for(int i = 0; i < adj[u].size(); i ++){
        int v = adj[u][i];
        if(! color[v]){
            dfs1(v, u, d + 1);
        }
    }
}
int cur, curd;

void dfs2(int u){
    color[u] = true;
    if(onpath[u]){
        if(depth[u] > curd){
            cur = u;
            curd = depth[u];
        }
        return;
    }
    for(int i = 0; i < adj[u].size(); i ++){
        int v = adj[u][i];
        if(!color[v]){
            dfs2(v);
        }
    }   
}

int n, m, s, t;
int main(){
    freopen("assassination.in", "r", stdin);
//  freopen("in.txt", "r", stdin);
//  freopen("out.txt", "w", stdout);
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for(int i = 0; i < m; i ++){
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
    }
    dfs1(s, -1, 1);
    
    if(!color[t]){
        cout<<0<<endl;
        return 0;
    }
    
    int id = t;
    vector<int> que;
    while(id != s){
        onpath[id] = true;
        id = pre[id];
        que.push_back(id);
    }
    que.push_back(s);
    reverse(que.begin(), que.end());
//  for(int i = 1; i < 5; i ++)
//      cout<<pre[i]<<' ';cout<<endl;
    
    for(int i = 0; i <= n; i ++)
        color[i] = false;
        
    cur = s, curd = 1, id = 0;
    
    vector<int> ans;
    
    while(cur != t){
        onpath[que[id]] = false;
        dfs2(que[id ++]);
        if(que[id] == cur)
            ans.push_back(cur);
    }
    sort(ans.begin(), ans.end());
    printf("%d\n", (int)ans.size());
    for(int i = 0; i < ans.size(); i ++){
        if(i) printf(" ");
        printf("%d", ans[i]);
    }printf("\n");
}
