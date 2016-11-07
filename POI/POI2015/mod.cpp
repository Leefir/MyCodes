#include <cstdio>
#include <cstring>
#include <cassert>
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b) - 1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

namespace Program{
inline int max(int x, int y){
	if(x > y) return x;
	return y;
}
inline void read(int &res){
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do res = (res * 10) + (c ^ 48);
	while(c = getchar(), c >= '0' && c <= '9');
}
const int N = 500000;
struct Edge{
	int u, v;
	Edge(){}
	Edge(int _u, int _v): u(_u), v(_v){}
	inline int get(int x){
		return u ^ v ^ x;
	}
}edge[N+5];
struct node{
	int id, nxt;
	node(){}
	node(int _id, int _nxt): id(_id), nxt(_nxt){}
}to[N*2+5];
int Gsz, head[N+5];
inline void addEdge(int u, int id){
	to[Gsz] = node(id, head[u]);
	head[u] = Gsz++;
}
void initGraph(const int n){
	rep(i, 0, n) head[i] = -1;
	Gsz = 0;
}
int n;
void input(){
	scanf("%d", &n);
	initGraph(n);
	rep(i, 0, n-1){
		int u, v;
		read(u); read(v);
		--u; --v; //id[0, n)
		edge[i] = Edge(u, v);
		addEdge(u, i);
		addEdge(v, i);
	}
}
int forbiddenEdge;
int ID, dismx;
void IDdfs(int u, int par, int d){
	if(d > dismx) dismx = d, ID = u;
	for(int i = head[u]; ~i; i = to[i].nxt){
		int eid = to[i].id; if(eid == forbiddenEdge) continue;
		int v = edge[eid].get(u); if(v == par) continue;
		IDdfs(v, u, d+1);
	}
}
int seq[N+5], seqe[N+5], seqtot; //直径链 
//seqe[i] 连接 seq[i]和seq[i+1] 
bool findDiameter(int u, int par){
	if(u == ID){seq[seqtot++] = u; return true;}
	for(int i = head[u]; ~i; i = to[i].nxt){
		int eid = to[i].id; if(eid == forbiddenEdge) continue;
		int v = edge[eid].get(u); if(v == par) continue;
		if(findDiameter(v, u)){
			seqe[seqtot-1] = eid;
			seq[seqtot++] = u;
			return true;
		}
	}
	return false;
}
void setDiameter(int rt, int id){
	forbiddenEdge = id;
	ID = dismx = -1; IDdfs(rt, -1, 0); int a = ID;
	ID = dismx = -1; IDdfs(a, -1, 0); //a, ID为直径的两个端点 
	seqtot = 0; findDiameter(a, -1);
//	printf("______dia ");
//	rep(i, 0, seqtot) printf("%d ", seq[i]+1); puts("");
}
int ldia[N+5], rdia[N+5]; //ldia[i]为seq[0, i]的直径
int subdia[N+5], submx[N+5]; //subdia[i]为nodei子树的直径, submx[i]为i往下走能走的最远距离 
void subdfs(int u, int par){
	submx[u] = subdia[u] = 0;
	int mx1 = 0, mx2 = -1;
	for(int i = head[u]; ~i; i = to[i].nxt){
		int eid = to[i].id;
		int v = edge[eid].get(u); if(v == par) continue;
		subdfs(v, u);
		int t = submx[v] + 1;
		if(t >= mx1) mx2 = mx1, mx1 = t;
		else if(t >= mx2) mx2 = t;
		subdia[u] = max(subdia[u], subdia[v]);
	}
	if(mx2 == -1) subdia[u] = max(subdia[u], mx1);
	else subdia[u] = max(subdia[u], mx1 + mx2);
	submx[u] = mx1;
}
void getsub(int id){
	int u = seq[id];
	submx[u] = subdia[u] = 0;
	int mx1 = 0, mx2 = -1;
	for(int i = head[u]; ~i; i = to[i].nxt){
		int eid = to[i].id;
		int v = edge[eid].get(u);
		if(id-1 >= 0 && v == seq[id-1]) continue;
		if(id+1 < seqtot && v == seq[id+1]) continue;
		subdfs(v, u);
		int t = submx[v] + 1;
		if(t >= mx1) mx2 = mx1, mx1 = t;
		else if(t >= mx2) mx2 = t;
		subdia[u] = max(subdia[u], subdia[v]);
	}
	if(mx2 == -1) subdia[u] = max(subdia[u], mx1);
	else subdia[u] = max(subdia[u], mx1 + mx2);
	submx[u] = mx1;
}
void prepare(){
	rep(i, 0, seqtot) getsub(i);
	int mx = 0;//mx为当前点出来能到的最远距离 
	ldia[0] = subdia[seq[0]];
	rep(i, 1, seqtot){
		++mx;
		ldia[i] = ldia[i-1]; //不经过当前点的情况 
		ldia[i] = max(ldia[i], subdia[seq[i]]); //当前点的子树
		ldia[i] = max(ldia[i], mx + submx[seq[i]]); //子树出来和mx接起来
		mx = max(mx, submx[seq[i]]);//更新mx 
	}
	mx = 0;
	rdia[seqtot-1] = subdia[seq[seqtot-1]];
	per(i, 0, seqtot-1){
		++mx;
		rdia[i] = rdia[i+1];
		rdia[i] = max(rdia[i], subdia[seq[i]]);
		rdia[i] = max(rdia[i], mx + submx[seq[i]]);
		mx = max(mx, submx[seq[i]]);
//		printf("rdia[%d] %d\n", seq[i]+1, rdia[i]);
	}
}
int ans1, eid1, ans2, eid2;
void solve1(){
/*第一行输出五个正整数k,x1,y1,x2,y2，其中k表示新树直径的最小值，
x1,y1表示这种情况下要去掉的边的两端点，
x2,y2表示这种情况下要加上的边的两端点。*/
	//使直径变短，删边只可能删直径上的边
	int ans = n, eid = -1;
	rep(i, 0, seqtot-1){
		//删除seqe[i] 即连接seq[i]和seq[i+1]的边
		int l = ldia[i], r = rdia[i+1];
		l = (l+1) / 2; r = (r+1) / 2; //上取整，较长的一段会成为新直径的一部分 
		int now = max(l + r + 1, max(ldia[i], rdia[i+1]));
//		printf("delete %d - %d  now %d\n", seq[i]+1, seq[i+1] + 1, now);
		if(now < ans) ans = now, eid = seqe[i];
	}
	ans1 = ans; eid1 = eid;
}
void solve2(){
/*第二行输出五个正整数k,x1,y1,x2,y2，其中k表示新树直径的最大值，
x1,y1表示这种情况下要去掉的边的两端点，
x2,y2表示这种情况下要加上的边的两端点。*/
	//使直径边长，删边可能删直径上的边或挂在直径上的边
	//删直径上的边，再把两个新树的直径接起来
	int ans = -1, eid = -1;
	rep(i, 0, seqtot-1){
		int now = ldia[i] + rdia[i+1] + 1;
//		printf("delete %d - %d  now %d\n", seq[i]+1, seq[i+1]+1, now);
		if(now > ans) ans = now, eid = seqe[i];
	}
	//删挂在直径上的边，把原直径和掉下来的树的直径接起来
	rep(i, 0, seqtot){
		int u = seq[i];
		for(int j = head[u]; ~j; j = to[j].nxt){
			int id = to[j].id;
			int v = edge[id].get(u);
			if(i-1 >= 0 && v == seq[i-1]) continue;
			if(i+1 < seqtot && v == seq[i+1]) continue;
			int now = (seqtot-1) + subdia[v] + 1;
			if(now > ans) ans = now, eid = id;
		}
	}
	ans2 = ans; eid2 = eid;
}
void output2(int ans, int eid){
	//把两棵树的直径接起来 	
	setDiameter(edge[eid].u, eid); int x2 = seq[0];
	setDiameter(edge[eid].v, eid); int y2 = seq[0];
	printf("%d %d %d %d %d\n", ans, edge[eid].u+1, edge[eid].v+1, x2+1, y2+1);
}
void output1(int ans, int eid){
	//把两棵树的中心接起来
	setDiameter(edge[eid].u, eid); int x2 = seq[seqtot / 2];
	setDiameter(edge[eid].v, eid); int y2 = seq[seqtot / 2];
	printf("%d %d %d %d %d\n", ans, edge[eid].u+1, edge[eid].v+1, x2+1, y2+1);
}
void output(){
	output1(ans1, eid1);
	output2(ans2, eid2);
}
void Main(){
	input();
	setDiameter(0, -1);
	prepare();
	solve1();
	solve2();
	output();
}

} //namespace Program
int main(){
	Program::Main();
	return 0;
}
/*
去掉一条边并加上一条新边
可以去掉并加上同一条边?_?
*/ 

