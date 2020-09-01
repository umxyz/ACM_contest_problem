#include <fstream>
#include <string.h>
using namespace std;

int getDigit(int p) {
	int ans = 0;
	while (p) {
		ans++;
		p /= 10;
	}
	return ans;
}
char str[1000010];
int main() {
	ifstream input("input");
	ifstream user_output("user_output");
	int n, p;
	input >>n >>p;

	user_output >> str;

	if (getDigit(p) > n) {
		if (strcmp(str, "T_T") == 0) return 0;
		else return 1;
	}
	int len = strlen(str);
	if (len != n) return 1;
	if (str[0] == '0') return 1;
	long long ret = 0;

	for (int i = 0; i < len; i++) {
		if (!(str[i] >= '0' && str[i] <= '9'))return 1;
		ret = ret*10 + str[i] - '0';
		ret %= p;
	}
	if (ret == 0) return 0;

	return 1;
}
