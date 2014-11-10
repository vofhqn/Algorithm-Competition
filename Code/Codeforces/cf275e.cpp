#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 100000 + 100;

int n, m, h[N];
pair<int, int> loc[N];

struct Describer{
    int total, maxlen, left, right;
    Describer(){}
    Describer(int a, int b, int c, int d)
            :total(a), maxlen(b), left(c), right(d){}
};
Describer operator + (Describer L, Describer R){
    Describer ret;
    int middle = L.right + R.left;
    int left = (L.left == L.total ? L.total + R.left : L.left),
        right = (R.right == R.total ? R.total + L.right : R.right);
    ret.total = L.total + R.total;
    ret.left = left, ret.right = right;
    ret.maxlen = max(L.maxlen, max(R.maxlen, middle));
    
    return ret;
}

struct Persist{
    Describer des;
    
    Persist(){}
    Persist(Describer a):des(a){}
    Persist(int a, int b, int c, int d){
        des = Describer(a, b, c, d);
    }
    Persist *lson, *rson;
    void build(int l, int r){
        des.total = r - l + 1;
        des.maxlen = des.left = des.right = 0;
        if(l != r){
            lson = new Persist;
            lson -> build(l, (l + r) / 2);
            rson = new Persist;
            rson -> build((l + r) / 2 + 1, r);
        }
    }
    Persist *insert(int loc, int l, int r){
        Persist *ret = new Persist;
        if(l == r){
            ret -> des.total =
                 ret -> des.maxlen = 
                    ret -> des.left = 
                        ret -> des.right = 1;
            ret -> lson = ret -> rson = NULL;
        }else{
            int mid = (l + r) / 2;
            if(loc <= mid){
                ret -> lson = this -> lson -> insert(loc, l, mid);
                ret -> rson = this -> rson;
            }else{
                ret -> lson = this -> lson;
                ret -> rson = this -> rson -> insert(loc, mid + 1, r);
            }
            ret -> des = ret -> lson -> des + ret -> rson -> des;
        }
        return ret;
    }
    Describer query(int l, int r, int he, int en){
        if(l == he && r == en){
            return this -> des;
        }else{
            int mid = (he + en) / 2;
            Describer ll(0, 0, 0, 0), rr(0, 0, 0, 0);
            if(l <= mid)
                ll = this -> lson -> query(l, min(mid, r), he, mid);
            if(r > mid)
                rr = this -> rson -> query(max(mid + 1, l), r, mid + 1, en);
            return ll + rr;
        }
    }
} *sgt[N];
int main(){
    cin>> n;
    for(int i = 0; i < n; i ++){
        cin>> h[i];
        loc[i] = make_pair(h[i], i);
    }
    sort(loc, loc + n);
    reverse(loc, loc + n);
    sgt[0] = new Persist;
    sgt[0] -> build(0, n - 1);
    for(int i = 0; i < n; i ++){
        sgt[i + 1] = sgt[i] -> insert(loc[i].second, 0, n - 1);
    //  cout<<sgt[i + 1] -> query(0, 3, 0, 4).maxlen<<endl;
    }
    cin>> m;
    for(int i = 0; i < m; i ++){
        int ll, rr, ww;
        cin>> ll>> rr>> ww;
        ll --, rr --;
        int binl = 0, binr = n, t = -1, mid;
        while(binl <= binr){
            mid = (binl + binr) / 2;
            Describer des = sgt[mid] -> query(ll, rr, 0, n - 1);
            if(des.maxlen >= ww){
                t = mid;
                binr = mid - 1;
            }else{
                binl = mid + 1;
            }
        }
        cout<<loc[t - 1].first<<endl;
    }
}
