#include <iostream>
#include <set>
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 500000 + 500000 + 10;

multiset<int> sd[N];

int n, fat[N], d[N];

inline int gao(int id, int nsd){
//	cout<<"xixi "<<id<<' '<<nsd<<endl;
	if(nsd != 0)
		sd[id].erase(-(nsd - 1));
	sd[id].insert(-(nsd));

	multiset<int>::iterator beg = sd[id].begin();
	multiset<int>::iterator sec = (sd[id].begin());
					   sec ++;

	if(sec == sd[id].end())
		return -(*beg);

	return max(-(*beg), -((*sec) - 1));
}

void change(int id){
	d[id] = 1;
	int now = id;
	while(now != 1){
		int tempd = gao(fat[now], d[now]);
		if(tempd > d[fat[now]]){
			d[fat[now]] = tempd;
		}else{
			break;
		}
		now = fat[now];
	}
}

int main(){
//	cin>> n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
//		cin>> fat[i + 1];
		scanf("%d", &fat[i + 1]);
		change(i + 1);
		multiset<int>::iterator ans = sd[1].begin();
//		cout<< - (*ans)<<' ';
		printf("%d ", -(*ans));
	}printf("\n");
}
