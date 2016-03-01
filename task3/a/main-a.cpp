#include <cmath>
#include <iostream>
#include <iomanip>

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
    if (!pointsAreOnTheSameLine(p, a, b))
        return false;
    return equals((a - p).len() + (b - p).len(), (a - b).len());
}

long double distanceFromPointToLine(Pnt p, Pnt a, Pnt b) {
    if (pointsAreOnTheSameLine(p, a, b))
        return 0;
    return fabs((p - a) % (b - a) / (b - a).len());
}

long double BaseOfPerpendicularIsInsideSegment(Pnt p, Pnt a, Pnt b) {
    Pnt normal = Pnt((b - a).y, - (b - a).x);
    normal = normal * (1 / normal.len());
    long double l = distanceFromPointToLine(p, a, b);
    return pointIsOnSegment(p + normal * l, a, b)
        || pointIsOnSegment(p - normal * l, a, b);

}
int main() {
    freopen("distance4.in", "r", stdin);
    freopen("distance4.out", "w", stdout);
    Pnt p, a, b;
    cin >> p.x >> p.y >> a.x >> a.y >> b.x >> b.y;
    if (BaseOfPerpendicularIsInsideSegment(p, a, b))
        cout << setprecision(10) << distanceFromPointToLine(p, a, b) << endl;
    else
        cout << setprecision(10) << min((p - a).len(), (p - b).len()) << endl;
    return 0;
}