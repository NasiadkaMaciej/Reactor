#include <bits/stdc++.h>
#include <chrono>
#include <thread>

int main(int argv, char *argc[])
{
	srand(time(NULL));
	typedef std::chrono::high_resolution_clock Clock;

	// Set default or user provided number of tests
	int repetitions = 0;
	if (argv == 1)
		repetitions = 5;
	else if (argv == 2)
	{
		repetitions = atoi(argc[1]);
		if (!strcmp(argc[1], "-h") || !strcmp(argc[1], "--help"))
			printf("Usage: reactor {Attempts}\n");
	}

	unsigned long long *timeIntervals = new unsigned long long[repetitions];
	unsigned long *userAttempts = new unsigned long[repetitions];

	for (int i = 5; i > 0; i--)
	{
		printf("Welcome, in %i seconds you will start testing your reaction speed.\n", i);
		printf("Press ENTER as soon as you will see characters on the screen.\n");
		std::this_thread::sleep_for(std::chrono::seconds(1));
		printf("\033[2J\033[1;1H");
	};

	for (int i = 0; i < repetitions; i++)
	{
		timeIntervals[i] = (rand() % (5000000000 - 2000000000 + 1)) + 5000000000;
		int time = 0;
		int64_t reaction = 0;

		while (true)
		{
			auto a = Clock::now();
			if (timeIntervals[i] >= time)
			{
				printf("\033[2J\033[1;1H");
				std::this_thread::sleep_for(std::chrono::nanoseconds(10000));
				auto b = Clock::now();
				time += std::chrono::duration_cast<std::chrono::nanoseconds>(b - a).count();
			}
			else
			{
				printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");

				getchar();
				auto b = Clock::now();
				userAttempts[i] = std::chrono::duration_cast<std::chrono::nanoseconds>(b - a).count();
				break;
			}
		}
	}

	std::cout << "\033[2J\033[1;1H";

	double *average = new double[repetitions];
	double avg = 0;

	for (int i = 0; i < repetitions; i++)
	{
		double ms = userAttempts[i] / 1000000.;
		std::cout << i + 1 << ". " << ms << "ms\n";
		average[i] = ms;
	}
	for (int i = 0; i < repetitions; i++)
		avg += average[i];
	avg = avg / repetitions;
	std::cout << "Avg: " << avg << "ms\n";
}
