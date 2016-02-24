#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <ctime>

using namespace std;


void sum(vector<double> &array, int from, int to,
		double &common_sum, mutex &m, bool need_sin) {
	double my_sum = 0;
	for (int i = from; i < to; ++i) {
		my_sum += need_sin ? sin(array[i]) : array[i];
	}
	mutex.lock();
	common_sum += my_sum;
	mutex.unlock();
}

vector<double> array;

int main () {
	int arrSize = 100000000;
	std::mt19937 gen;
	uniform_real_distribution distr(-1000000000, 1000000000);
	for (int i = 0; i < arrSize; ++i) {
		array.push_back(distr(gen));
	}
	int Nthreads;
	cin >> Nthreads;
	bool need_sin;
	cin >> need_sin;
	double ans = 0;
	vector<thread> t;
	mutex m;

	chrono::system_clock::time_point start = chrono::steady_clock::now();
	for (int i = 0; i < Nthreads; ++i) {
		t.push_back(thread(sum, 
			ref(array),
			(arrSize / Nthreads) * i,
			(arrSize / Nthreads) * (i + 1), 
			ref(ans), ref(m), need_sin));
	}
	for (int i = 0; i < t.size(); ++i)
		t[i].join();
	chrono::system_clock::time_point end = chrono::steady_clock::now();
	cout << "Summing took "
         << chrono::duration_cast<std::chrono::microseconds>(end - start).count()
         << "us.\n";

	return 0;
}