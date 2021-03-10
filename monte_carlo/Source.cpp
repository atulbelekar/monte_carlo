#include<iostream>
#include<random>
#include<cmath>
#include<omp.h>
#include<chrono>
using namespace std;
using namespace std::chrono;

int main() {
	int num_threads = 8;
	omp_set_num_threads(num_threads);
	random_device rand;
	mt19937_64 generator(rand());
	double lowx = -acos(0);
	double highx = acos(0);
	double lowy = 0;
	double highy = 1;
	uniform_real_distribution<double> distributionx(lowx, highx);
	uniform_real_distribution<double> distributiony(lowy, highy);
	int num_points = 1000000;
	double in[12];
	memset(in, 0, sizeof(in));
	auto start = chrono::high_resolution_clock::now();
    #pragma omp parallel
	{
		int id = omp_get_thread_num();
		for (int i = id; i < num_points; i += num_threads)
		{
			double x = distributionx(generator);
			double y = distributiony(generator);

			if (cos(x) >= y)
			{
				in[id]++;
			}
		}
	}
	double ans = 0;
	for (int i = 0; i < num_threads; i++) {
		ans += in[i];
	}
	auto stop = chrono::high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << duration.count() << endl;
	std::cout << highx*((ans) /(double)num_points)*2;

}