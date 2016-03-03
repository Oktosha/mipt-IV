#include <cmath>
#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

const long double EPS = 1e-9;

bool equals(long double a, long double b) {
    return fabs(a - b) < EPS; 
}

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
	freopen("intersec4.in", "r", stdin);
    freopen("intersec4.out", "w", stdout);
	int N;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		iPnt o1, o2;
		long long r1, r2;
		cin >> o1.x >> o1.y >> r1;
		cin >> o2.x >> o2.y >> r2;
		fPnt fo1(o1.x, o1.y), fo2(o2.x, o2.y);
		long double fr1(r1), fr2(r2);
		if ((o1 == o2) && (r1 == r2)) {
			printf("3\n");
		} else if ((o1 == o2) && (r1 != r2)) {
			printf("0\n");
		} else if (((o1 - o2).len2() > (r1 + r2) * (r1 + r2))
			|| ((o1 - o2).len2() < (r1 - r2) * (r1 - r2))){
			printf("0\n");
		} else if ((o1 - o2).len2() == (r1 + r2) * (r1 + r2)){
			printf("1\n");
			fPnt ans = fo2 + (fo1 - fo2) * (fr2 / (fo1 - fo2).len());
			printf("%0.10Lf %0.10Lf\n", ans.x, ans.y);
			//if (!(equals((ans - fo1).len(), fr1) 
			//	&& equals((ans - fo2).len(), fr2)))
			//	for(;;);
		} else if ((o1 - o2).len2() == (r1 - r2) * (r1 - r2)) {
			printf("1\n");
			fPnt ans = fo1 + (fo2 - fo1) * (fr1 / (fo1 - fo2).len());
			if (!(equals((ans - fo1).len(), fr1) 
				&& equals((ans - fo2).len(), fr2))) {
				ans = fo2 + (fo1 - fo2) * (fr2 / (fo1 - fo2).len());
			}
			//if (!(equals((ans - fo1).len(), fr1) 
			//	&& equals((ans - fo2).len(), fr2)))
			//	for(;;);
			printf("%0.10Lf %0.10Lf\n", ans.x, ans.y);
		} else {
			printf("2\n");
			//moving coorginates to make first circle be in center
			fPnt moved_o2 = fo2 - fo1;

			//get line from subsctracting
			long double A, B, C;
			A = -2 * moved_o2.x;
			B = -2 * moved_o2.y;
			C = moved_o2.x * moved_o2.x 
				+ moved_o2.y * moved_o2.y 
				- fr2 * fr2 + fr1 * fr1;

			fPnt ans1, ans2;
			if (equals(A, 0)) {
				ans1.y = -C / B;
				ans2.y = -C / B;
				ans1.x = sqrt(fr1 * fr1 - ans1.y * ans1.y);
				ans2.x = -sqrt(fr1 * fr1 - ans2.y * ans2.y);
			} else if (equals(B, 0)) {
				ans1.x = -C / A;
				ans2.x = -C / A;
				ans1.y = sqrt(fr1 * fr1 - ans1.x * ans1.x);
				ans2.y = -sqrt(fr1 * fr1 - ans2.x * ans2.x);
			} else {
				long double a, b, c;
				a = A * A + B * B;
				b = 2 * A * C;
				c = C * C - fr1 * fr1 * B * B;
				long double d;
				d = b * b - 4 * a * c;
				//cout << a << " " << b << " " << c << endl;
				long double x1, x2;
				ans1.x = (-b + sqrt(d)) / (2 * a);
				ans2.x = (-b - sqrt(d)) / (2 * a);
				ans1.y = (- A * ans1.x - C) / B;
				ans2.y = (- A * ans2.x - C) / B;
			}

			ans1 = ans1 + fo1;
			ans2 = ans2 + fo1;
			fPnt h = (ans1 + ans2) * 0.5;

			printf("%0.10Lf %0.10Lf\n", h.x, h.y);
			printf("%0.10Lf %0.10Lf\n", (h - fo1).len(), (ans1 - h).len());
			printf("%0.10Lf %0.10Lf\n", ans1.x, ans1.y);
			printf("%0.10Lf %0.10Lf\n", ans2.x, ans2.y);
		}
	}
	return 0;
}