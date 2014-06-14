#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 300000 + 300;
const long long inf = 1ll * (1e18);

struct Data1{
	int a, b, s, id;
	
	Data1(){}
	Data1(int x, int y, int _id):a(x), b(y), id(_id){
		s = x + y;
	}

	bool operator < (Data1 const &x) const{
		return s < x.s;
	}
};

struct Data2{
	int val, id;

	Data2(){}
	Data2(int a, int b):val(a), id(b){}

	bool operator < (Data2 const &x) const{
		return val < x.val;
	}
};

vector<Data1> d1;
vector<Data2> d2;

int n, w;

int ans[N];

int maxb[N], bid[N], mina[N], aid[N];
long long sum1[N], sum2[2 * N];

long long gs2(int left){
	if(left < 0 || left > (int)d2.size())
		return -1;
	if(left == 0) return 0;
	return sum2[left - 1];
}

int main(){
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	scanf("%d%d", &n, &w);

	for(int i = 0; i < n; i ++){
		int a, b;
		scanf("%d%d", &a, &b);
		b -= a;
		if(b >= a){
			d2.push_back(Data2(a,i));
			d2.push_back(Data2(b,i));
		}else{
			d1.push_back(Data1(a, b, i));
		}
	}

	
	sort(d1.begin(), d1.end());
	sort(d2.begin(), d2.end());



	for(int i = 0; i < d1.size(); i ++){
		if(i == 0){
			maxb[i] = d1[0].b;
			bid[i] = 0;
		}else{
			if(maxb[i - 1] > d1[i].b){
				maxb[i] = maxb[i - 1];
				bid[i] = bid[i - 1];
			}else{
				maxb[i] = d1[i].b;
				bid[i] = i;
			}
		}
	}
	for(int i = (int)d1.size() - 1; i >= 0; i --){
		if(i == (int) d1.size() - 1){
			mina[i] = d1.back().a;
			aid[i] = i;
		}else{
			if(mina[i + 1] < d1[i].a){
				mina[i] = mina[i + 1];
				aid[i] = aid[i + 1];
			}else{
				mina[i] = d1[i].a;
				aid[i] = i;
			}
		}
	}
	for(int i = 0; i < d1.size(); i ++){
		sum1[i] = d1[i].s;
		if(i)
			sum1[i] += sum1[i - 1];
	}
	for(int i = 0; i < d2.size(); i ++){
		sum2[i] = d2[i].val;
		if(i)
			sum2[i] += sum2[i - 1];
	}
	
	if(w == 1){
		int id = -1;
		long long mt = inf;
		if(d2.size() > 0)
			mt = d2[0].val, id = d2[0].id;
		for(int i = 0; i < d1.size(); i ++){
			if(d1[i].a < mt){
				mt = d1[i].a;
				id = d1[i].id;
			}
		}
		cout<<mt<<endl;
		for(int i = 0; i < n; i ++){
			if(i != id)printf("0");
			else	printf("1");
		}
		printf("\n");
		return 0;
	}

	long long mt = inf;
	int loc = -1, ty = -1;
	long long temp = gs2(w);
	if(temp >= 0)
		mt = temp;
	
	for(int i = 0; i < d1.size(); i ++){
		long long s1, s2, s;
		int n1;
		//case1
			s1 = sum1[i];
			n1 = 2 * (i + 1);
			s2 = gs2(w - n1);
			if(s2 >= 0){
				s = s1 + s2;
				if(s < mt){
					mt = s;
					loc = i;
					ty = 1;
				}
			}
		//case2
			if(i < (int)d1.size() - 1){
				s1 = sum1[i] + mina[i + 1];
				n1 = (2 * (i + 1) + 1);
				s2 = gs2(w - n1);
				if(s2 >= 0){
					s = s1 + s2;
					if(s < mt){
						mt = s;
						loc = i;
						ty = 2;
					}
				}
			}
		//case3
			s1 = sum1[i] - maxb[i];
			n1 = 2 * (i + 1) - 1;
			s2 = gs2(w - n1);
			if(s2 >= 0){
				s = s1 + s2;
				if(s < mt){
					mt = s;
					loc = i;
					ty = 3;
				}
			}
	}
	cout<<mt<<endl;
	
	if(ty == -1){
		for(int i = 0; i < w; i ++)
			ans[d2[i].id] ++;
	}else{
		for(int i = 0; i <= loc; i ++){
			ans[d1[i].id] = 2;
		}
		if(ty == 1){
			int upt = w - 2 * (loc + 1);
			for(int i = 0; i < upt; i ++)
				ans[d2[i].id] ++;
		}else if(ty == 2){
			int upt = w - 2 * (loc + 1) - 1;
			for(int i = 0; i < upt; i ++)
				ans[d2[i].id] ++;
			ans[d1[aid[loc + 1]].id] ++;
		}else{
			int upt = w - 2 * (loc + 1) + 1;
			for(int i = 0; i < upt; i ++)
				ans[d2[i].id] ++;
			ans[d1[bid[loc]].id] --;
		}
	}
	
	for(int i = 0; i < n; i ++)
		printf("%d", ans[i]);
	printf("\n");

	return 0;
}
