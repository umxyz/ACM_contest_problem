#pragma warning(disable:4786)
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<functional>
#include<string>
#include<cstring>
#include<cstdlib>
#include<queue>
#include<utility>
#include<fstream>
#include<sstream>
#include<cmath>
#include<stack>
#include<assert.h>
using namespace std;

#define MEM(a, b) memset(a, (b), sizeof(a))
#define CLR(a) memset(a, 0, sizeof(a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(X) ( (X) > 0 ? (X) : ( -(X) ) )
#define S(X) ( (X) * (X) )
#define SZ(V) (int )V.size()
#define FORN(i, n) for(i = 0; i < n; i++)
#define FORAB(i, a, b) for(i = a; i <= b; i++)
#define ALL(V) V.begin(), V.end()

typedef pair<int,int> PII;
typedef pair<double, double> PDD;
typedef vector<int> VI;

#define IN(A, B, C) assert( B <= A && A <= C)

//typedef int LL;
//typedef __int64 LL;

struct SwapList
{
	PII Original;
	PII Data;

	SwapList(PII O, PII D)
	{
		Original = O;
		Data = D;
	}

	SwapList() {}
};

SwapList swaplist[200]; //Original = ekhon kon cell, data = kon cell er data ase ekhane

int sz_swaplist;
int row[6000], col[6000]; //row[i] = i'th row te asole ke ase? 0 if new
int row_id[6000], col_id[6000]; //row_id[i] = Original ith row koi ase? 0 if deleted
int r, c;
int flag[6000];
int changed_flag[6000];

int find_in_swaplist(int r, int c)
{
	for(int i = 0; i < sz_swaplist; i++)
		if(PII(r,c) == swaplist[i].Original)
			return i;

	return -1;
}

int reverse_find_in_swaplist(int r, int c)
{
	for(int i = 0; i < sz_swaplist; i++)
		if(PII(r,c) == swaplist[i].Data)
			return i;

	return -1;
}

