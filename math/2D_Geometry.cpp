#define EPS ...

using namespace std;
typedef double T;

int cmp(double x, double y = 0) {
	return (x <= y + EPS) ? (x + EPS < y) ? -1 : 0 : 1;
}

struct point {
    T x, y;

    point(T x = 0, T y = 0): x(x), y(y) {}

    point operator + (point b) { return point(x + b.x, y + b.y); }
    point operator - (point b) { return point(x - b.x, y - b.y); }
    bool operator < (const point b) const { return tie(x,y) < tie(b.x, b.y); }
};
typedef pair<point, point> segm;

inline T distPoints(point a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

/** Dot product **/
inline T escalar(point a, point b) {
    return a.x * b.x + a.y * b.y;
}

/** Cross product **/
inline T vetorial(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

/** Counter-clockwise **/
int ccw(point p, point q, point o) {
	return cmp(vetorial(p - o, q - o));
}

T angle(point p, point q, point o) {
	point u = p - q, v = o - q;
	return atan2(vetorial(u, v), escalar(u, v));
}

/** Area of polygon **/
T polygon_area(vector <point> &points) {
    T area = vetorial(points.back(), points[0]);
    for(int i=1; i < (int)points.size(); i++)
        area += vetorial(points[i-1], points[i]);

    return abs(area) / 2;
}

struct line {
    T a, b, c;

    line(T a, T b, T c): a(a), b(b), c(c) {}

    line(point p1, point p2):
        a(p1.y - p2.y),
        b(p2.x - p1.x),
        c(p1.x*p2.y - p2.x*p1.y) {}
};

/** Distance from point to line (defined by two other points) **/
inline T point_line(point a, point l1, point l2) {
    return abs(vetorial(l2 - l1, a - l1)) / abs(distPoints(l2 - l1));
}

/** Distance from point to line **/
inline T point_line(point a, line l) {
    return abs(l.a*a.x + l.b*a.y + l.c) / sqrt(l.a*l.a + l.b*l.b);
}

inline T point_segment(segm s, point a) {
    if(escalar(s.second - s.first, a - s.first) < 0)
        return distPoints(a - s.first);

    if(escalar(s.first - s.second, a - s.second) < 0)
        return distPoints(a - s.second);

    return point_line(a, s.first, s.second);
}

bool parallel(line a, line b) {
    return abs(a.b * b.a - a.a * b.b) < EPS;
}

/** Distance between two lines **/
T distLines(line a, line b) {
    if(!parallel(a,b)) return 0;
    if(a.a == 0) return point_line(point(0, -a.c/a.b), b);
    return point_line(point(-a.c/a.a, 0), b);
}

/**Intersection between two lines **/
point intersection(line a, line b) {
    point ret;
    ret.x = (b.c * a.b - a.c * b.b) / (b.b * a.a - a.b * b.a);
    ret.y = (b.c * a.a - a.c * b.a) / (a.b * b.a - b.b * a.a);
    return ret;
}

bool equal_lines(line a, line b) {
    if(!parallel(a,b)) return false;
    return abs(distLines(a,b)) < EPS;
}

line perpendicular(line a, point b) {
    T la, lb, lc;
    la = a.b;
    lb = -a.a;
    lc = -la * b.x - lb * b.y;
    return line(la, lb, lc);
}
