#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <iomanip>

using namespace std;

const long long MAX = 10005000;
const long double EPS = 1e-9;
struct HEvent {
	HEvent(long long x, long long y, long long r, long long s) : base_x(x), base_y(y), r(r), s(s) {}
	long long base_x;
	long long base_y;
	long long r;
	long long s;
	long long factX() const {
		return base_x + r * s;
	}
	bool operator < (HEvent e) const {
		return (factX() < e.factX())
			|| ((factX() == e.factX()) && (base_y < e.base_y))
			|| ((factX() == e.factX()) && (base_y == e.base_y) && (s > e.s))
			|| ((factX() == e.factX()) && (base_y == e.base_y) && (s == e.s) && (r > e.r));
	}
};

long long currentX;
struct VEvent {
	VEvent(long long x, long long y, long long r, long long s) : base_x(x), base_y(y), r(r), s(s) {}
	long long base_x;
	long long base_y;
	long long r;
	long long s;
	bool operator == (VEvent e) const  {
	//	cout << "operator eq" << endl;
		return (base_x == e.base_x) && (base_y == e.base_y) && (r == e.r) && (s == e.s);
	}
	long double getYOnCurrentX() const {
		return (long double)(base_y) 
			+ s * sqrt((long double)(r * r - (base_x - currentX) * (base_x - currentX)));
	}
	bool operator < (VEvent e) const {
	//cout << "cmp " << e.base_x << " " << e.base_y << " " << e.r << " " << e.s << " vs " << base_x << " " << base_y << " " << r << " " << s << endl; 
		if (getYOnCurrentX() < e.getYOnCurrentX() - EPS) {
		//	cout << "eps decision " << getYOnCurrentX() << " < " << e.getYOnCurrentX() << endl;
			return true;
		}
		if (getYOnCurrentX() > e.getYOnCurrentX() + EPS) {
		//	cout << "eps decision " << getYOnCurrentX() << " > " << e.getYOnCurrentX() << endl;
			return false;
		}
		if (s < e.s) {
		//	cout << "s decision true" << endl;
			return true;
		}
		if (s > e.s) {
		//	cout << "s decision false" << endl;
			return false;
		}
		if (r > e.r) {
		//	cout << "r decision true";
			return true;
		}
		//cout << "r decision false" << endl;
		return false;
	}
};

int main() {
	freopen("circles.in", "r", stdin);
	freopen("circles.out", "w", stdout);
	int N;
	cin >> N;
	//cout << fixed;
	vector<HEvent> hEvents;
	for (int i = 0; i < N; ++i) {
		long long x, y, r;
		cin >> x >> y >> r;
		hEvents.push_back(HEvent(x, y, r, -1));
		hEvents.push_back(HEvent(x, y, r, 1));
	}
	sort(hEvents.begin(), hEvents.end());
	//cout << "hEvents" << endl;
	//for (auto e : hEvents) {
	//	cout << e.base_x << " " << e.base_y << " " << e.r << " " << e.s << endl;
	//}
	set<VEvent> eventsOnCurrentX;
	long long ans = 0;
	eventsOnCurrentX.insert(VEvent(-MAX, -3 * MAX, 2 * MAX, 1));
	//cout << "Processing" << endl;
	for (auto e : hEvents) {
		currentX = e.factX();
		if (e.s == -1) {
			VEvent cur = VEvent(e.base_x, e.base_y, e.r, -1);
			eventsOnCurrentX.insert(cur);
			//cout << "eventsOnCurrentX = " << currentX << endl;
			//for (auto it : eventsOnCurrentX) {
			//	cout << it.base_x << " " << it.base_y << " " << it.r << " " << it.s << endl;
			//}
			auto it = eventsOnCurrentX.find(cur);
			--it;
			//cout << endl;
			//cout << " cur: " << cur.base_x << " " << cur.base_y << " " << cur.r << " " << cur.s << endl;
			//cout << "prev: " << it->base_x << " " << it->base_y << " " << it->r << " " << it->s << endl;
			//cout << endl;
			if (it->s == 1) {
				eventsOnCurrentX.insert(VEvent(e.base_x, e.base_y, e.r, 1));
				ans += e.r * e.r;
			} else {
				eventsOnCurrentX.erase(VEvent(e.base_x, e.base_y, e.r, -1));
			}
		} else {
			//cout << endl;
			//cout << "erasing " << e.base_x << " " << e.base_y << " " << e.r << endl; 
			eventsOnCurrentX.erase(VEvent(e.base_x, e.base_y, e.r, 1));
			//cout << "erased 1" << endl;
			eventsOnCurrentX.erase(VEvent(e.base_x, e.base_y, e.r, -1));
			//cout << "erased -1" << endl;
			//cout << endl;
		}
	}
	//cout << "Ans" << endl;
	cout.precision(30);
	cout << fixed << ((long double)(ans)) * M_PI << endl;
	return 0;
}