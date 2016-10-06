#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

namespace Program{

const int N = 10000;
const int L = 100000;
const int B = 10;
const int mod = 2012;

namespace sam{
	struct State{
		State *par, *go[B], *next;
		int mx, cnt, val;
		
		void init(){
			par = next = 0;
			memset(go, 0, sizeof go);
			mx = cnt = val = 0;
		}
	};
	
	State statePool[L * 2 + 5], *cur;
	State *root, *last;
	State *firstMx[L + 5];
	
	inline State *newState(int mx){
		State *res = cur++;
		res->init();
		res->mx = mx;
		
		res->next = firstMx[mx];
		firstMx[mx] = res;
		
		return res;
	}
	
	void init(){
		memset(firstMx, 0, sizeof firstMx);
		cur = statePool;
		root = last = newState(0);
	}
	
	void extend(int w){
		State *p = last;
		State *np = newState(p->mx + 1);
		
		while(p && p->go[w] == 0){
			p->go[w] = np;
			p = p->par;
		}
		
		if(p == 0) np->par = root;
		else{
			State *q = p->go[w];
			
			if(q->mx == p->mx + 1) np->par = q;
			else{
				State *nq = newState(p->mx + 1);
				memcpy(nq->go, q->go, sizeof q->go);
				nq->par = q->par;
				q->par = np->par = nq;
				while(p && p->go[w] == q){
					p->go[w] = nq;
					p = p->par;
				}
			}
		}
		
		last = np;
		
	}
	
	void insert(string &s){
		last = root;
		
		for(int i = 0; i < (int)s.length(); ++i)
			extend(s[i] - '0');
			
	}
	
	inline void add(int &x, int y){
		if((x += y) >= mod) x -= mod;
	}
	
	int solve(){
		root->go[0] = 0;
		root->cnt = 1;
		
		int ans = 0;
		
		for(int i = 0; i <= L; ++i)
			for(State *t = firstMx[i]; t; t = t->next){
				add(ans, t->val);
				for(int j = 0; j < B; ++j)
					if(t->go[j]){
						add(t->go[j]->val, (t->val * 10 + j * t->cnt) % mod);
						add(t->go[j]->cnt, t->cnt);
					}
			}
		
		return ans;
	}
};

int n;
string str[N + 5];

bool input(){
	if(scanf("%d", &n) == EOF) return false;
	for(int i = 0; i < n; ++i)
		cin >> str[i];
	return true;
}

void build(){
	sam::init();
	
	for(int i = 0; i < n; ++i)
		sam::insert(str[i]);
	
}

void output(){
	printf("%d\n", sam::solve());
}
//module by 2012
};

int main(){
	//multicases
	while(Program::input()){
		Program::build();
		Program::output();
	}
	return 0;
}
