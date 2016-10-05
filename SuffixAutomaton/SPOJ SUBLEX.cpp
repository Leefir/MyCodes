#include <cstdio>
#include <cstring>

const int N = 90000;
const int B = 26;
const int Q = 500;

struct Suffix_Automaton{
	struct State{
		State *par, *go[B], *next;
		int mx, cnt;
		
		State(): par(0), next(0), mx(0){
			memset(go, 0, sizeof go);
		}
	};
	
	State *newState(int mx){
		State *res = new State;
		res->mx = mx;
		
		res->next = firstMx[mx];
		firstMx[mx] = res;
		
		return res;
	}
	
	State *root, *last;
	State *firstMx[N + 5];
	
	Suffix_Automaton(){
		memset(firstMx, 0, sizeof firstMx);
	}
	
	void init(){
		root = last = newState(0);
	}
	
	void extend(int w){
		State *p = last;
		State *np = newState(p->mx + 1);
		
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
			
		for(int i = last->mx; i >= 0; --i){
			for(State *t = firstMx[i]; t; t = t->next){
				t->cnt = (t != root);
				for(int j = 0; j < B; ++j)
					if(t->go[j])
						t->cnt += t->go[j]->cnt;
			}
		}
		
	}
	
	char str[N + 5];
	
	void dfs(char *str, State *cur, int k){
	
		k -= (cur != root);
		
		if(k == 0){
			*str = 0;
			return;
		}
		
		for(int i = 0; i < B; ++i){
			if(!cur->go[i])continue;
			
			int cnt = cur->go[i]->cnt;
			
			if(k<=cnt){
				*str = i + 'a';
				dfs(str+1, cur->go[i], k);
				break;
			}else k -= cnt;
		}
	}
	
	
	char *query(int k){
		dfs(str, root, k);
		return str;
	}
}sam;

char buf[N + 5];

int main(){
	scanf("%s", buf);
	sam.build(buf);
	
	int q;
	scanf("%d", &q);
	
	while(q--){
		int k;
		scanf("%d", &k);
		puts(sam.query(k));
	}
	
	return 0;
}
