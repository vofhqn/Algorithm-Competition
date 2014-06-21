//线性筛法+sqrt(n) 每组询问被卡常了- - 懒得改了
#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;
 
const int Mod = (1 << 30);
const int N = 4000000 + 444;
 
int prime[N], factor[N], u[N], squ[N], p[N], cnt;
long long H[N], sH[N];
 
inline int choose2(int n){
	return (1ll * n * (n - 1) / 2)%Mod;
}
 
int main(){
	prime[1] = 1;
	for(int i = 2; i < N; i ++){
		H[i] = i;
		if(!prime[i]) p[cnt ++] = i;
		for(int j = 0; j < cnt && p[j] * i < N; j ++){
			prime[p[j] * i] = 1;
			factor[p[j] * i] = p[j];
			if(i % p[j] == 0)
				break;
		}
	}
 
	u[1] = squ[1] = 1;
	for(int i = 2; i < N; i ++){
		if(prime[i]){
			int temp = i, cnt = 0, f = factor[i];
			while(temp % f == 0 && cnt < 3){
				cnt ++;
				temp /= f;
			}
			if(cnt >= 3){
				H[i] = 0;
			}else if(cnt == 2){
				H[i] = -1ll * f * H[temp];
			}
		}else{
			H[i] = 1 - i;
		}
	}
	H[0] = sH[0] = 0;
	for(int i = 1; i < N; i ++){
		sH[i] = (H[i] + sH[i - 1]) % Mod;
	}
	int T;
	cin>> T;
	while(T --){
		int A, B;
		cin>> A>> B;
		vector<int> seg;
		for(int i = 1; i * i <= A; i ++){
			seg.push_back(i);
			seg.push_back(A/i);
		}
		for(int i = 1; i * i <= B; i ++){
			seg.push_back(i);
			seg.push_back(B/i);
		}
		seg.push_back(0);
		sort(seg.begin(), seg.end());
		seg.erase(unique(seg.begin(), seg.end()), seg.end());
		 
		int ans = 0;
		for(int i = 1; i < seg.size(); i ++){
			long long sum = (sH[seg[i]] - sH[seg[i - 1]] + Mod) % Mod;
			long long temp =(1ll * choose2(A/seg[i] + 1) * choose2(B/seg[i] + 1)) % Mod;
			(ans += (1ll * sum * temp) % Mod) %= Mod;
		}
		cout<<ans<<endl;
	}
}	
