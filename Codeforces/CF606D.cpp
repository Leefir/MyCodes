#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;
#define foreach(it,a) for(__typeof((a).begin()) it=(a).begin();it!=(a).end();++it)
#define rep(i,a,b) for(int i=(a),i##_end_=(b);i<i##_end_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_begin_=(a);i>=i##_begin_;--i) 
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sz(x) ((int)(x).size())
#define two(x) (1<<(x))
#define twol(x) (1ll<<(x))
#define debug(x) cout<<#x<<" = "<<x<<endl;
typedef vector<int> vi;
typedef vector<string> vs;
typedef long long ll;
typedef double db;
typedef long double ldb;
typedef pair<int,int>pii;
typedef vector<pii> vpii;
const int inf=0x20202020;
const ll mod=1000000007;
const db eps=1e-9;
const db pi=acos(-1);
ll powmod(ll a,ll b){ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}

const int N = (int)1e5;

int n, m;

struct node{
	int val, flag, id;
	node(){}
	node(int _val, int _flag, int _id): val(_val), flag(_flag), id(_id){}
	bool operator <(const node &tmp)const{
		if(val != tmp.val) return val < tmp.val;
		return flag > tmp.flag;
	}
};
vector<node>vec;
void input(){
	scanf("%d %d", &n, &m);
	
	vec.resize(m);
	rep(i, 0, m){
		int val, flag;
		scanf("%d %d", &val, &flag);
		vec[i] = node(val, flag, i);
	}
	sort(all(vec));
	
}

namespace us{
	int fa[N + 5];
	
	void init(){
		rep(i, 0, n) fa[i] = i;
	}
	
	int get(int u){
		if(fa[u] != u) fa[u] = get(fa[u]);
		return fa[u];
	}
	
	void unite(int u, int v){
		fa[get(u)] = get(v);
	}
}

pii ans[N + 5];

void output(){
	rep(i, 0, m) printf("%d %d\n", ans[i].fi + 1, ans[i].se + 1);
}

vpii can;
set<set<int>* >st;

void init(){
	us::init();
	can.clear();
	
	st.clear();
	rep(i, 0, n){
		set<int> *tmp = new set<int>; tmp->clear();
		tmp->insert(i);
		st.insert(tmp);
	}
}

set<int> *merge(set<int> *a, set<int> *b){
	if(a->size() < b->size()) swap(a, b);
	a->insert(b->begin(), b->end());
	delete b;
	return a;
}

void solve(){
	init();
	
	rep(i, 0, sz(vec)){
		int flag = vec[i].flag, id = vec[i].id;
		if(flag == 1){
			//要求不连通
			if(st.size() <= 1){
				puts("-1");
				return;
			}
			set<int> *tmp = *st.begin();st.erase(st.begin());
			set<int> *tmpp = *st.begin();st.erase(st.begin());
			ans[id] = pii(*(tmp->begin()), *(tmpp->begin()));
			us::unite(ans[id].fi, ans[id].se);
			
			for(set<int>::iterator it = tmp->begin(); it != tmp->end(); ++it){
				for(set<int>::iterator jt = tmpp->begin(); jt != tmpp->end(); ++jt){
					if(it == tmp->begin() && jt == tmpp->begin())continue;
					can.pb(pii(*it, *jt));
					if(sz(can) >= m)break;
				}
				if(sz(can) >= m)break;
			}
			
			st.insert(merge(tmp, tmpp));
		}else{
			if(sz(can) == 0){
				puts("-1");
				return;
			}
			ans[id] = pii(can.back().fi, can.back().se);
//			printf("add_edge %d %d\n", can.back().fi + 1, can.back().se + 1);
			can.pop_back();
		}
	}
	
	output();
}

int main(){
	input();
	solve();
	return 0;
}

/*

no loops and multiple edges
*/
