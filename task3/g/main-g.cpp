#include <cmath>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

class Pnt {
  public:
    long long x;
    long long y;
    Pnt() : x(0), y(0) {}
    Pnt(long long x, long long y) : x(x), y(y) {}
    Pnt operator + (Pnt other) {
        return Pnt(x + other.x, y + other.y);
    }
    Pnt operator - (Pnt other) {
        return Pnt(x - other.x, y - other.y);
    }
    long long operator * (Pnt other) {
        return x * other.x + y * other.y;
    }
    long long operator % (Pnt other) {
        return x * other.y - y * other.x;
    }
    long long len2() {
        return x * x + y * y;
    }
    bool operator == (const Pnt& p) const {
        return x == p.x && y == p.y;
    }
};

bool cornersign(Pnt prev, Pnt corner, Pnt next) {
    return signbit((corner - prev) % (next - corner));
}

int main() {
    freopen("polygon.in", "r", stdin);
    freopen("polygon.out", "w", stdout);
    int N;
    cin >> N;
    vector <Pnt> a;
    for (int i = 0; i < N; ++i) {
        Pnt p;
        cin >> p.x >> p.y;
        a.push_back(p);
    }
    bool first_sign = cornersign(a[0], a[1], a[2]);
    bool ans = true;
    for (int i = 0; i < N; ++i) {
        ans = ans && (first_sign 
                == cornersign(a[(N + i - 1) % N], a[i], a[(i + 1) % N]));
    }
    cout << (ans ? "YES" : "NO") << endl;
    return 0;
}