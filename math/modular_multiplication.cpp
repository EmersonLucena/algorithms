///Multiplication without overflow

#define MOD ...
typedef long long ll;

ll mul_mod(ll a, ll b) {
	ll ret = 0;
	a %= MOD;
	while(b) {
		if(b % 2) ret = (ret + a) % MOD;
		a = (a * 2) % MOD;
		b /= 2;
	}
	return ret;
}
