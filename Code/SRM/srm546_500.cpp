#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

struct Sp{
	int v, c;
}d1, d2;

int T;

long long po10[21];

inline int gbit(long long num, int b){
	if(b == 0) return num % 10;
	return (num / po10[b]) % 10;
}

inline int glen(long long num){
	int ans = 0;
	while(num){
		ans ++;
		num/=10;
	}
	return ans;
}

inline int geq(int a, int b){
	if(a == b) return 1;
	if(a < b) return 0;
	if(a > b) return 2;
}

long long cnt[20][2][3][21][21];//bits/ lead zero/ equal/ c1/ c2
long long count(long long upp){
	if(upp <= 0) return 0;
	
	memset(cnt, 0, sizeof(cnt));
	
	int len = glen(upp);
	if(len == 0) return 0;

	int ub = gbit(upp, 0);
	for(int b = 0; b < 10; b ++){
		int lz = (b == 0), 
			eq = geq(b, ub),
			c1 = (b == d1.v),
			c2 = (b == d2.v);
		cnt[0][lz][eq][c1][c2] ++;
	}

	for(int i = 0; i < len - 1; i ++){
		ub = gbit(upp, i + 1);
			for(int plz = 0; plz < 2; plz ++)
				for(int peq = 0; peq < 3; peq ++){
					for(int c1 = 0; c1 < 21; c1 ++)
						for(int c2 = 0; c2 < 21; c2 ++)if(cnt[i][plz][peq][c1][c2]){
							for(int b = 0; b < 10; b ++){
								int neq = geq(b, ub);
								int eq;
								if(neq != 1) eq = neq;
								else	eq = peq;

								int nlz = (b == 0);
								int cc1 = (b == d1.v), cc2 = (b == d2.v);
								if(cc1 + c1 < 21 && cc2 + c2 < 21){
									cnt[i + 1][nlz][eq][c1 + cc1][c2 + cc2] += cnt[i][plz][peq][c1][c2];
								}
							}
						}
				}
	}
	long long ans = 0;
//	cout<<len<<endl;
	for(int l = 0; l < len; l ++)
	for(int c1 = d1.c; c1 < 21; c1 ++)
		for(int c2 = d2.c; c2 < 21; c2 ++){
			for(int eq = 0; eq < 2; eq ++)
				ans += cnt[l][0][eq][c1][c2];
			if(l != len - 1){
				ans += cnt[l][0][2][c1][c2];
			}			
		}
	return ans;
}

long long solve(long long low){
	long long l = low, r = (1e17), mid, t = -1;
	long long diu = count(low - 1);
	while(l <= r){
		mid = (l + r) / 2;
		long long biu = count(mid);
		if(biu > diu){
			t = mid;
			r = mid - 1;
		}else{
			l = mid + 1;
		}
	}
	return t;
}

long long n;

int main(){
	po10[0] = 1;
	for(int i = 1; i < 21; i ++)
		po10[i] = 10ll * po10[i - 1];
	cin>> T;
	while(T --){
		cin>> n;
		cin>> d1.v>> d1.c>> d2.v>> d2.c;
		if(d1.v > d2.v)
			swap(d1, d2);
		long long ans = solve(n);
		cout<<ans<<endl;
	}
}
