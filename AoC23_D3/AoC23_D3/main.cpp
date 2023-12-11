#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>

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
		for (int i = pre - 1; i < pre + range; ++i)
		{
			if (i < 0 || (i % w) > ((i + 1) % w))
			{
				continue;
			}
			else if ((i % w) < ((i - 1) % w))
			{
				break;
			}
			else if (IsSymbol(array[i]))
			{
				return true;
			}
		}
	}
	int line = index - 1;
	for (int i = line; i < line + range; i += (range-1))
	{
		if (i < 0 || (i % w) >((i + 1) % w))
		{
			continue;
		}
		else if ((i % w) < ((i - 1) % w))
		{
			break;
		}
		else if (IsSymbol(array[i]))
		{
			return true;
		}
	}
	int post = index + w;
	if (post < w*h)
	{
		for (int i = post - 1; i < post + range; ++i)
		{
			if (i < 0 || (i % w) > ((i + 1) % w))
			{
				continue;
			}
			else if ((i % w) < ((i - 1) % w))
			{
				break;
			}
			else if (IsSymbol(array[i]))
			{
				return true;
			}
		}
	}
	return false;
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
	}

	auto end = chrono::high_resolution_clock::now();

	double duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count() * 1000000;

	cout << "Sum: " << sum << " Time: " << duration << " millis";

}