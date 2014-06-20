#include <iostream>
using namespace std;

const int Mod = 1000000007;
const int N = 2222 + 2222;

int c[N][N], dp[N][N];

class Seatfriends{
	public:
int countseatnumb(int n, int k, int g){
	for(int i = 0; i < N; i ++){
		c[i][0] = 1;
		for(int j = 1; j <= i; j ++)
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % Mod;
	}
	
	dp[1][1] = 1;
	for(int i = 1; i < k; i ++){
		for(int j = 1; j <= g; j ++){
			if(j < g && i + j + 2 <= n){
				dp[i + 1][j + 1] += (1ll * dp[i][j] * j) % Mod;
				if(dp[i + 1][j + 1] >= Mod)
					dp[i + 1][j + 1] -= Mod;
			}
			if(i + 1 + j <= n){
				dp[i + 1][j] += (2ll * dp[i][j] * j) % Mod;
				if(dp[i + 1][j] >= Mod)
					dp[i + 1][j] -= Mod;
			}
			dp[i + 1][j - 1] += (1ll * dp[i][j] * j) % Mod;
			if(dp[i + 1][j - 1] >= Mod)
				dp[i + 1][j - 1] -= Mod;
		}
	}
	if(k == n) return (1ll * dp[k][0] * n) % Mod;
	long long ans = 0;
	int e = n - k;
	for(int i = 1; i <= g; i ++){
		long long temp = (1ll * dp[k][i] * c[e - 1][i - 1]) % Mod;
		ans = (ans + temp) % Mod;
	}
	return (ans * n) % Mod;
}
	};
