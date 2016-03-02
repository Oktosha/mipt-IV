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



Pnt left_bottom(1000000007, 1000000007);

bool cmp(Pnt a, Pnt b) {
    Pnt av = a - left_bottom;
    Pnt bv = b - left_bottom;
    bool ans = (av % bv > 0)
        || ((av % bv == 0) && av.len2() < bv.len2());
    //cout << "cmp (" << a.x << ", " << a.y << ") (" 
    //    << b.x <<", " << b.y << ") " << (ans?" is true": "is false") << endl;
    //cout <<  av.x <<  " " << av.y  << " " << bv.x << " " << bv.y << endl;
    //cout << "lb " << left_bottom.x << " " << left_bottom.y << endl;
    return ans;
}

bool cornerIsBad(const vector<Pnt>& a, Pnt  p) {
    Pnt corner = a[a.size() - 1];
    Pnt pre = a[a.size() - 2];
    bool ans = ((corner - pre) % (p - corner)) <= 0;

    //cout << "corner (" << pre.x << ", " << pre.y << ") ("
    //    << corner.x << ", " << corner.y << ") ("
    //    << p.x << ", " << p.y << ") is "
    //    << (ans?"bad":"good") << endl;
    return ans;
}

int main() {
    freopen("hull.in", "r", stdin);
    freopen("hull.out", "w", stdout);
    int N;
    cin >> N;
    vector<Pnt> a;
    
    for (int i = 0; i < N; ++i) {
        Pnt p;
        cin >> p.x >> p.y;
        if ((p.y < left_bottom.y)
            || ((p.y == left_bottom.y) && (p.x < left_bottom.x)))
            left_bottom = p;
        a.push_back(p);
    }
    //cout << "Left bottom " << left_bottom.x << " " << left_bottom.y << endl;
    auto it = unique(a.begin(), a.end());
    a.resize(distance(a.begin(), it)); 
    sort(a.begin(), a.end(), cmp);

    //for (Pnt p : a) {
    //    cout << p.x << " " << p.y << endl;
    //}
    vector<Pnt> ans;
    ans.push_back(a[0]);
    ans.push_back(a[1]);
    for (int i = 2; i < a.size(); ++i) {
        while((ans.size() > 1) && (cornerIsBad(ans, a[i]))) {
            ans.pop_back();
        }
        ans.push_back(a[i]);
    }

    cout << ans.size() << endl;
    for (Pnt p : ans) {
        cout << p.x << " " << p.y << endl;
    }

    return 0;
}