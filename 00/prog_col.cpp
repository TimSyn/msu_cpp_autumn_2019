#include <chrono>
#include <iostream>

#define SIZE 1000

class Timer
{
    using clock_t = std::chrono::high_resolution_clock;
    using microseconds = std::chrono::microseconds;
public:
    Timer()
        : start_(clock_t::now())
    {
    }

    ~Timer()
    {
        const auto finish = clock_t::now();
        const auto us = 
            std::chrono::duration_cast<microseconds>
                (finish - start_).count();
        std::cout << us << " us" << std::endl;
    }

private:
    const clock_t::time_point start_;
};

void fill_mass(int (*mass)[SIZE], int size)
{
	int i, j;	

	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++)
			mass[i][j] = 1;
}

int sum_by_col(int (*mass)[SIZE], int size)
{
	int i, j, sum = 0;

	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++)
			sum += mass[j][i];
	return sum;
}

int sum_by_raw(int (*mass)[SIZE], int size)
{
	int i, j, sum = 0;

	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++)
			sum += mass[i][j];
	return sum;
}

int main()
{
    int A[SIZE][SIZE];
    
    fill_mass(A, SIZE);
    Timer *t = new Timer();
    sum_by_col(A, SIZE);
    delete t;
    return 0;
}
