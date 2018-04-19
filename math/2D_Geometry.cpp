#define EPS ...
#define INF ...

using namespace std;
typedef double T;

int cmp(T x, T y = 0) {
	return (x <= y + EPS) ? (x + EPS < y) ? -1 : 0 : 1;
}

struct point {
    T x, y;
    int id;

    point(T x = 0, T y = 0, int id = -1): x(x), y(y), id(id) {}

    point operator + (point b) { return point(x + b.x, y + b.y); }
    point operator - (point b) { return point(x - b.x, y - b.y); }
    point operator * (T c) { return point(x*c, y*c); }
    point operator / (T c) { return point(x/c, y/c); }
    bool operator < (const point b) const { return pair<T, T>(x, y) < pair<T, T>(b.x, b.y); }
};

typedef pair<point, point> segm;

point mid_point(point a, point b) {
    return point((a.x + b.x) / 2, (a.y + b.y) / 2);
}

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

/** Counter-clockwise (o is the pivot)**/
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

/** Center of mass of a polygon with uniform mass distribution **/
point polygon_centroid(vector <point> &poly) {
    point ret;
    T area = polygon_area(poly);

    ret.x = (poly.back().x + poly[0].x) * vetorial(poly.back(), poly[0]);
    ret.y = (poly.back().y + poly[0].y) * vetorial(poly.back(), poly[0]);
    for(int i = 1; i < (int)poly.size(); i++) {
        ret.x += (poly[i-1].x + poly[i].x) * vetorial(poly[i-1], poly[i]);
        ret.y += (poly[i-1].y + poly[i].y) * vetorial(poly[i-1], poly[i]);
    }

    ret.x /= (6 * area);
    ret.y /= (6 * area);

    return ret;
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

/** Distance from point to segment **/
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

/** Line perpendicular to line A at point B **/
line perpendicular(line a, point b) {
    T la, lb, lc;
    la = a.b;
    lb = -a.a;
    lc = -la * b.x - lb * b.y;
    return line(la, lb, lc);
}

struct circle {
    point center;
    T rad;

    circle(point c, T r): center(c), rad(r) {}

    circle(point p1, point p2) {
        center = mid_point(p1, p2);
        rad = distPoints(p2 - p1) / 2;
    }

    circle(point p1, point p2, point p3) {
        line l12 (p1, p2);
        line l23 (p2, p3);
        assert(!equal_lines(l12, l23));

        point p12 = mid_point(p1, p2);
        point p23 = mid_point(p2, p3);

        center = intersection(perpendicular(l12, p12), perpendicular(l23, p23));
        rad = distPoints(center - p1);
    }
};

circle mec_solve1(vector<point> &p, int i, int j) {
    circle c(p[i], p[j]);
    for(int k = 0; k < j; k++)
        if(cmp(distPoints(c.center - p[k]), c.rad) == 1)
            c = circle(p[i], p[j], p[k]);
    return c;
}

circle mec_solve2(vector<point> &p, int i) {
    circle c(p[0], p[i]);
    for(int j = 1; j < i; j++)
        if(cmp(distPoints(c.center - p[j]), c.rad) == 1)
            c = mec_solve1(p, i, j);
    return c;
}

circle mec_solve3(vector<point> &p) {
    circle c(p[0], p[1]);
    for(int i = 2; i < (int)p.size(); i++)
        if(cmp(distPoints(c.center - p[i]), c.rad) == 1)
            c = mec_solve2(p, i);
    return c;
}

circle minimum_enclosing_circle(vector<point> p) {
    if(p.size() == 1) return circle{p[0], 0};
    random_shuffle(p.begin(), p.end());
    return mec_solve3(p);
}

point pivot;
bool polar_cmp(point a , point b) {
    T cross = vetorial(a - pivot, b - pivot);
    return cmp(cross) == 1 || (cmp(cross) == 0 && cmp(distPoints(pivot - a), distPoints(pivot - b)) == -1);
}

vector<point> convex_hull(vector<point> p, bool repeat_last = false) {
    if(p.size() <= 2) return p;

    int pi = 0;
    for(int i = 1; i < p.size(); i++)
        if(p[i] < p[pi]) pi = i;

    swap(p[0], p[pi]); pivot = p[0];
    sort(p.begin()+1, p.end(), polar_cmp);

    vector<point> s;
    s.push_back(p.back()); s.push_back(p[0]); s.push_back(p[1]);

    for(int i = 2; i < p.size();) {
        int j = s.size()-1;
        if(s.size() == 2 || ccw(s[j], p[i], s[j-1]) == 1) s.push_back(p[i++]);
        else s.pop_back();
    }
    if(!repeat_last) s.pop_back();
    return s;
}

point ComputeLineIntersection (point a, point b, point c, point d) {
    b = b - a; d = c - d; c = c - a;
    if (escalar(b,b) < EPS) return a;
    if (escalar(d,d) < EPS) return c;
    return a + b*vetorial(c,d)/vetorial(b,d);
}

///Pick a very tight EPS (like 1e-16, use long double if needed)
vector<vector<point> > voronoi(vector<point> p) {
    int n = p.size();

    vector<vector<point> > diagram, ans(p.size() + 4, vector<point>(2));
    vector<point> inv, hull;

    p.resize(p.size() + 4);

    for(int i = 0; i < n; i++) {
        diagram.push_back(vector<point>());

        p[n].x = 2*(-INF) - p[i].x; p[n].y = p[i].y;
        p[n+1].x = p[i].x; p[n+1].y = 2*INF - p[i].y;
        p[n+2].x = 2*INF - p[i].x; p[n+2].y = p[i].y;
        p[n+3].x = p[i].x; p[n+3].y = 2*(-INF) - p[i].y;

        inv.clear();
        for(int j = 0; j < n + 4; j++) {
            if(j == i) continue;
            T tmp = escalar(p[j] - p[i], p[j] - p[i]);
            inv.push_back(point((p[j].x - p[i].x)/tmp, (p[j].y - p[i].y)/tmp, j));
        }

        hull = convex_hull(inv, true);

        for(int j = 0; j < hull.size(); j++) {
            assert(hull[j].id != -1);
            ans[j][0].x = (p[i].x + p[hull[j].id].x) / 2;
            ans[j][0].y = (p[i].y + p[hull[j].id].y) / 2;
            ans[j][1].x = ans[j][0].x - (p[hull[j].id].y - p[i].y);
            ans[j][1].y = ans[j][0].y + (p[hull[j].id].x - p[i].x);

            if(j) diagram[i].push_back(ComputeLineIntersection(ans[j-1][0], ans[j-1][1], ans[j][0], ans[j][1]));
        }
    }

    return diagram;
}

int main() {
    return 0;
}
