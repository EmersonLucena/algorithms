#include <bits/stdc++.h>

#define MAXN 250250

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

struct myhash {
	ll chash[MAXN][2];
	ll mult[MAXN][2];
	ll b1, M1, b2, M2;
	
	myhash(ll b1 = 311, ll M1 = 1000000021, ll b2 = 317, ll M2 = 1000000009) :
		b1(b1), M1(M1), b2(b2), M2(M2) { calc();}
	
	void calc() {
		mult[0][0] = mult[0][1] = 1;
		for(ll i=1; i < MAXN; i++) {
			mult[i][0] = (mult[i-1][0] * b1)%M1;
			mult[i][1] = (mult[i-1][1] * b2)%M2;
		}
	}	
	
	// Preprocess new string in global string st
	void compute(string &st) {
		chash[0][0] = chash[0][1] = st[0] + 1;
		for(int i=1; i<(int)st.size();i++) {
			chash[i][0] = ((chash[i-1][0]*b1)%M1 + st[i] + 1)%M1;
			chash[i][1] = ((chash[i-1][1]*b2)%M2 + st[i] + 1)%M2;
		}
	}
	
	// Hash of substring [l, r] INCLUSIVE
	pll substr(ll l, ll r) {
		if(!l) return make_pair(chash[r][0], chash[r][1]);

		ll p1 = (chash[r][0] - (chash[l-1][0] * mult[r-l+1][0])%M1 + M1)%M1;
		ll p2 = (chash[r][1] - (chash[l-1][1] * mult[r-l+1][1])%M2 + M2)%M2;
		return make_pair(p1, p2);
	}
};


char s[MAXN];
string st;

int main() {
	myhash h;
	while(true) {
		scanf(" %s", s);
		st = s;
		h.compute(st);

		int l = 0, r = 0;
		while(true) {
			scanf("%d %d", &l, &r);
			if(l == -1) break;
			pll resp = h.substr(l, r);
			printf("%s\n%lld\n%lld\n\n", st.substr(l, r - l + 1).c_str(), resp.first, resp.second);
		}
	}

	return 0;
}
