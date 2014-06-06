#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 100010;

const long long Mul = 1000000007;
int Log[N];
struct Suffix_Array{
	int str[N], suffix[N], rank[N], height[N];
	long long hash[N];
	
	int n;
	struct Data{
		int head, loc, p;
		Data(){}
		Data(int a, int b):head(a), loc(b){}
		bool operator < (const Data & a) const{
			if(head != a.head) return head < a.head;
			return loc > a.loc;
		}
	};
	
	long long _pow[N];
	
	int mheight[21][N];
	
	Suffix_Array(){}
	Suffix_Array(vector<int> &_str){
		n = _str.size();
		for(int i = 0; i < _str.size(); i ++)
			str[i] = _str[i];
		str[n] = -1;
		_pow[0] = 1;
		for(int i = 1; i <= (int)_str.size() + 1; i ++)
			_pow[i] = _pow[i - 1] * Mul;
	}
	void init(vector<int> &_str){
		n = _str.size();
		for(int i = 0; i < _str.size(); i ++)
			str[i] = _str[i];
		str[n] = -1;
		_pow[0] = 1;
		for(int i = 1; i <= (int)_str.size() + 1; i ++)
			_pow[i] = _pow[i - 1] * Mul;
	}
	
	inline long long ghash(int h, int e){
		if(e < h) return 0;
		return hash[e] - ((h)?hash[h - 1]:0)*_pow[e - h + 1];
	}
	int to[N];
	void init(){
		vector<Data> data;
		
		for(int i = 0; i <= n; i ++){
			data.push_back(Data(str[i], i));
			to[i] = i;
		}
		sort(data.begin(), data.end());
		data[0].p = 0;
		for(int i = 1; i <= n; i ++){
			data[i].p = ((data[i].head == data[i - 1].head)? data[i - 1].p : i);
			to[data[i].p] = i;
		}
		for(int i = 0; i <= n; i ++){
			suffix[i] = data[i].loc;
			rank[data[i].loc] = i;
		}
		vector<Data> temp;
		for(int len = 1; len <= n; len <<= 1){
			for(int i = 0; i <= n; i ++){
				to[i] = i;
			}
			temp = data;
			
			for(int i = 0; i <= n; i++){
				int loc = data[i].loc;
				if(loc < len) continue;
				
				int dloc = loc - len;
				Data now = data[rank[dloc]];
				int next = to[now.p] ++;
				temp[next] = now;
				
				if(next != now.p){
					Data front = temp[next - 1];
					int jloc = front.loc + len;
					if(data[rank[jloc]].p == data[rank[loc]].p){
						temp[next].p = temp[next - 1].p;
					}
					else{
						temp[next].p = next;
					}
				}			
			}
			
			data = temp;
			for(int i = 0; i <= n; i ++){
				suffix[i] = data[i].loc;
				rank[data[i].loc] = i;
			}	
		}
		
		for(int i = 0; i <= n; i ++){
			hash[i] = (i?hash[i - 1]:0) * Mul + str[i];
		}
		
		for(int i = 2; i <= n; i ++){
			int l = 0, r = min(n - suffix[i] + 1, n - suffix[i - 1] + 1);
			int si = suffix[i], si1 = suffix[i - 1];
			int t = -1, mid;
			while(l <= r){
				mid = (l + r)/2;
				if(ghash(si, si + mid - 1) == ghash(si1, si1 + mid - 1)){
					t = mid;
					l = mid + 1;
				}else{
					r = mid - 1;
				}
			}
			height[i] = t;
		}
		
		height[0] = 0;
		for(int i = 1; i <= n; i ++){
			mheight[0][i] = height[i];
		}
		for(int k = 1; k <= 20; k ++){
			for(int i = 1; i <= n; i ++){
				int ti = i - (1 << (k - 1));
				if(ti > n || ti < 0) continue;
				mheight[k][i] = min(mheight[k - 1][i], mheight[k - 1][ti]);
			}
		}
	}
	int lcp(int s1, int s2){
		int r1 = rank[s1], r2 = rank[s2];
		
		if(r1 > r2) swap(r1, r2);
		int l = Log[r2 - r1];
		int ret = mheight[l][r2];
		int loc = r1 + (1 << l);
		ret = min(ret, mheight[l][loc]);
		return ret;
	}
} sa;
