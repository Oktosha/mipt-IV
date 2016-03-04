#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

class iPnt {
  public:
    long long x;
    long long y;
    iPnt() : x(0), y(0) {}
    iPnt(long long x, long long y) : x(x), y(y) {}
    iPnt operator + (iPnt other) {
        return iPnt(x + other.x, y + other.y);
    }
    iPnt operator - (iPnt other) {
        return iPnt(x - other.x, y - other.y);
    }
    long long operator * (iPnt other) {
        return x * other.x + y * other.y;
    }
    long long operator % (iPnt other) {
        return x * other.y - y * other.x;
    }
    long long len2() {
        return x * x + y * y;
    }
    iPnt ord() {
    	return iPnt(-y, x);
    }
    bool operator == (const iPnt& p) const {
        return x == p.x && y == p.y;
    }
};

class fPnt {
  public:
    long double x;
    long double y;
    fPnt() : x(0), y(0) {}
    fPnt(long double x, long double y) : x(x), y(y) {}
    fPnt operator + (fPnt other) {
        return fPnt(x + other.x, y + other.y);
    }
    fPnt operator - (fPnt other) {
        return fPnt(x - other.x, y - other.y);
    }
    long double operator * (fPnt other) {
        return x * other.x + y * other.y;
    }
    fPnt operator * (long double k) {
        return fPnt(x * k, y * k);
    }
    long double operator % (fPnt other) {
        return x * other.y - y * other.x;
    }
    long double len() {
        return sqrt(x * x + y * y);
    }
    long double len2() {
        return x * x + y * y;
    }
    fPnt ord() {
        return fPnt(-y, x);
    }
};

int main() {
    freopen("tangent.in", "r", stdin);
    freopen("tangent.out", "w", stdout);
    iPnt p0, p1;
    long long r;
    cin >> p0.x >> p0.y >> r >> p1.x >> p1.y;
    cout << setprecision(10);
    if ((p0 - p1).len2() < r * r) {
        cout << 0 << endl;
    } else if ((p0 - p1).len2() == r * r) {
        cout << 1 << endl;
        cout << p1.x << " " << p1.y << endl;
    } else {
        cout << 2 << endl;
        fPnt fp0(p0.x, p0.y), fp1(p1.x, p1.y);
        long double fr = r;
        long double p1p2len = sqrt((fp0 - fp1).len2() - fr * fr);
        long double p3p2len = r * p1p2len / (fp0 - fp1).len();
        long double p1p3len = sqrt(p1p2len * p1p2len - p3p2len * p3p2len);
        fPnt fp3 = fp1 + (fp0 - fp1) * (p1p3len / (fp0 - fp1).len());
        cout << fp3.x << " " << fp3.y << endl;
        cout << p1p3len << " " << p3p2len << endl;
        fPnt h = (fp0 - fp1).ord() * (p3p2len / (fp0 - fp1).len());
        cout << (fp3 + h).x << " " << (fp3 + h).y << endl;
        cout << (fp3 - h).x << " " << (fp3 - h).y << endl;
    }
    return 0;
}