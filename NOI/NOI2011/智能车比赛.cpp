#include <ctime>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;
typedef double db;
typedef long double ldb;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
#define foreach(it,a) for(__typeof((a).begin()) it=(a).begin();it!=(a).end();++it)
#define rep(i,a,b) for(int i=(a),i##_end_=(b);i<i##_end_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_begin_=(a);i>=i##_begin_;--i) 
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
const int inf=(int)1e9;
const int INF=0x7fffffff;
const ll linf=1LL<<60;
 
const int N = 2000;
const db eps = 1e-9;
int n;
int x[N+5][2], y[N+5][2]; //x[1..n]
int lim[N+5][2]; //lim[2..n]
int sx, sy, tx, ty; //sx <= tx
db v;
int X[N+5], Y[N+5][4]; //X[1..n+1]
void input(){
    scanf("%d", &n);
    rep(i, 1, n+1) scanf("%d %d %d %d", &x[i][0], &y[i][0], &x[i][1], &y[i][1]);
    scanf("%d %d", &sx, &sy);
    scanf("%d %d", &tx, &ty);
    if(sx > tx) swap(sx, tx), swap(sy, ty);
    scanf("%lf", &v);
     
    rep(i, 2, n+1){
        lim[i][0] = max(y[i-1][0], y[i][0]);
        lim[i][1] = min(y[i-1][1], y[i][1]);
    }
     
    rep(i, 1, n+1){
        if(i > 1) assert(X[i] == x[i][0]);
        X[i] = x[i][0]; X[i+1] = x[i][1];
        Y[i][2] = y[i][0]; Y[i][3] = y[i][1];
        Y[i+1][0] = y[i][0]; Y[i+1][1] = y[i][1];
    }
    Y[1][0] = Y[1][2]; Y[1][1] = Y[1][3];
    Y[n+1][2] = Y[n+1][0]; Y[n+1][3] = Y[n+1][1];
    rep(i, 1, n+1+1) sort(Y[i], Y[i]+4);
}
 
namespace P100{
 
const int N = 2000;
db dp[N+5][2];
bool legal(int x0, int y0, int x1, int y1){
    if(x0 == x1) return true;
    if(x0 > x1) swap(x0, x1), swap(y0, y1); //x0 < x1
    db k = (y0-y1)/(db)(x0-x1);
    db b = y0-k*x0;
    rep(i, 2, n+1)if(x0 <= X[i] && X[i] <= x1){
        if(x0 == X[i]){
            if(!(y[i][0]<=y0 && y0<=y[i][1])) return false;
        }else if(x1 == X[i]){
            if(!(y[i-1][0]<=y1 && y1<=y[i-1][1])) return false;
        }else{
            db yy = k*X[i]+b;
            if(!(lim[i][0]<yy+eps && yy-eps<lim[i][1])) return false;
        }
    }
    return true;
}
db distance(int x0, int y0, int x1, int y1){
    return sqrt((x0-x1)*(db)(x0-x1) + (y0-y1)*(db)(y0-y1));
}
void init(){
    rep(i, 2, n+1) rep(j, 0, 2){
        if(legal(sx, sy, X[i], lim[i][j])) dp[i][j] = distance(sx, sy, X[i], lim[i][j]);
        else dp[i][j] = 1e30;
    }
}
void DP(){
    rep(i, 2, n+1) rep(j, 0, 2){
        db tmp = dp[i][j];
        if(tmp > 1e29) continue;
        if(i+1 > n) continue;
        db k[2]; rep(t, 0, 2) k[t] = (lim[i+1][t]-lim[i][j])/(db)(X[i+1]-X[i]);
        rep(a, i+1, n+1){
            db kk[2];
            rep(b, 0, 2){
                kk[b] = (lim[a][b]-lim[i][j])/(db)(X[a]-X[i]);
                if(k[0]<kk[b]+eps && kk[b]-eps<k[1])
                    dp[a][b] = min(dp[a][b], tmp+distance(X[i], lim[i][j], X[a], lim[a][b]));
            }
            k[0] = max(k[0], kk[0]);
            k[1] = min(k[1], kk[1]);
            if(k[0]-k[1]>eps) break;
        }
    }
}
void output(){
    db ans = 1e30;
    if(legal(sx, sy, tx, ty)) ans = distance(sx, sy, tx, ty);
    rep(i, 2, n+1) rep(j, 0, 2){
        if(legal(tx, ty, X[i], lim[i][j])) ans = min(ans, dp[i][j] + distance(tx, ty, X[i], lim[i][j]));
    }
    printf("%.15lf\n", ans/v);
}
void Main(){
    init();
    DP();
    output();
}
 
} // namespace P60
/*
-40000 <= xi, yi <= 40000
1 <= v <= 10
*/
int main(){
    input();
    P100::Main();
    return 0;
}
