#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 11111;

int sg[N], skip[N], n, m;
int to[N*10];

int main(){
//  freopen("in.txt", "r", stdin);
//  freopen("out.txt", "w", stdout);
//Gamegame.in / game.out
    freopen("game.in", "r", stdin);
   freopen("game.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%d", &skip[i]);
    
    sg[0] = 0;
    int cnt = 0;
    for(int lane = 1; lane < N; lane ++){
        to[0] = lane;
        for(int i = 0; i < n; i ++){
            int tsg = 0;
            for(int left = lane - skip[i]; left > 0; left -= skip[i]){
                cnt ++;
                tsg ^= sg[left];
                if(tsg >= N) continue;
                to[tsg] = lane;
            }
        }
        for(int i = 0; ; i ++){
            if(to[i] < lane){
                sg[lane] = i;
                break;
            }
        }
    }
//  return 0;
    int m;
    cin>> m;
    for(int cas = 1; cas <= m; cas ++){
        int thissg = 0;
        int t, lane;
        scanf("%d%d", &lane, &t);
        
        for(int i = 0; i < t; i ++){
            int loc;
            scanf("%d", &loc);
            assert(lane + 1 - loc >= 0);
            thissg ^= sg[lane + 1 - loc];
        }
        if(thissg)printf("1\n");
        else printf("2\n");
    }
}
