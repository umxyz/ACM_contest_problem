/*
    Judge program for UVa
    argv[1]= judge_in
    argv[2] = judge_ans
    stdin = user_out
    
    Attention:
    1. After reading everything form user_out, check for validity.
    2. Check 'Case %d', check extra output
*/
#define AC 0
#define PE 1
#define WA 2

#include<cstdio>
#include<cstdlib>
#include<cmath>

char dummy[100000];

int main(int argc, char* argv[]){
  FILE *in = fopen(argv[1], "r");
  FILE *ans = fopen(argv[2], "r");
	freopen(argv[3],"r",stdin);

  double a, b;
  
  while(fscanf(ans, "%s%s%lf%%", dummy, dummy, &a) == 3){
    if(scanf("%s%s%lf%%", dummy, dummy, &b) != 3) return WA;
    if(!(fabs(a-b) < 0.015)) return WA;
  }
  if(scanf("%s", dummy) == 1) return WA;
  printf("Correct!\n");
  return AC;
}
