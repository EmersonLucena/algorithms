//Floyd's cycle detection
//Practice problem: http://codeforces.com/group/eqgxxTNwgd/contest/101252/problem/D

using namespace std;
typedef long long ll;

ll a, b, c;

ll f(ll x) {
	return (a * x + (x % b)) % c;
}

//mu -> first ocurrence
//lambda -> cycle length
ll mu, lambda;

void Floyd(ll x0) {
    //hare -> fast pointer
    //tortoise -> slow pointer
    ll hare, tortoise;
    tortoise = f(x0);
    hare = f(f(x0));

    while(hare != tortoise) {
        tortoise = f(tortoise);
        hare = f(f(hare));
    }

    hare = x0;
    mu = 0;

    while(tortoise != hare) {
        tortoise = f(tortoise);
        hare = f(hare);
        mu++;
    }

    hare = f(tortoise);
    lambda = 1;

    while(t != h) {
        hare = f(hare);
        lambda++;
    }
}
