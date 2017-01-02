#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <ctime>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b)-1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)
 
namespace Program{
 
const int N = 50000;
const int S = 223;
struct Query{
    int l, r, o, id;
    Query(){}
    bool operator <(const Query tmp)const{
        if(o != tmp.o) return o < tmp.o;
        return (o&1) ? r < tmp.r : r > tmp.r;
    }
}q[N+5];
int n, m, c[N+5];
void input(){
    scanf("%d %d", &n, &m);
    rep(i, 1, n+1) scanf("%d", &c[i]);
    rep(i, 0, m){
        scanf("%d %d", &q[i].l, &q[i].r);
        q[i].o = q[i].l/S;
        q[i].id = i;
    }
}
typedef unsigned int ui;
typedef pair<int, int> pii;
pii ans[N+5];
ui sum, cnt[N+5];
inline void move(int pos, int flag){
    sum -= cnt[c[pos]]*cnt[c[pos]];
    cnt[c[pos]] += flag;
    sum += cnt[c[pos]]*cnt[c[pos]];
}
void solve(){
    sort(q, q+m);
    int l = 1, r = 0;
    sum = 0; memset(cnt, 0, sizeof cnt);
    rep(i, 0, m){
        while(q[i].l < l) move(--l, 1);
        while(q[i].l > l) move(l++, -1);
        while(q[i].r < r) move(r--, -1);
        while(q[i].r > r) move(++r, 1);
        int len = r-l+1;
        ans[q[i].id] = pii((sum-len)/2, len*(ui)(len-1)/2);
    }
}
int gcd(int x, int y){
    if(x == 0) return y;
    return gcd(y%x, x);
}
void output(){
    rep(i, 0, m){
        if(ans[i].first == 0) puts("0/1");
        else{
            int d = gcd(ans[i].first, ans[i].second);
            printf("%d/%d\n", ans[i].first/d, ans[i].second/d);
        }
    }
}
void Main(){
    input();
    solve();
    output();
}
 
} //namespace Program
 
/*
 
*/
int main(){
    Program::Main();
    return 0;
}
