#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	freopen ("intersec1.in","r",stdin);
	freopen ("intersec1.out","w",stdout);
	
	long double a1, b1, c1, a2, b2, c2;
	cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
	long double y = (a1 * c2 - a2 * c1) / (a2 * b1 - a1 * b2);
	long double x = (b2 * c1 - b1 * c2) / (a2 * b1 - a1 * b2);
	cout << setprecision(8) << x << " " << y << endl;
	return 0;
}