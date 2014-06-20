#include <iostream>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

	namespace maxFlow{
const int INF = 1000000000;
const int maxN = 6000;
const int maxE = 40000;
int n, e;
int S,T,d[maxN],q[maxN],v[maxN],b[maxN],a[maxE][3],tot;
void clear(){
	S = T = 0;
	tot = 1;
	for(int i = 0; i < maxN; i ++)
		d[i] = q[i] = v[i] = b[i]= 0;
	for(int i = 0; i < maxE; i ++)
		for(int j = 0; j < 3; j ++)
			a[i][j] = 0;
}
void add(int u, int v, int c){
    a[++tot][0]=v,a[tot][1]=c,a[tot][2]=b[u],b[u]=tot;
    a[++tot][0]=u,a[tot][1]=0,a[tot][2]=b[v],b[v]=tot;
}
bool build()
{
    int l,r;
    q[l=r=1]=S;
    memset(d,0,sizeof(d));
    d[S]=1;
    while (l<=r)
    {
        int x=q[l++];
        for (int i=b[x];i;i=a[i][2])
        {
            int y=a[i][0];
            if (d[y] || !a[i][1])
                continue;
            d[y]=d[x]+1;
            q[++r]=y;
            if (y==T)
                return(true);
        }
    }
    return(false);
}
int dinic(int x,int flow)
{
    if (x==T)
        return(flow);
    int k=flow;
    for (int i=b[x];i;i=a[i][2])
    {
        int y=a[i][0];
        if (d[y]!=d[x]+1 || !a[i][1])
            continue;
        int t=dinic(y,min(k,a[i][1]));
        k-=t;
        a[i][1]-=t;
        a[i^1][1]+=t;
        if (k==0)
            break;
    }
    if (k==flow)
        d[x]=-1;
    return(flow-k);
}
int maxflow(){
	int ret = 0;
	while(build()){
		ret += dinic(S, INF);	
	}
	return ret;
}
	}
int dx[] = {3, 0, -3, 0}, dy[] = {0, 3, 0, -3};
vector<string> maze;
class BlockTheBlockPuzzle{
	public:
int n, m;
int id(int x, int y, int t){
	return 1 + x * m + y + t * n * m;
}
int minimumHoles(vector<string> _maze){
	maxFlow::clear();
	n = _maze.size();
	m = _maze[0].length();
	
	maze = _maze;
	int ans = 10000;
	
	maxFlow::S = 0;
	for(int i = 0; i < n; i ++){
		for(int j = 0; j < m; j ++){
			int c;
			if(maze[i][j] == 'H')c = 0;
			else if(maze[i][j] == 'b' || maze[i][j] == '$') c = 10000000;
			else	c = 1;
			maxFlow::add(id(i, j, 0), id(i, j, 1), c); 
			if(i == 3 && j == 6){
				cout<<"haha "<<c<<endl;
			}
		}
	}
	for(int i = 0; i < n; i ++){
		for(int  j= 0; j < m; j ++)if(maze[i][j] != 'H'){
			int id0 = id(i, j, 0), id1 = id(i, j, 1);
			if(maze[i][j] == '$'){
				maxFlow::T = id0;
			}
			if(maze[i][j] == 'b'){
				maxFlow::add(maxFlow::S, id0, 10000000);
			}
			for(int d = 0; d < 4; d ++){
				int ni = i + dx[d], nj = j + dy[d];
				
				if(ni >= 0 && ni < n && nj >= 0 && nj < m && maze[ni][nj] != 'H'){
					int cnt = 0;
					if(d == 0){
						for(int ti = i + 1; ti < ni; ti ++){
							if(maze[ti][j] == '.')cnt ++;
							if(maze[ti][j] == 'b')cnt += 10000000;
						}
					}
					if(d == 1){
						for(int tj = j + 1; tj < nj; tj ++){
							if(maze[i][tj] == '.')cnt ++;
							if(maze[i][tj] == 'b')cnt += 10000000;
						}
					}
					if(d == 2){
						for(int ti = ni + 1; ti < i; ti ++){
							if(maze[ti][j] == '.')cnt ++;
							if(maze[ti][j] == 'b')cnt += 10000000;
						}
					}
					if(d == 3){
						for(int tj = nj + 1; tj < j; tj ++){
							if(maze[i][tj] == '.')cnt ++;
							if(maze[i][tj] == 'b')cnt += 10000000;
						}
					}
					maxFlow::add(id1, id(ni, nj, 0), cnt);
					if(i == 3 &&  j== 6 && d == 3){
						cout<<"hehe "<<cnt<<' '<<id1<<' '<<id(ni, nj, 0)<<' '<<maxFlow::T<<endl;
					}
				}
			}
		}
	}
	ans = maxFlow::maxflow();
	if(ans >= 1000000)return -1;
	return ans;
}
	};
