#include <cstdio>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

#define AC 0
#define WA 1
#define ERROR -1
#define MAXN 1024 + 5
#define LENGTH 10000000 + 5
#define LIM 10000000

int n, pos, A[MAXN][MAXN];
char buf[LENGTH];

int spj(ifstream &input, ifstream &user_output);

int main(){
	ifstream input("input"), user_output("user_output");
    int result = spj(input, user_output);
    fprintf(stderr, "result: %d\n", result);
    return result;
}

int IsBlank(char c)
{
	int res = (c == ' ' || c == '\t' || c == '\n') ? 1 : 0;
	return res;
}

int IsDigit(char c)
{
	int res = (c >= '0' && c <= '9') ? 1 : 0;
	return res;
}

int ReadInt(const char *p, int *st, int *x)
{
	for (; p[*st] != '\n' && IsBlank(p[*st]); (*st) ++) ;
	if (p[*st] == '\n') return 0;
	if (p[*st] != '-' && !IsDigit(p[*st])) return 0;
	int f = p[*st] == '-' ? -1 : 1;
	*x = p[*st] == '-' ? 0 : p[*st] - '0';
	for ((*st) ++; IsDigit(p[*st]); (*st) ++)
	{
		*x = (*x) * 10 + p[*st] - '0';
		if (*x > LIM) return 0;
	}
	*x = *x * f;
	return 1;
}

int ReadAny(const char *p, int *st)
{
	for (; p[*st] != '\n' && IsBlank(p[*st]); (*st) ++) ;
	if (p[*st] == '\n' || p[*st] == '\0') return 0;
	return 1;
}

int ReadEof(ifstream &is)
{
	char ch;
	while (is >> ch)
	{
		if (!IsBlank(ch))
			return false;
	}
	return true;
}

int spj(ifstream &input, ifstream &user_output)
{  
	if (!(input >> n)) return ERROR;
    
	for (int i = 1; i <= n; i ++)
	{
		string line;
		if (!getline(user_output, line)) return WA;
		int pos = 0;
		for (int j = 1; j <= n; j ++)
		{
			if (ReadInt(line.data(), &pos, A[i] + j) != 1) return WA;
			if (A[i][j] != 1 && A[i][j] != -1) return WA;
		}
		if (ReadAny(line.data(), &pos)) return WA;
	}
	
	for (int i = 1; i < n; i ++)
		for (int j = i + 1; j <= n; j ++)
		{
			int sum = 0;
			for (int l = 1; l <= n; l ++)
				sum += A[i][l] * A[j][l];
			if (sum != 0) return WA;
		}
		
	if (!ReadEof(user_output))
		return WA;
	
    return AC;
}
