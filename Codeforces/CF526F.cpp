#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b) - 1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

namespace Program{
	const int N = (int)3e5;
	
	int n;
	int a[N + 5];
	
	void input(){
		scanf("%d", &n);
		
		rep(i, 0, n){
			int x, y;
			scanf("%d %d", &x, &y);
			--x; --y;
			a[x] = y;
		}
	}
	
	long long ans;
	
	int lmi[N + 5], lmx[N + 5];
	int rmi[N + 5], rmx[N + 5];
	int cnt[N * 2 + 5];
	void conquer(int l, int r){
		//[l, r)
		int mid = l + (r - l) / 2;
		//[l, mid) [mid, r)
		
		assert(l < mid);
		assert(mid < r);
		
		//prepare lmi,lmx,rmi,rmx
		lmi[mid - 1] = lmx[mid - 1] = a[mid - 1];
		per(i, l, mid - 1) lmi[i] = min(lmi[i + 1], a[i]), lmx[i] = max(lmx[i + 1], a[i]);
		rmi[mid] = rmx[mid] = a[mid];
		rep(i, mid + 1, r) rmi[i] = min(rmi[i - 1], a[i]), rmx[i] = max(rmx[i - 1], a[i]);
		
		//lmi && lmx
		rep(i, l, mid){
			int pos = i + lmx[i] - lmi[i];//[i, pos]
			if(mid <= pos && pos < r) ans += rmx[pos] <= lmx[i] && rmi[pos] >= lmi[i];
		}
		//rmi && rmx
		rep(i, mid, r){
			int pos = i - (rmx[i] - rmi[i]);//[pos, i]
			if(l <= pos && pos < mid) ans += lmx[pos] <= rmx[i] && lmi[pos] >= rmi[i];
		}
		
		//lmi && rmx
		//lmi <= rmi, lmx <= rmx
		//rmx - lmi = r - l  ->  rmx - r = lmi - l
		int mip = mid, mxp = mid;
		per(i, l, mid){
			while(mip< r && lmi[i] <= rmi[mip]) cnt[rmx[mip] - mip + N]++, ++mip;//[mid, mip)
			while(mxp< r && !(lmx[i] <= rmx[mxp])) cnt[rmx[mxp] - mxp + N]--, ++mxp;//[mxp, r)
			if(mxp < mip) ans += cnt[lmi[i] - i + N];
		}
		rep(i, mid, r) cnt[rmx[i] - i + N] = 0;//clear
		
		//lmx && rmi
		//lmx >= rmx, lmi >= rmi
		//lmx - rmi = r - l  ->  lmx + l = rmi + r
		mip = mxp = mid;
		per(i, l, mid){
			while(mxp < r && lmx[i] >= rmx[mxp]) cnt[rmi[mxp] + mxp]++, ++mxp;//[mid, mxp)
			while(mip < r && !(lmi[i] >= rmi[mip])) cnt[rmi[mip] + mip]--, ++mip;//[mip, r)
			if(mip < mxp) ans += cnt[lmx[i] + i];
		}
		rep(i, mid, r) cnt[rmi[i] + i] = 0;//clear
	}
	
	void divide(int l, int r){
		//[l, r)
		if(r - l < 2){
			++ans;
			return;
		}
		
		conquer(l, r);
		
		int mid = l + (r - l) / 2;
		divide(l, mid);
		divide(mid, r);
		
	}
	
	void solve(){
		ans = 0;
		memset(cnt, 0, sizeof cnt);
		
		divide(0, n);
		
		cout << ans <<endl;
	}
	
}//namespace Program

int main(){
	Program::input();
	Program::solve();
	
	return 0;
}

/*
任意一行，任意一列都只会存在一只布丁怪物
正方形
*/
