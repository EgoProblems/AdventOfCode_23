#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>

#define PART2

using namespace std;

int ComputeLength(int value)
{
	int len = 1;
	while ((value /= 10) >= 1)
	{
		len++;
	}
	return len;
}

bool IsSymbol(char a)
{
	return (a >= '!' && a < '.') || a == '/' || (a >= ':' && a <= '@');
}

bool IsValidNumber(int index, int len, char array[], int w, int h)
{
	int range = len + 2;

	int pre = index - w;
	if (pre >= 0)
	{
		for (int i = pre - 1; i < pre + range-1; ++i)
		{
			if (i < 0 || array[i] == ' ')
			{
				continue;
			}
			else if (IsSymbol(array[i]))
			{
				return true;
			}
		}
	}
	int line = index - 1;
	for (int i = line; i < (line + range); i += (range-1))
	{
		if (i < 0 || array[i] == ' ')
		{
			continue;
		}
		else if (IsSymbol(array[i]))
		{
			return true;
		}
	}

	int post = index + w;
	if (post < w*h)
	{
		for (int i = post - 1; i < post + range-1; ++i)
		{
			if (i < 0 || array[i] == ' ')
			{
				continue;
			}
			else if (IsSymbol(array[i]))
			{
				return true;
			}
		}
	}
	return false;
}

bool IsANumber(char a)
{
	return a >= '0' && a <= '9';
}

int FindAdjacentNumbers(char array[], int index, int output[], int w)
{
	//stringstream s;

	int outputIDX = 0;
	for(int j = -1 ; j < 2 ; ++j)
	{
		int tempH = w * j;
		for (int i = index - tempH - 1; i <= index - tempH + 1; ++i)
		{
			//s << array[i];
			if (IsANumber(array[i]))
			{
				int start = i;
				while (IsANumber(array[--i]))
				{
					start = i;
				}
				int value = atoi(&array[start]);
				int len = ComputeLength(value);
				i += len + 1;
				output[outputIDX++] = value;
			}
		}
		//s << endl;
	}

	//s << endl << endl;

	//if (outputIDX > 1)
	//{
	//	cout << s.str();
	//}

	return outputIDX;
}

int main()
{
	auto start = chrono::high_resolution_clock::now();

	ifstream file("input");

	string in;
	stringstream fileText;
	getline(file, in);
	fileText << in;
	int w = in.length();
	int h = 1;
	while (!file.eof())
	{
		getline(file, in);
		fileText << in;
		h++;
	}

	char* array = new char[h * w];
	fileText.read(array, w * h * sizeof(char));

	int sum = 0;
	for (int i = 0; i < w * h; ++i)
	{

#ifndef PART2
		if (array[i] >= '0' && array[i] <= '9')
		{
			int val = atoi(&array[i]);
			int len = ComputeLength(val);

			if (IsValidNumber(i, len, array, w, h))
			{
				sum += val;
			}

			i += len - 1;
		}
#else
		int values[6] = {0,0,0,0,0,0};
		if (array[i] == '*')
		{
			if (FindAdjacentNumbers(array, i, values, w) > 1)
			{
				int total = 1;
				for (int i = 0; i < 6; ++i)
				{
					if (values[i] == 0)
					{
						break;
					}
					total *= values[i];
				}
				sum += total;
			}
		}
#endif
	}

	auto end = chrono::high_resolution_clock::now();

	double duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000.f;

	cout << "Sum: " << sum << " Time: " << duration << " millis";

}