int main()
{
	char cmd[10];
	int ks = 0, i, n, Q;
	int r1, c1, r2, c2;
	int a, x, j;
	int find1, find2;
	PII content1, content2;
	int dist, cnt, cnt1, cnt2;

	while(scanf("%d %d", &r, &c)!=EOF)
	{
		if(!r && !c) break;

		IN(r, 1, 5000);
		IN(c, 1, 5000);

		sz_swaplist = 0;

		for(i = 1; i <= r; i++) row[i] = i, row_id[i] = i;
		for(i = 1; i <= c; i++) col[i] = i, col_id[i] = i;
		
		scanf("%d", &n);
		IN(n, 1, 50);

		while(n--)
		{
			scanf("%s", cmd);
			
			if(strcmp(cmd, "DC")==0)  //delete columns
			{
				CLR(flag);
				
				//input
				scanf("%d", &a);
				for(i = 0; i < a; i++)
				{
					scanf("%d", &x);
					IN(x, 1, c);
					assert(flag[x] == 0);
					flag[x] = 1;
				}
				
				//delete columns
				for(i = 1, j = 1; i <= c; i++)
				{
					changed_flag[i] = j;

					if(flag[i]) 
					{
						changed_flag[i] = 0;
						col_id[ col[i] ] = 0;
						continue;
					}
					
					col_id[ col[i] ] = j; 
					col[j++] = col[i];
				}
				
				c-=a;

				//fix swap list
				for(i = j = 0; i < sz_swaplist; i++)
				{
					if(changed_flag[swaplist[i].Original.second] == 0)
						continue;

					swaplist[j] = swaplist[i];
					swaplist[j].Original.second = changed_flag[swaplist[i].Original.second];
					j++;
				}

				sz_swaplist = j;
			}
			else if(strcmp(cmd, "DR")==0)  //delete rows
			{
				CLR(flag);

				//input
				scanf("%d", &a);
				for(i = 0; i < a; i++)
				{
					scanf("%d", &x);
					IN(x, 1, r);
					assert(flag[x] == 0);
					flag[x] = 1;
				}
				
				//delete rows
				for(i = 1, j = 1; i <= r; i++)
				{
					changed_flag[i] = j;

					if(flag[i]) 
					{
						changed_flag[i] = 0;
						row_id[ row[i] ] = 0;
						continue;
					}

					row_id[ row[i] ] = j;
					row[j++] = row[i];
				}
				
				r-=a;

				//fix swap list
				for(i = j = 0; i < sz_swaplist; i++)
				{
					if(changed_flag[swaplist[i].Original.first] == 0)
						continue;

					swaplist[j] = swaplist[i];
					swaplist[j].Original.first = changed_flag[swaplist[i].Original.first];
					j++;
				}

				sz_swaplist = j;
			}
			else if(strcmp(cmd, "IC")==0)  //insert columns
			{
				CLR(flag);

				//input
				scanf("%d", &a);
				for(i = 0; i < a; i++)
				{
					scanf("%d", &x);
					IN(x, 1, c);
					assert(flag[x] == 0);
					flag[x] = 1;
				}

				//inserting columns
				for(i = c, j = c + a; i >= 1; i--)
				{
					changed_flag[i] = j;

					col_id[ col[i] ] = j; 
					col[j--] = col[i];

					if(flag[i]) 
					{
						col_id[ 0 ] = j;
						col[j--] = 0;
					}
				}
				
				c+=a;

				//fix swap list
				for(i = 0; i < sz_swaplist; i++)
				{
					swaplist[i].Original.second = changed_flag[swaplist[i].Original.second];
					j++;
				}
			}
			else if(strcmp(cmd, "IR")==0)
			{
				CLR(flag);

				//input
				scanf("%d", &a);
				for(i = 0; i < a; i++)
				{
					scanf("%d", &x);
					IN(x, 1, r);
					assert(flag[x] == 0);
					flag[x] = 1;
				}

				//inserting rows
				for(i = r, j = r + a; i >= 1; i--)
				{
					changed_flag[i] = j;

					row_id[ row[i] ] = j; 
					row[j--] = row[i];

					if(flag[i]) 
					{
						row_id[ 0 ] = j;
						row[j--] = 0;
					}
				}
				
				r+=a;

				//fix swap list
				for(i = 0; i < sz_swaplist; i++)
				{
					swaplist[i].Original.first= changed_flag[swaplist[i].Original.first];
					j++;
				}
			}
			else if(strcmp(cmd, "EX")==0)
			{
				scanf("%d %d %d %d", &r1, &c1, &r2, &c2);

				IN(r1, 1, r);
				IN(r2, 1, r);
				IN(c1, 1, c);
				IN(c2, 1, c);


				find1 = find_in_swaplist(r1, c1);
				find2 = find_in_swaplist(r2, c2);

				if(find1!=-1 && find2!=-1)
				{
					swap( swaplist[find1].Data, swaplist[find2].Data );
				}
				else if(find1==-1 && find2==-1)
				{
					if(row[r1]==0 || col[c1]==0) content1 = PII(-1, -1);
					else content1 = PII(row[r1], col[c1]);

					if(row[r2]==0 || col[c2]==0) content2 = PII(-1, -1);
					else content2 = PII(row[r2], col[c2]);

					swaplist[ sz_swaplist++ ] = SwapList(PII(r1, c1), content2);
					swaplist[ sz_swaplist++ ] = SwapList(PII(r2, c2), content1);
				}
				else
				{
					if(find1==-1) {swap(r1, r2); swap(c1, c2); swap(find1, find2);}

					//find2==-1, find1!=-1
					//(r1, c1) is in swaplist
					//(r2, c2) is not in swaplist

					if(row[r2]==0 || col[c2]==0) content2 = PII(-1, -1);
					else content2 = PII(row[r2], col[c2]);

					content1 = swaplist[find1].Data;

					swaplist[find1].Original = PII(r2, c2);
					swaplist[ sz_swaplist++ ] = SwapList(PII(r1, c1), content2);
				}
			}
			else
				assert(0);
		}

		printf("Spreadsheet #%d\n", ++ks);

		dist = cnt = 0;
		cnt1 = cnt2 = 0;

		for(i = 1; i <= r; i++) if(row[i]) cnt1++;
		for(i = 1; i <= c; i++) if(col[i]) cnt2++;

		for(i = 1; i <= r; i++) if(row[i]) dist += cnt2*ABS(i - row[i]);
		for(i = 1; i <= c; i++) if(col[i]) dist += cnt1*ABS(i - col[i]);
		cnt = cnt1*cnt2;

		for(i = 0; i < sz_swaplist; i++)
		{
			PII Original = swaplist[i].Original;
			PII Data = swaplist[i].Data;

			if(row[Original.first] && col[Original.second]) 
			{
				cnt--;
				dist -= ABS(Original.first - row[Original.first]);
				dist -= ABS(Original.second - col[Original.second]);
			}

			if(Data.first != -1)
			{
				cnt++;
				dist += ABS(Data.first - Original.first);
				dist += ABS(Data.second - Original.second);
			}
		}

		printf("There are %d cell(s) kept, total distance = %d\n", cnt, dist);

		scanf("%d", &Q);
		IN(Q, 1, 10000);
		while(Q--)
		{
			scanf("%d %d", &r1, &c1);

			find1 = reverse_find_in_swaplist(r1, c1);

			if(find1!=-1) printf("Cell data in (%d,%d) moved to (%d,%d)\n", r1, c1, swaplist[find1].Original.first, swaplist[find1].Original.second);
			else if(row_id[r1] && col_id[c1]) printf("Cell data in (%d,%d) moved to (%d,%d)\n", r1, c1, row_id[r1], col_id[c1]);
			else printf("Cell data in (%d,%d) GONE\n", r1, c1);
		}
	} 

	return 0;
}
