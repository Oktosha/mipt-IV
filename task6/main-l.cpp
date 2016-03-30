#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 100500;
const int MAX_M = 100500;

int perm[MAX_N + 1];
int a[MAX_M][2];

struct Request {
	int t;
	int n;
	int k;
	int l;
	int pos;
	Request(int t, int n, int k, int l, int pos)
		: t(t), n(n), k(k), l(l), pos(pos) {}
	bool operator < (Request r) {
		return pos < r.pos;
	}
	
};


struct RSQ {
	RSQ* left;
	RSQ* right;
	int l;
	int r;
	int sum;
};

RSQ* build();

int main() {
	cin >> N >> M;
	perm[0] = 0;
	for (int i = 1; i <= N; ++i) {
		cin >> perm[i];
	}
	vector<Request> request;
	for (int i = 0; i <= M; ++i) {
		int x, y, k, l;
		cin >> x >> y >> k >> l;
		request.emplace_back(t, i, k, l, x - 1);
		request.emplace_back(t, i, k, l, y);
	}

	sort(request.begin(), request.end());

	return 0;
}