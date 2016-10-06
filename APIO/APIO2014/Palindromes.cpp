#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

namespace Program{

const int L = 300000;
const int B = 26;

namespace sam{
	struct State{
		State *par, *go[B], *next;
		int mx;
		int rcnt, rmx;
		bool vis;
		
		void init(){
			par = next = 0;
			memset(go, 0, sizeof go);
			mx = 0;
			rcnt = rmx = 0;
			vis = false;
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
	
	inline void extend(int w, int pos){
		State *p = last;
		State *np = newState(p->mx + 1);
		np->rcnt = 1;
		np->rmx = pos;
		
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
	
	void build(char *buf){
		init();
		
		for(char *pt = buf; *pt; ++pt)
			extend(*pt - 'a', pt - buf);
		
	}
	
	void calc(){
		for(int i = last->mx; i >= 0; --i)
			for(State *t = firstMx[i]; t; t = t->next)
				if(t->par){
					t->par->rcnt += t->rcnt;
					t->par->rmx = max(t->par->rmx, t->rmx);
				}
	}
	
	long long run(char *buf){
		int len = strlen(buf);
		
		State *t = root;
		int l = 0;
		
		long long ans = 0;
		
		for(int i = len - 1; i >= 0; --i){
			int w = buf[i] - 'a';
			
			while(t && t->go[w] == 0){
				t = t->par;
				if(t) l = t->mx;
			}
			if(t == 0) l = 0, t = root;
			else ++l, t = t->go[w];
			
			
			if(t->rmx < i + l){
				if(t->rmx >= i) ans = max(ans, (long long)t->rcnt * min(t->rmx - i + 1, l));
				State *tmp = t;
				while(tmp && tmp->vis == false){
					tmp->vis = true;
					if(i <= tmp->rmx && tmp->rmx < i + tmp->mx) ans = max(ans, (long long)tmp->rcnt * (tmp->rmx - i + 1));
					tmp = tmp->par;
				}
			}
		}
		
		return ans;
	}
}

char str[L + 5];

void input(){
	scanf("%s" ,str);
}

void build(){
	sam::build(str);
	sam::calc();
}

void solve(){
	cout << sam::run(str) << endl;
}

}

int main(){
	Program::input();
	Program::build();
	Program::solve();
	return 0;
}
