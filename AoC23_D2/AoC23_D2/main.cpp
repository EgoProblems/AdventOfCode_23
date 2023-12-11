#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#define PART2 1

using namespace std;

enum COL { R = 0 , G, B};
const int maxCubes[3] = { 12,13,14 };

COL Extract(string test, int& value)
{
	value = atoi(test.c_str());
	
	int id = value > 9 ? 4 : 3;

	switch (test[id])
	{
	case 'r':
		return R;
	case 'g':
		return G;
	case 'b':
		return B;
	}
	cout << "ERROR! Str: " << test;
	return R;
}

// PART 2
void UpdateLowestMax(string test, int maxValues[3])
{
	int value = atoi(test.c_str());

	int id = value > 9 ? 4 : 3;

	switch (test[id])
	{
	case 'r':
		maxValues[R] = maxValues[R] < value ? value : maxValues[R];
		return;
	case 'g':
		maxValues[G] = maxValues[G] < value ? value : maxValues[G];
		return;
	case 'b':
		maxValues[B] = maxValues[B] < value ? value : maxValues[B];
		return;
	}
	cout << "ERROR! Str: " << test;
}

void GetMaxValues(string cubes[3], int count, int maxValues[3])
{
	for (int i = 0; i <= count; ++i)
	{
		UpdateLowestMax(cubes[i], maxValues);
	}
}

int ParseCubes(string input, string cubes[3])
{
	int commaPos = -1;
	int count = 0;
	while ((commaPos = input.find(',')) != -1)
	{
		cubes[count++] = input.substr(0, commaPos);
		input = input.substr(commaPos + 1);
	}
	cubes[count] = input;
	return count;
}

bool CheckOverMax(string cubes[3], int count)
{
	for (int i = 0; i <= count; ++i)
	{
		int value;
		COL colour = Extract(cubes[i], value);

		if (value > maxCubes[colour])
		{
			return true;
		}
	}
	return false;
}

int ParseLine(string input)
{
	int charNum = input.find(':');
	if (charNum > 0)
	{
		int gameNum = atoi(input.substr(5,8).c_str());

		input = input.substr(charNum + 1);

		string cubes[3];
		int max[3] = { 0,0,0 };
		while ((charNum = input.find(';')) != -1)
		{
			string sub = input.substr(0, charNum);
			int count = ParseCubes(sub, cubes);

#ifndef PART2
			if (CheckOverMax(cubes, count))
			{
				return 0;
			}
#else
			GetMaxValues(cubes, count, max);
#endif
			input = input.substr(charNum + 1);
		}

	

		// Check the last part of the string!
		int count = ParseCubes(input, cubes);
#ifndef PART2
		if (CheckOverMax(cubes, count))
		{
			return 0;
		}
		return gameNum;
#else
		GetMaxValues(cubes, count, max);
		return max[0] * max[1] * max[2];
#endif

	}
	return 0;
}

int main()
{
	auto start = chrono::high_resolution_clock::now();
	int total = 0;
	ifstream file("input");
	while (!file.eof())
	{
		string toProcess;
		getline(file, toProcess);

		//cout << "Possible Line: ";

		//if(toProcess != "")
		//{ 
			int outputValue = ParseLine(toProcess);
			//if(outputValue) cout << "  " << outputValue;
			total += outputValue;
		//}

		//cout << endl;
	}
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	cout << "Total of IDs: " << total << "   Time taken: " << duration/ 1000000.f << " millis.";

	return 0;
}