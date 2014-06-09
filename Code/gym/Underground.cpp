#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

const double MAXV = 1e18;
const int N = (int)3e5 + 10;

struct Group{
    int x, y;
    vector<int> z;
}g1[N], g[N];

int n;

long long sqr(int v){
    return 1ll * v * v;
}

double dist(int i, int j, int k){
    int i1 = (i - 1 + n) % n;
    return sqrt(1.0 * sqr(g[i].x - g[i1].x) + sqr(g[i].y - g[i1].y) + sqr(g[i].z[k] - g[i1].z[j]));
}

vector<vector<int> > prev;
vector<vector<double> > totdis;
void gao(int id, int f1, int t1, int f2, int t2){
    if(f2 > t2) return;
    
    int m1 = f1, m2 = (f2 + t2)/2;
    totdis[id][m2] = MAXV;
    
    for(int i = f1; i <= t1; i ++){
        double d = totdis[id - 1][i] + dist(id, i, m2);
        if(d < totdis[id][m2]){
            totdis[id][m2] = d;
            m1 = i;
            prev[id][m2] = i;
        }
    }
    
    if(f2 != m2) gao(id, f1, m1, f2, m2 - 1);
    if(m2 != t2) gao(id, m1, t1, m2 + 1, t2);
}

double solve(vector<int> &F, vector<int> & T){
//  cout<<F[0]<<' '<<T[0]<<endl;
    if(F[0] > T[0]) return MAXV;
    
    vector<int> M(n);
    M[0] = (F[0] + T[0]) / 2;
    
    for(int i = F[1]; i <= T[1]; i ++){
        prev[1][i] = M[0];
        totdis[1][i] = dist(1, M[0], i);
    }
    for(int i = 2; i < n; i ++){
        gao(i, F[i - 1], T[i - 1], F[i], T[i]);
    }
    
    double ret = MAXV;
    for(int i = F.back(); i <= T.back(); i ++){
        double d = totdis.back()[i] + dist(0, i, M[0]);
        if(d < ret){
            ret = d;
            M.back() = i;
        }
    }
    
    for(int i = n - 2; i > 0; i --){
        M[i] = prev[i + 1][M[i + 1]];
    }
    
    M[0] --;
    if(F[0] <= M[0])ret = min(ret, solve(F, M));
    M[0] += 2;
    if(M[0] <= T[0])ret = min(ret, solve(M, T));
    return ret;
}

int main(){
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    freopen("underground.in", "r", stdin);
    freopen("underground.out", "w", stdout);
    
    scanf("%d", &n);
    
    int mc = 2 * N, loc = 0;
    for(int i = 0; i < n; i ++){
        scanf("%d%d", &g1[i].x, &g1[i].y);
        int c;
        scanf("%d", &c);
        g1[i].z.resize(c);
        for(int j = 0; j < c; j ++)
            scanf("%d", &g1[i].z[j]);
        sort(g1[i].z.begin(), g1[i].z.end());
        
        if(c < mc){
            mc = c;
            loc = i;
        }
    }
    
    if(n == 1){
        printf("0.0\n");
        return 0;
    }
    
    for(int i = 0; i < n; i ++){
        g[i] = g1[(i + loc)%n];
    }
    
    vector<int> F(n), T(n);
    for(int i = 0; i < n; i ++)
        F[i] = 0, T[i] = (int)g[i].z.size() - 1;
    
    prev.resize(n), totdis.resize(n);
    for(int i = 0; i < n; i ++)
        prev[i].resize(g[i].z.size()),
        totdis[i].resize(g[i].z.size());
    
    
    double ans = solve(F, T);
    printf("%.7lf\n", ans);
}
