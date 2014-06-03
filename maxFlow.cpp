	namespace maxFlow{
const int INF = 1000000000;
const int maxN = 202;
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
