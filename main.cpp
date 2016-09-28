//clang++ -O2 -std=c++14 % -o %:r && ./%:r
#include <iostream>
#include "OOP1.h"
#include "OOP2.h"
#include "DOD1.h"

int main()
{
	const int nr_of_balls = 1'000'000;

	{
		std::vector<std::array<float, 8>> rendertarget(nr_of_balls);
		OOP1Test(nr_of_balls, rendertarget);
	}
	{
		std::vector<std::array<float, 8>> rendertarget(nr_of_balls);
		OOP2Test(nr_of_balls, rendertarget);
	}
	{
		std::vector<std::array<float, 8>> rendertarget(nr_of_balls);
		DOD1Test(nr_of_balls, rendertarget);
	}

	std::cin.get();
	return 0;
}
