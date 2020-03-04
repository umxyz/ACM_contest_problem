#include <cmath>
#include <random>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 10;
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
	cout << "4" << endl;
	cout << "1 2 1 3" << endl;
}

void MakeData(int id, int maxn, int maxw)
{
	static int W[100005];
	int n = Rand(maxn / 2 + 1, maxn);
	int w = Rand(maxw / 2, min(maxw, n));
	for (int i = 1; i <= n; i ++)
		W[i] = i;
	for (int i = 1; i <= n; i ++)
		swap(W[i], W[Rand(i, n)]);
	cout << n << endl;
	for (int i = 1; i <= n; i ++)
		cout << W[Rand(1, w)] << (i == n ? '\n' : ' ');
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
		else if (i <= 2) MakeData(i, 100000, 2);
		else if (i <= 6) MakeData(i, 100000, 100);
		else MakeData(i, 100000, 100000);
		
		cerr << "Make " << filename << endl;
	}
	cout.rdbuf(back_up);
	return 0;
}
