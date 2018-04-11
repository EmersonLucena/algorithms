//Catalan Number c(n) is trapezoid(n, n, 1)
//Catalan Triangle c(x, y) is trapezoid(x, y, 1)

//How many strings with x Xs and y Ys such that
// in every prefix #Y does not exceed #X by m or more
ll trapezoid(ll x, ll y, ll m) {
	if(0 <= y && y < m)               return nCr(x + y, y);
	else if(m <= y && y <= x + m - 1) return nCr(x + y, y) - nCr(x + y, y - m); // CAREFUL WITH MOD
	else 				  return 0;
}
