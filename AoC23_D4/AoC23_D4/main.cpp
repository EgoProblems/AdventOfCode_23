#include <iostream>
#include <chrono>
#include <fstream>
#include <string>

using namespace std;

#define PART2

int main()
{
	auto start = chrono::high_resolution_clock::now();

	ifstream file("input");
	int sum = 0;
	string winnersStr;

	int* numTries = NULL;
	while (!file.eof())
	{
		getline(file, winnersStr);

		string numbersStr;

		// Reusing variable. First find the location, then repeatedly use as the count. 
		int numberCount = winnersStr.find('|');
		int winnerCount = winnersStr.find(':');

		numbersStr = winnersStr.substr(numberCount + 1);
		winnersStr = winnersStr.substr(winnerCount + 1, numberCount - winnerCount);

		winnerCount = winnersStr.size() / 3;
		numberCount = numbersStr.size() / 3;

		int* winners = new int[winnerCount];
		int* numbers = new int[numberCount];

		for (int i = 0 ; i < winnerCount ; ++i)
		{
			winners[i] = atoi(&winnersStr[(i * 3) + 1]);
		}
		for (int i = 0 ; i < numberCount ; ++i)
		{
			numbers[i] = atoi(&numbersStr[(i * 3) + 1]);
		}

#ifndef PART2
		int power = 0;
		for (int i = 0 ; i < winnerCount; ++i)
		{
			for (int j = 0; j < numberCount; ++j)
			{
				if (winners[i] == numbers[j])
				{
					power++;
				}
			}
		}
		sum += pow(2, power-1);
#else
		if (numTries == NULL)
		{
			numTries = new int[numberCount];
			for (int i = 0; i < numberCount; ++i)
			{
				numTries[i] = 1;
			}
		}

		int numWinners = 0;
		for (int i = 0; i < winnerCount; ++i)
		{
			for (int j = 0; j < numberCount; ++j)
			{
				if (winners[i] == numbers[j])
				{
					numWinners++;
				}
			}
		}
		
		int toAdd = numTries[0];
		sum += toAdd;

		for (int i = 0; i < numberCount; ++i)
		{
			if (i < numberCount - 1)
			{
				numTries[i] = numTries[i + 1];
			}
			else
			{
				numTries[i] = 1;
			}
			if (i < numWinners)
			{
				numTries[i] += toAdd;
			}
		}
	}
#endif
	

	file.close();

	auto end = chrono::high_resolution_clock::now();
	double time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000.f;

	cout << "Total: " << sum << "   " << time << " millis";

	return 0;
}