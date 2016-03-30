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

//Дерево фенвика скопипащено с e-maxx (хотя как ещё его писать?)
//Я не помню как там переходить от одного элемента к другому

int fenvik_tree[MAX_N] = {0};

void inc(int x) {
	for (; x < MAX_N; x = (x | (x+1)))
		++fenvik_tree[x];
}

int prefix_sum(int r) {
	int result = 0;
	for (; r >= 0; r = (r & (r+1)) - 1)
		result += fenvik_tree[r];
	return result;
}

int sum(int l, int r) {
	return prefix_sum(r) - prefix_sum(l - 1);
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

	int cur_pos = 0;
	for (auto req : request) {
		while(cur_pos < req.pos) {
			++cur_pos;
			//cout << "inc " << perm[cur_pos] << endl;
			inc(perm[cur_pos]);
		}
		a[req.n][req.t] = sum(req.k, req.l);
	}

	for (int i = 0; i < M; ++i) {
		fout << a[i][1] - a[i][0] << "\n";
	}
	fin.close();
	fout.close();
	return 0;
}