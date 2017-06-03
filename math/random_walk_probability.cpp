#define EPS ...
#define MOD ...

///Fast exponentiation
T expo(T base, long long e) {
    T ret = 1;
    while(e) {
        if(e & 1) ret *= base;
        e /= 2;
        base *= base;
    }
    return ret;
}

/**
 0---i-------N
 Probability of reaching N(winning)
 Variation - Loser gives a coin to the winner
**/
double random_walk(double probability_moving_forward, int i, int N) {
    double p = probability_moving_forward, q = 1 - p;

    if(fabs(p - q) < EPS) return 1.0 * i / N;
    return (1 - expo(q / p, i)) / (1 - expo(q / p, N));
}
