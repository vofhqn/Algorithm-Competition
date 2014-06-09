#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;


const int N = 2222;
const int Mod = 1000000007;

struct Point{
    int x, y;
    bool operator < (Point const &a) const{
        return x < a.x;
    }
}p[N];

int w, h, n;

inline int choose2(int i){
    return (1ll * i * (i + 1) / 2ll) % Mod;
}

int main(){
//  freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    freopen("rectangles.in","r", stdin);
    freopen("rectangles.out","w", stdout);
    cin>> w>> h>> n;
    if(n == 0){
        cout<<(1ll * choose2(w + 1)*choose2(h+1))%Mod<<endl;
        return 0;
    }
    for(int i = 0; i < n; i ++){
        cin>> p[i].x>> p[i].y;
    }
    sort(p, p + n);
    int ans = 0;
    ans = (1ll * choose2(w - p[n - 1].x) * choose2(h + 1)) % Mod;
    for(int i = 0; i < n; i ++){
        if(i != 0 && p[i].x == p[i - 1].x) continue;
        
        int hei = choose2(h + 1);
        int wid = (i>0 ? choose2(p[i].x - p[i - 1].x - 1) : choose2(p[i].x));
        ans = (ans + (1ll * hei * wid) % Mod);
        if(ans >= Mod) ans -= Mod;
    }
    //cout<<ans<<endl;
    for(int i = 0; i < n; i ++){
        set<pair<int, int> > yseg;
        yseg.insert(make_pair(h, 0));
        int cy = choose2(h + 1);
        int head = ((i == 0) ? (p[i].x + 1) : (p[i].x - p[i - 1].x));
        int tail;
        for(int j = i; j < n; j ++){
            tail = ((j == n - 1)?(w + 1 - p[j].x): (p[j + 1].x - p[j].x));
            int y_ = p[j].y;
            
            set<pair<int, int> >::iterator it = yseg.lower_bound(make_pair(y_, -1));
            if(it == yseg.end()){
                int temp = (1ll * (1ll * head * tail)%Mod * cy) % Mod;
                ans = (ans + temp) % Mod;
                continue;
            }
            pair<int, int> th = (*it);
            if(th.second > y_){
                int temp = (1ll * (1ll * head * tail)%Mod * cy) % Mod;
                ans = (ans + temp) % Mod;
                continue;
            }
            cy -= choose2(th.first - th.second + 1);
            if(cy < 0) cy += Mod;
            
            yseg.erase(it);
            if(y_ > th.second) {
                yseg.insert(make_pair(y_-1, th.second));
                cy += choose2(y_-1-th.second + 1);
                if(cy >= Mod)
                    cy -= Mod;
            }
            if(y_ < th.first){
                yseg.insert(make_pair(th.first, y_+1));
                cy += choose2(th.first - (y_+1) + 1);
                if(cy >= Mod)
                    cy -= Mod;
            }
            int temp = (1ll * (1ll * head * tail)%Mod * cy) % Mod;
            ans = (ans + temp) % Mod;
        }
    }
    cout<<ans<<endl;
}
