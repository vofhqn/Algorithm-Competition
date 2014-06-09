#include <iostream>
#include <cassert>
#include <map>
#include <cstdio>
#include <vector>
using namespace std;

const int Mod = 1000000007;

int n, m;

bool legal(int state){
    for(int i = 1; i < n; i ++){
        if((state & (1 << i)) && (state & (1 << (i - 1))))
            return false;
    }
    return true;
}

vector<int> state;
int stid[1 << 6];
int nextstate[22][1 << 6];

int tiling(int ptstate, int tmstate, int i, int ntstate){
    if(i == 0){
        for(int i = 0; i < n; i ++){
            if((ptstate & (1 << i)) && (tmstate & (1 << i)))
                return -1;
        }
    }
    if(i == n){
        return (1 << stid[ntstate]);
    }
    int ret = 0;
    if((ptstate & (1 << i)) || (tmstate & (1 << i))){
        ret |= tiling(ptstate, tmstate, i + 1, ntstate);
    }else{
        if((i == 0) || !(ntstate & (1 << (i - 1)))){
            ret |= tiling(ptstate, tmstate, i + 1, ntstate | (1 << i));
        }
        if(i < n - 1 && ( !(ptstate & (1 << (i + 1))) && !(tmstate & (1 << (i + 1))))){
            ret |= tiling(ptstate, tmstate, i + 2, ntstate);
        }
        
    }
    return ret;
}
int gao(int posst, int mst){
    int ret = 0;
    bool non = true;
    for(int i = 0; i < (int)state.size(); i ++){
        if(posst & (1 << i)){
            int t = nextstate[i][mst];
            
            if(t == -1) continue;
            
            non = false;
            ret |= nextstate[i][mst];
        }
    }
    if(non) return -1;
    return ret;
}

int main(){
//  freopen("in.txt", "r", stdin);
//  freopen("out.txt", "w", stdout);
    
    cin>> n>> m;
    for(int i = 0; i < (1 << n); i ++){
        if(legal(i)){
            state.push_back(i);
            stid[i] = (int)state.size() - 1;
        }
    }
    
    for(int i = 0; i < state.size(); i ++){
        for(int j = 0; j < (1 << n); j ++){
            nextstate[i][j] = tiling(state[i], j, 0, 0);
        }
    }
    
/*  for(int i = 0; i < 8; i ++){
        cout<<0<<' '<<i<<' '<<nextstate[0][i]<<endl;
    }*/
    
    assert(state[0] == 0);
    
    map<int, int> pst;
    for(int i = 0; i < (1 << n); i ++){
        assert(nextstate[0][i] != -1);
        pst[nextstate[0][i]] ++;
    }
    for(int i = 2; i <= m; i ++){
        map<int, int> nst;
        
        for(map<int, int>::iterator it = pst.begin(); it != pst.end(); it ++){
            for(int mst = 0; mst < (1 << n); mst ++){
                int outst = gao(it -> first, mst);
            
                if(outst == -1) continue;
                
                nst[outst] += it -> second;
                if(nst[outst] >= Mod)
                    nst[outst] -= Mod;
            }
        }
        
        pst = nst;
    }
    
    int ans = 0;
    for(map<int, int>::iterator it = pst.begin(); it != pst.end(); it ++){
        if((it -> first) & 1){
            ans += it->second;
            if(ans >= Mod)
                ans -= Mod;
        }
    }
    cout<<ans<<endl;
}
