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
	cout << "3 4" << endl;
	cout << "0111" << endl;
	cout << "1110" << endl;
	cout << "0101" << endl;
}

void MakeData(int id, int maxn)
{
	int n = Rand(maxn / 2 + 1, maxn), m = Rand(maxn / 2 + 1, maxn);
	cout << n << ' ' << m << endl;
	if (id <= 2)
	{
		for (int i = 1; i <= n; i ++)
		{
			for (int j = 1; j <= m; j ++)
				cout << Rand(0, 1);
			cout << endl;
		}
	}
	else if (id <= 4)
	{
		for (int i = 1; i <= n; i ++)
		{
			for (int j = 1; j <= m; j ++)
				cout << id - 3;
			cout << endl;
		}
	}
	else if (id <= 7)
	{
		int cx = (id <= 6) ? 1 : n / 2, cy = (id == 5 ? 1 : (id == 6 ? m : m / 2));
		int lim = id <= 6 ? Rand(maxn / 2 + 1, min(n, m)) : min(n, m) / 2;
		for (int i = 1; i <= n; i ++)
		{
			for (int j = 1; j <= m; j ++)
				cout << (abs(i - cx) + abs(j - cy) != lim);
			cout << endl;
		}	
	}
	else 
	{
		static bool Flag[3005][3005];
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= m; j ++)
				Flag[i][j] = 1;
		int cnt = 100;
		for (int i = 1; i <= cnt; i ++)
		{
			int x = Rand(1, n), y = Rand(1, m);
			Flag[x][y] = 0;
		}
		for (int i = 1; i <= n; i ++)
		{
			for (int j = 1; j <= m; j ++)
				cout << Flag[i][j];
			cout << endl;
		}
	}
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
		else MakeData(i, 3000);
		
		cerr << "Make " << filename << endl;
	}
	cout.rdbuf(back_up);
	return 0;
}
