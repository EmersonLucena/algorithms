#include <bits/stdc++.h>

#define MN 1000100

using namespace std;

int divisor[MN], n;

void modified_sieve() {
    for(int i = 1; i < MN; i++)
        divisor[i] = i;

    for(int i = 2; i * i < MN; i++)
        if(divisor[i] == i)
            for(int j = 2*i; j < MN; j += i)
                divisor[j] = i;
}

vector<int> get_prime_divisors(int x) {
    ///Careful with x <= 1
    vector<int> ret;
    while(x != 1) {
        ret.push_back(divisor[x]);
        x /= divisor[x];
    }

    sort(ret.begin(), ret.end());
    return ret;
}

int main() {
    modified_sieve();
    while(1) {
        scanf("%d", &n);

        vector<int> divs = get_prime_divisors(n);
        for(int divi : divs)
            printf("%d ", divi);
        puts("");
    }
    return 0;
}
