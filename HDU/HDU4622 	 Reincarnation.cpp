#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

namespace Program{

const int L = 2000;
const int Q = 10000;
const int B = 26;

vector<int>ans[L + 5];

namespace sam{
	
	const int M = L * 2 + 5;
	int par[M], go[M][B], mx[M];
	
	int cur;
	int root, last;
	
	inline int newState(int _mx){
		int res = ++cur;
		par[res] = 0;
		memset(go[res], 0, sizeof go[res]);
		mx[res] = _mx;
		return res;
	}
	
	void init(){
		cur = 0;
		root = last = newState(0);
	}
	
	inline void extend(int w, int id){
		int p = last;
		int np = newState(mx[p] + 1);
		
		while(p && go[p][w] == 0){
			go[p][w] = np;
			p = par[p];
		}
		
		if(p == 0) par[np] = root;
		else{
			int q = go[p][w];
			
			if(mx[q] == mx[p] + 1) par[np] = q;
			else{
				int nq = newState(mx[p] + 1);
				memcpy(go[nq], go[q], sizeof go[q]);
				par[nq] = par[q];
				par[q] = par[np] = nq;
				while(p && go[p][w] == q){
					go[p][w] = nq;
					p = par[p];
				}
			}
		}
		
		last = np;
		
		ans[id].push_back((ans[id].size() ? ans[id].back() : 0)+ mx[np] - mx[par[np]]);
	}
	
}

char str[L + 5];
int q;

void input(){
	scanf("%s", str);
	scanf("%d", &q);
}

void build(){
	int len = strlen(str);
	
	for(int i = 0; i < len; ++i){
		ans[i].clear();
		sam::init();
		for(int j = i; j < len; ++j)
			sam::extend(str[j] - 'a', i);
	}
}

void solve(){
	while(q--){
		int l, r;
		scanf("%d %d", &l, &r);
		--l; --r;
		
		printf("%d\n", ans[l][r-l]);
	}
}

}//namespace Program

int main(){
	int cas; scanf("%d", &cas);
	while(cas--){
		Program::input();
		Program::build();
		Program::solve();
	}
	return 0;
}
