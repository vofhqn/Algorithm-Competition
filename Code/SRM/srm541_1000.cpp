#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>
using namespace std;

int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

map<pair<vector<string>, long long>, long long> mp;

long long solve(vector<string> &maze, long long lt){
	pair<vector<string>, long long> th = make_pair(maze, lt);
	if(mp.find(th) != mp.end()){
		return mp[th];
	}
	
	long long ret = 0;
	int n = maze.size(), m = maze[0].size();
	
	if(lt == 0 && n == 1 && m == 1){
		return mp[th] = (maze[0][0] == 'o');
	}
	if(lt % 2 == 1){
		vector<string> nmaze(n + 2);
		for(int i = 0; i < n + 2; i ++)
			nmaze[i].resize(m + 2);
		for(int i = 0; i < n + 2; i ++){
			for(int j = 0; j < m + 2; j ++){
				int pi = i - 1, pj = j - 1;
				int c = 0;
				if(pi >= 0 && pi < n && pj >= 0 && pj < m){
					c += (maze[pi][pj] == 'o');
				}
				for(int dr = 0; dr < 4 ; dr ++){
					int pi_ = pi + dx[dr], pj_ = pj + dy[dr];
					if(pi_ >= 0 && pi_ < n && pj_>=0 && pj_ < m){
						c+= (maze[pi_][pj_] == 'o');
					}
				}
				if(c % 2 == 1){
					nmaze[i][j] = 'o';
				}else{
					nmaze[i][j] = '.';
				}
			}

		}
		ret += solve(nmaze, lt - 1);
	}else{
		for(int bi = 0; bi < 2; bi ++)if(bi < n)
			for(int bj = 0; bj < 2; bj ++)if(bj < m){
				int nn = (n + 1 - bi)/ 2, nm = (m + 1 - bj) / 2;
				vector<string> nmaze(nn);
				for(int i = 0; i < nn; i ++)
					nmaze[i].resize(nm);
				for(int i = bi, li = 0; i < n; i += 2, li ++)
					for(int j = bj, lj = 0; j < m; j += 2, lj ++){
						nmaze[li][lj] = maze[i][j];
					}
				ret += solve(nmaze, lt / 2);
			}
	}
	return mp[th] = ret;
}

int T, n, m, k;

vector<string> maze;
int main(){
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	cin>> T;
	while(T --){
		cin>> n>> m>> k;
		maze.resize(n);
		for(int i = 0; i < n; i ++)
			cin>> maze[i];
		long long ans = solve(maze, k);
		cout<<ans<<endl;
	}
}
