#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

const int N = (int)5e5;
const int B = 26;

int T;

struct Suffix_Automaton{
	struct State{
		State *par, *go[B], *next;
		int mx, right, cnt;
		
		State(): par(0), next(0), mx(0){
			right = cnt = 0;
			memset(go, 0, sizeof go);
		}
	};
	
	State *root, *last, *cur;
	State *firstMx[N + 5];
	State statePool[N * 2 + 5];
	
	Suffix_Automaton(){
		memset(firstMx, 0, sizeof firstMx);
	}
	
	inline State *newState(int mx){
		State *res = cur++;
		res->mx = mx;
		
		res->next = firstMx[mx];
		firstMx[mx] = res;
		
		return res;
	}
	
	void init(){
		cur = statePool;
		root = last = newState(0);
	}
	
	void extend(int w){
		State *p = last;
		State *np = newState(p->mx + 1);
		np->right = 1;
		
		for(;p && !p->go[w]; p = p->par)
			p->go[w] = np;
		
		if(!p)
			np->par = root;
		else{
			State *q = p->go[w];
			
			if(q->mx == p->mx + 1)
				np->par = q;
			else{
				State *nq = newState(p->mx + 1);
				memcpy(nq->go, q->go, sizeof q->go);
				nq->par = q->par;
				q->par = np->par = nq;
				
				for(;p && p->go[w] == q; p = p->par)
					p->go[w] = nq;
			}
			
		}
		
		last = np;
		
	}
	
	void build(char *buf){
		init();
		
		for(char *pt = buf; *pt; ++pt)
			extend(*pt - 'a');
		
	}
	
	void calc(){
		for(int i = last->mx; i >= 0; --i)
			for(State *t = firstMx[i]; t; t = t->next){
				if(T == 0)
					t->right = 1;
				else if(t->par)
					t->par->right += t->right;
			}
		root->right = 0;
		
		for(int i = last->mx; i >= 0; --i)
			for(State *t = firstMx[i]; t; t = t->next){
			
				t->cnt = t->right;
				
				for(int j = 0; j < B; ++j)
					if(t->go[j]){
						t->cnt += t->go[j]->cnt;
//						printf("go[j] %d\n", t->go[j]->cnt);
					}
				
				
//				printf("mx %d  right %d cnt %d\n", t->mx, t->right, t->cnt);
			}
	}
	
	
	void dfs(State *cur, int k){
//		printf("k %d  mx %d right %d cnt %d\n", k, cur->mx, cur->right, cur->cnt);
		
		k -= cur->right;
		
		if(k <= 0)
			return;
		
		for(int i = 0; i < B; ++i){
			if(!cur->go[i])continue;
			
			int cnt = cur->go[i]->cnt;
			
			if(k <= cnt){
				putchar(i + 'a');
				dfs(cur->go[i], k);
				return;
			}else k -= cnt;
		}
		
	}
	
	void work(int k){
		calc();
		
		if(root->cnt < k)puts("-1");
		else dfs(root, k);
		
	}
	
}sam;

char buf[N + 5];

int main(){
	scanf("%s", buf);
	sam.build(buf);
	
	int k;
	scanf("%d %d", &T, &k);
	sam.work(k);
	
	return 0;
}
