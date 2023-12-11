
//#define CHRISTIANS_SOLUTION

#ifndef CHRISTIANS_SOLUTION
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>

struct Pair
{
	char Compare(std::string);
	char charVal;
	std::string id;
};

char Pair::Compare(std::string test)
{
	for (int i = 0; i < test.size(); ++i)
	{
		if (test[i] == charVal)
		{
			return charVal;
		}

		int j = 0;
		if (test[i] == id[j])
		{
			while (test[i+j] == id[j])
			{
				if (j == id.size() - 1)
				{
					return charVal;
				}
				j++;
			}
		}
		return -1;
	}
	return -1;
}

void ImportKey(Pair ids[9])
{
	int count = 0;
	std::ifstream file("keyvalues");
	while (!file.eof() && count < 9)
	{
		std::string value;
		file >> ids[count].id;
		file >> value;
		ids[count++].charVal = value[0];		
	}
	file.close();
}

int main()
{
	clock_t start = clock();

	Pair ids[9];
	ImportKey(ids);

	std::ifstream file("input");

	std::vector<std::string> input;

	char *val1=0, *val2=0;
	char id1 = -1, id2 = -1;

	int output = 0;

	while (!file.eof())
	{
		std::string value;
		std::getline(file, value);

		input.push_back(value);

		for (int i = 0; i < value.size(); ++i)
		{
			std::string test = value.substr(i);
			for( Pair p : ids )
			{
				id1 = p.Compare(test);
				if (id1 != -1)
				{
					break;
				}
			}

			if (id1 != -1)
			{
				val1 = &id1;
				break;
			}
		}


		for (int i = value.size()-1; i >= 0; --i)
		{
			std::string test = value.substr(i);
			for (Pair p : ids)
			{
				id2 = p.Compare(test);
				if (id2 != -1)
				{
					break;
				}
			}

			if (id2 != -1)
			{
				val2 = &id2;
				break;
			}
		}
		std::string concat = "";
		concat.append(val1, 1);
		concat.append(val2, 1);

		output += atoi(concat.c_str());
	}

	clock_t end = clock();

	double diff = (end-start);

	std::cout << std::endl << output << " took: " << diff << " millis";

	return 0;
}

#else // if CHRISTIANS_SOLUTION
#include <thread>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

int answer = 0;

class foo
{
public:
	inline int Val() const { return m_val; }

	inline void operator() (std::string line)
	{
		for (size_t i = 0; i < line.size(); i++)
		{
			int value = line[i] - '0';
			if (value <= 9)
			{
				answer += 10 * value;
				i = line.size();
			}

		}

		for (size_t i = 0; i < line.size(); i++)
		{
			int value = line[line.size() - i - 1] - '0';
			if (value <= 9)
			{
				answer += value;
				return;
			}
		}
	}
private:
	int m_val;
};

int main()
{
	auto timer = clock();// std::chrono::system_clock::now();
	std::vector<std::string> lines;
	std::ifstream fin;
	fin.open("input", std::ios::in);
	std::string tmp;
	while (getline(fin, tmp))
		lines.push_back(tmp);

	uint32_t threadSize = std::thread::hardware_concurrency() - 2;
	uint32_t lineIndex = 0;
	int diff = lines.size() - lineIndex;
	std::vector<std::thread> threads;
	while (diff > 0)
	{
		for (size_t i = 0; i < (diff < threadSize ? diff : threadSize); i++)
		{
			threads.push_back(std::thread(foo(), lines[lineIndex++]));
		}

		for (int i = 0; i < threads.size(); i++)
			threads[i].join();

		threads.clear();

		diff = lines.size() - lineIndex;
	}

	clock_t end = clock();
	double elapsed = end - timer;// std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - timer).count();

	std::cout << answer << " and took: " << elapsed << "ms" << std::endl;

	return 0;
}

#endif