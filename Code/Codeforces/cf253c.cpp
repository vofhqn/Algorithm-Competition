#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

const int N = 500000 + 5;

int n, array[N];

long long solve(int remain, set<pair<int, int> > &v, set<int> &id, set<int> &rid){
	if(remain <= 2) return 0;

	pair<int, int> pivot = *v.begin();
	int loc = pivot.second;
	

	set<int>::iterator lit = id.upper_bound(loc), rit = rid.upper_bound(-loc);
	long long ret = 0;
	if(lit != id.end() && rit != rid.end()){
		ret = min(array[*lit], array[-(*rit)]);
	}else{
		ret = array[loc];
	}
	

	v.erase(pivot);
	id.erase(loc);
	rid.erase(-loc);

	ret += solve(remain - 1, v, id, rid);
	return ret;
}

int main(){
	cin>> n;

	set<pair<int, int> > value;
	set<int> id, rid;
	for(int i = 0; i < n; i ++){
		cin>> array[i];
		value.insert(make_pair(array[i], i));
		id.insert(i);
		rid.insert(-i);
	}

	long long ans = solve(n, value, id, rid);
	cout<<ans<<endl;
}
