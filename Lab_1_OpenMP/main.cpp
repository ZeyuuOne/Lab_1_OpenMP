#include <iostream>
#include "cstdlib"
#include "random"
#include "ctime"
#include "chrono"
#include "omp.h"

using namespace std;
using namespace std::chrono;

#define N 1008
#define ThreadNumber 12

int a[N * N], b[N * N], c[N * N];

int main() {
    //Initialize matrix a & b
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            a[i * N + j] = i + j + 1;
            b[i * N + j] = 1;
        }

    auto start = system_clock::now();
    
#pragma omp parallel for num_threads(ThreadNumber)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            double temp = 0;
            for (int k = 0; k < N; ++k) {
                temp += a[i * N + k] * b[k * N + j];
            }
            c[i * N + j] = temp;
        }
    }

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "size: "<<N<<" numprocs: "<<ThreadNumber<<" total time: "
        << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;

    return 0;
}