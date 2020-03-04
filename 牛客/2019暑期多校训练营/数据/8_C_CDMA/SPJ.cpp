#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

#define AC 0
#define WA 1
#define ERROR -1
#define MAXN 1024 + 5
#define LENGTH 10000000 + 5
#define LIM 10000000

int n, pos, A[MAXN][MAXN];
char buf[LENGTH];

int spj(FILE *input, FILE *user_output);

void close_file(FILE *f){
    if(f != NULL){
        fclose(f);
    }
}

int main(int argc, char *args[]){
    FILE *input = NULL, *user_output = NULL;
    int result;
    if(argc != 3){
        printf("Usage: spj x.in x.out\n");
        return ERROR;
    }
    input = fopen(args[1], "r");
    user_output = fopen(args[2], "r");
	
    result = spj(input, user_output);
    printf("result: %d\n", result);
    
    close_file(input);
    close_file(user_output);
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

int ReadInt(char *p, int *st, int *x)
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

int ReadAny(char *p, int *st)
{
	for (; p[*st] != '\n' && IsBlank(p[*st]); (*st) ++) ;
	if (p[*st] == '\n' || p[*st] == '\0') return 0;
	return 1;
}

int ReadEof(FILE *f)
{
	char ch = ' ';
	while (ch = fgetc(f))
	{
		if (ch == EOF || !IsBlank(ch))
			break ;
	}
	return (ch == EOF ? 1 : 0);
}

int spj(FILE *input, FILE *user_output)  
{  
    if (!~fscanf(input, "%d", &n)) return ERROR;
    
	for (int i = 1; i <= n; i ++)
	{
		if (fgets(buf, LENGTH, user_output) == NULL) return WA;
		int pos = 0;
		for (int j = 1; j <= n; j ++)
		{
			if (ReadInt(buf, &pos, A[i] + j) != 1) return WA;
			if (A[i][j] != 1 && A[i][j] != -1) return WA;
		}
		if (ReadAny(buf, &pos)) return WA;
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
