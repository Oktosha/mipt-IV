#include <cmath>
#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

const long double EPS = 1e-9;

class Pnt {
  public:
    long double x;
    long double y;
    Pnt() : x(0), y(0) {}
    Pnt(long double x, long double y) : x(x), y(y) {}
    Pnt operator + (Pnt other) {
        return Pnt(x + other.x, y + other.y);
    }
    Pnt operator - (Pnt other) {
        return Pnt(x - other.x, y - other.y);
    }
    long double operator * (Pnt other) {
        return x * other.x + y * other.y;
    }
    Pnt operator * (long double k) {
        return Pnt(x * k, y * k);
    }
    long double operator % (Pnt other) {
        return x * other.y - y * other.x;
    }
    long double len() {
        return sqrt(x * x + y * y);
    }
};

bool equals(long double a, long double b) {
    return fabs(a - b) < EPS; 
}

class Line {
  public:
    long double a;
    long double b;
    long double c;
    Line() : a(0), b(0), c(0) {}
    Line(Pnt p, Pnt q) {
        a =  (p - q).y;
        b = -(p - q).x;
        c = -(a * p.x + b * p.y);
        assert(equals(0, a * q.x + b * q.y + c));
    }
};



bool equals(Pnt a, Pnt b) {
    return equals(a.x, b.x) && equals(a.y, b.y); 
}

bool pointsAreOnTheSameLine(Pnt a, Pnt b, Pnt c) {
    Pnt v1 = a - b;
    Pnt v2 = a - c;
    return equals(0, v1 % v2);
}

bool pointIsOnSegment(Pnt p, Pnt a, Pnt b) {
    if (equals(p, a) || equals(p, b))
        return true;
    if (equals(a, b) && !equals(p, a))
        return false;
    if (!pointsAreOnTheSameLine(p, a, b))
        return false;
    return equals((a - p).len() + (b - p).len(), (a - b).len());
}

Pnt crossLines(Line l, Line t) {
    long double y = (l.a * t.c - t.a * l.c) / (t.a * l.b - l.a * t.b);
    long double x = (t.b * l.c - l.b * t.c) / (t.a * l.b - l.a * t.b);
    return Pnt(x, y);
}

bool segmentsAreParallel(Pnt a, Pnt b, Pnt p, Pnt q) {
    return equals((a - b) % (p - q), 0);
}
int main() {
    freopen("intersec2.in", "r", stdin);
    freopen("intersec2.out", "w", stdout);
    Pnt a, b, p, q;
    cin >> a.x >> a.y >> b.x >> b.y >> p.x >> p.y >> q.x >> q.y;
    if (equals(a, b)) {
        if (pointIsOnSegment(a, p, q))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    } else if (equals(p, q)) {
        if (pointIsOnSegment(p, a, b))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    } else if (segmentsAreParallel(a, b, p, q)) {
        if (pointIsOnSegment(a, p, q)
            || pointIsOnSegment(b, p, q)
            || pointIsOnSegment(p, a, b)
            || pointIsOnSegment(q, a, b))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    } else {
        Pnt crossingPoint = crossLines(Line(a, b), Line(p, q));
        if (pointIsOnSegment(crossingPoint, a, b)
            && pointIsOnSegment(crossingPoint, p, q))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}








