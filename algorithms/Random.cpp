
typedef unsigned long long ull;
ull seed = 0;
ull nxt() {
  seed ^= ull(102938711);
  seed *= ull(109293);
  seed ^= seed >> 13;
  seed += ull(1357900102873);
  return seed;
}
