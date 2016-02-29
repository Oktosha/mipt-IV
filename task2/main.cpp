#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <random>

using namespace std;


void sum(vector<double> &arr, int from, int to,
		double &common_sum, mutex &m, bool need_sin) {
	double my_sum = 0;
	for (int i = from; i < to; ++i) {
		my_sum += need_sin ? sin(arr[i]) : arr[i];
	}
	m.lock();
	common_sum += my_sum;
	m.unlock();
}

vector<double> arr;

int main () {
	int arrSize;
	cin >> arrSize;
    std::mt19937 gen;
	uniform_real_distribution<> distr(-1000000000, 1000000000);
	for (int i = 0; i < arrSize; ++i) {
		arr.push_back(distr(gen));
	}
	int Nthreads;
	cin >> Nthreads;
	bool need_sin;
	cin >> need_sin;
	double ans = 0;
	vector<thread> t;
	mutex m;

	chrono::steady_clock::time_point start = chrono::steady_clock::now();
	for (int i = 0; i < Nthreads; ++i) {
		t.push_back(thread(sum, 
			ref(arr),
			(arrSize / Nthreads) * i,
			(arrSize / Nthreads) * (i + 1), 
			ref(ans), ref(m), need_sin));
	}
	for (int i = 0; i < t.size(); ++i)
		t[i].join();
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	long long ans_time = chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	cout << " " << setw(6) 
		 << ans_time / 1000 << " " << setw(3) << ans_time % 1000
		 << " ";


	return 0;
}