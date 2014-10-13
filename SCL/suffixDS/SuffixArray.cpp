#include <iostream>
#include <cstring>
#include <cassert>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;


class Suffix_Array{
private:
	static const int N = 100010;
	
	struct Data{
		int head, loc, p;
		Data(){}
		Data(int a, int b):head(a), loc(b){}
		bool operator < (const Data & a) const{
			if(head != a.head) return head < a.head;
			return loc > a.loc;
		}
	};
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
		
		for(int i = 0; i < n; i ++)
			rank[i] --;
		for(int i = 0; i < n; i ++)
			suffix[rank[i]] = i;

		if(rank[0] == 0) h[0] = 0;
		else{
			for(; h[0] <= n - suffix[rank[0] - 1]; h[0] ++){
				if(str[0 + h[0]] != str[suffix[rank[0] - 1] + h[0]])
						break;
			}
		}
		for(int i = 1; i < n; i ++){
			if(rank[i] == 0){
				h[i] = 0; continue;
			}
			int pre = suffix[rank[i] - 1];
			int be = max(h[i - 1] - 1, 0), en = max(n - i, n - pre);
			for(h[i] = be; h[i] <= en; h[i] ++){
				if(str[i + h[i]] != str[pre + h[i]])
					break;
			}
		}
		for(int i = 0; i < n; i ++)
			height[rank[i]] = h[i];
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
public:
	int str[N], suffix[N], rank[N], height[N], h[N], n;	
	
	int mheight[21][N];
	
	Suffix_Array(){}
	void init(vector<int> &_str){
		n = _str.size();
		for(int i = 0; i < _str.size(); i ++)
			str[i] = _str[i];
		str[n] = -1;
		init();
	}
	int lcp(int s1, int s2){
		if(s1 == s2) return n - s2;
		int r1 = rank[s1], r2 = rank[s2];
		
		if(r1 > r2) swap(r1, r2);
		int l, cur;
		for(l = -1, cur = 1; cur <= r2 - r1; cur *= 2, l ++){}
		int ret = mheight[l][r2];
		int loc = r1 + (1 << l);
		ret = min(ret, mheight[l][loc]);
		return ret;
	}
} sa;
