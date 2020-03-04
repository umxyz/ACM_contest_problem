#include <cmath>
#include <random>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 9;
mt19937_64 gen(19260817);

int Rand(int p = 1000000000)
{
	return gen() % p + 1;
}

int Rand(int l, int r)
{
	return l + Rand(r - l + 1) - 1;
}

void PrintSample()
{
	cout << "2" << endl;
}

void MakeData(int id)
{
	cout << (1 << id + 1) << endl;
}

int main()
{
	streambuf *back_up = cout.rdbuf();
	for (int i = 0; i <= N; i ++)
	{
		string filename = to_string(i) + ".in";
		ofstream fout(filename.c_str());
		cout.rdbuf(fout.rdbuf());
		
		if (i == 0) PrintSample();
		else MakeData(i);
		
		cerr << "Make " << filename << endl;
	}
	cout.rdbuf(back_up);
	return 0;
}
