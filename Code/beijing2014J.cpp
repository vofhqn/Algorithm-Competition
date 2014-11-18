#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 202, Mod = 1000000007;

struct Long{
	int v;
	
	Long(){v = 0;}
	Long(const Long &o){
		v = o.v;
	}
	Long(int _v):v(_v % Mod){
	}
	
	Long operator + (const Long &other) const{
		int ret = v + other.v;
		if(ret >= Mod) ret -= Mod;
		return Long(ret);
	}
	Long operator - (const Long &other) const{
		int ret = v - other.v;
		if(ret < 0) ret += Mod;
		return Long(ret);
	}
	Long operator * (const Long &other) const{
		int ret = (1ll * v * other.v) % Mod;
		return Long(ret);
	}
	Long operator / (const Long &other) const{
			long long t = Mod - 2, mid = other.v, cur;
			cur = 1;
			while(t){
				if(t & 1) cur = (cur * mid) % Mod;
				mid = (mid * mid) % Mod;
				t /= 2;
			}
		int ret = (1ll * v * cur) % Mod;
		return Long(ret);
	}
	Long operator = (long long a){
		v = a;
	}
};
Long fac[N], comb[N][N];
struct Describer{
	int size;
	Long ways[N], none[N];
	
	Describer(){
		size = 0;
		for(int i = 0; i < N; i ++)
			ways[i] = none[i] = Long(0);
	}
	
	void standardize(){
		ways[size] = Long(fac[size]);
		for(int i = 0; i < size; i ++)
			ways[size] = ways[size] - ways[i];
		Long cur(0);
		for(int i = 0; i < N; i ++) none[i] = Long(0);
		for(int i = 0; i < size; i ++){
			for(int j = 0; j <= i; j ++)
				none[j] = none[j] + ways[i];
		}
		for(int i = 0; i <= size; i ++)
			none[i] = none[i] + ways[size];
	}
};

Describer merge(vector<Describer> &neigh){
	Describer ret;
	ret.size = 0;
	ret.ways[0] = Long(1);
	for(int i = 0; i < neigh.size(); i ++){
		Describer &cur = neigh[i];
		Long temp[N];
		for(int cost = 0; cost <= cur.size; cost ++){
			for(int now = 0; now <= ret.size; now ++){
				temp[now + cost] = temp[now + cost] + 
						(ret.ways[now] * cur.none[cost] * comb[cost + now][cost] * 
							comb[ret.size + cur.size - now - cost][cur.size - cost]);
			}
		}
		for(int j = 0; j <= ret.size + cur.size; j ++)
			ret.ways[j] = temp[j];
		ret.size += cur.size;
	}
	ret.size ++;
	ret.standardize();
	return ret;
}
Describer erase(Describer c, Describer &cur){
	Describer ret = c;
	ret.size -= cur.size;
	ret.ways[0] = Long(fac[ret.size - 1]);
	
	for(int i = 1; i < ret.size; i ++){
		for(int now = 0; now < i; now ++){
			int cost = i - now;
			ret.ways[now + cost] = ret.ways[now + cost] - 
					(ret.ways[now] * cur.none[cost] * comb[cost + now][cost] * 
							comb[ret.size + cur.size - now - cost - 1][cur.size - cost]);
		}
		ret.ways[i] = ret.ways[i] / 
			(cur.none[0] * comb[ret.size - 1 - i + cur.size][cur.size]);
	}
	
	ret.standardize();
	return ret;
}

int T, n;
vector<int> nxt[N];
Describer Each[N];
Long res[N];
int cnt = 0;
void dfs1(int u, int fa){
	vector<Describer> sons;
	for(int i = 0; i < nxt[u].size(); i ++){
		int v = nxt[u][i];
		if(v != fa){
			dfs1(v, u);
			sons.push_back(Each[v]);
		}
	}
	Each[u] = merge(sons);
}
void dfs2(int u, int fa, Describer &cur){
	cnt ++;
	vector<Describer> arr;
	if(cur.size)arr.push_back(cur);
	for(int i = 0; i < nxt[u].size(); i ++){
		int v = nxt[u][i];
		if(v != fa){
			arr.push_back(Each[v]);
		}
	}
	Describer fin = merge(arr);
	res[u] = Long(0);
	for(int i = 0; i < fin.size; i ++)
		res[u] = res[u] + fin.ways[i];
	for(int i = 0; i < nxt[u].size(); i ++){
		int v = nxt[u][i];
		if(v != fa){
			dfs2(v, u, erase(fin, Each[v]));
		}
	}
}
int main(){
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	fac[0] = Long(1);
	for(int i = 1; i < N; i ++)
		fac[i] = fac[i - 1] * Long(1ll * i);
	for(int i = 0; i < N; i ++){
		comb[i][0] = Long(1);
		for(int j = 1; j <= i; j ++)
			comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
	}
	cin>> T;
	for(int cas = 1; cas <= T; cas ++){
		cin>> n;
		for(int i = 0; i < n; i ++)
			nxt[i].clear();
		for(int i = 0; i < n - 1; i ++){
			int u, v; cin>> u>> v;
			u --, v --;
			nxt[u].push_back(v), nxt[v].push_back(u);
		}
		dfs1(0, -1);
		
		dfs2(0, -1, Describer());
		Long result(0);
		for(int i = 0; i < n; i ++){
			result = result + res[i];
		}
		cout<<"Case #"<<cas<<": "<<result.v<<endl;
	}
}
