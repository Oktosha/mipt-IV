#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

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

int main() {
    freopen("area.in", "r", stdin);
    freopen("area.out", "w", stdout);
    int N;
    cin >> N;
    Pnt first, prev, cur;
    cin >> first.x >> first.y;
    prev = first;
    long double ans = 0;
    for (int i = 1; i < N; ++i) {
        cin >> cur.x >> cur.y;
        ans += prev % cur;
        prev = cur;
    }
    ans += cur % first;
    ans = fabs(ans) / 2;
    cout << ans << endl;
    return 0;
}