///Use mul_mod if MOD is greater than 10^9

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

map<ll, ll> F;
ll fib(ll x) {
	if(x < 2) return 1;
	if(F.count(x)) return F[x];
	
	ll k = x / 2;	
	if(x % 2) return F[x] = (mul_mod(fib(k), fib(k+1)) + mul_mod(fib(k), fib(k-1)) ) % MOD;
	return F[x] = (mul_mod(fib(k), fib(k)) + mul_mod(fib(k-1), fib(k-1)) ) % MOD;
}
