#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <algorithm>

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
	bool operator < (Request r) const {
		return pos < r.pos;
	}
	
};


struct RSQ {
	RSQ(int l, int r): l(l), r(r), left(nullptr), right(nullptr), sum(0) {}
	int l;
	int r;
	RSQ* left;
	RSQ* right;
	int sum;
};

RSQ* build(int l, int r) {
	RSQ* root = new RSQ(l, r);
	if (l < r) {
		root->left = build(l, (l + r)/2);
		root->right = build(((l + r) / 2) + 1, r);
	}
	return root;
}

int sum(RSQ* root, int l, int r) {
	assert((root->l <= l) && (r <= root->r));
	if ((root->l == l) && (root->r == r))
		return root->sum;
	int ans = 0;
	if (l <= root->left->r) {
		ans += sum(root->left, l, min(r, root->left->r));
	}
	if (r >= root->right->l) {
		ans += sum(root->right, max(l, root->right->l), r);
	}
	return ans;
}

void inc(RSQ* root, int x) {
	//cout << "l r x " << root->l << " " << root->r << " " << x << endl;
	assert((root->l <= x) && (x <= root->r));
	root->sum += 1;
	if (root->l == root->r) {
		return;
	}
	if (x <= root->left->r) {
		inc(root->left, x);
	} else {
		inc(root->right, x);
	}
}

int main() {
	ifstream fin;
	ofstream fout;
	fin.open("permutation.in");
	fout.open("permutation.out", std::ofstream::out);
	ios_base::sync_with_stdio(0);
	int N, M;
	fin >> N >> M;
	perm[0] = 0;
	for (int i = 1; i <= N; ++i) {
		fin >> perm[i];
	}
	vector<Request> request;
	for (int i = 0; i <= M; ++i) {
		int x, y, k, l;
		fin >> x >> y >> k >> l;
		request.emplace_back(0, i, k, l, x - 1);
		request.emplace_back(1, i, k, l, y);
	}

	sort(request.begin(), request.end());
	RSQ *rsq = build(1, N);
	int cur_pos = 0;
	for (auto req : request) {
		while(cur_pos < req.pos) {
			++cur_pos;
			//cout << "inc " << perm[cur_pos] << endl;
			inc(rsq, perm[cur_pos]);
		}
		a[req.n][req.t] = sum(rsq, req.k, req.l);
	}

	for (int i = 0; i < M; ++i) {
		fout << a[i][1] - a[i][0] << "\n";
	}
	fin.close();
	fout.close();
	return 0;
}