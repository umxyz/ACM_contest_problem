#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<string>
#include<cstring>
#include<cstdlib>
#include<queue>
#include<stack>
#include<sstream>
#include<cmath>
#include<cassert>
using namespace std;

#define ABS(X) ( (X) > 0 ? (X) : ( -(X) ) )
#define FORAB(i, a, b) for(i = a; i <= b; i++)

typedef pair<int,int> PII;
typedef vector<string> VS;

#define IN(A, B, C) assert( B <= A && A <= C)

#define MAX_QUESTION 10
#define MAX_OPTION 5

#define EXCEPTION_MARKER	"**Exception**"
#define TRUE_MARKER			"**True**"
#define FALSE_MARKER		"**False**"

VS Question[MAX_QUESTION + 1], Option[MAX_QUESTION + 1][MAX_OPTION + 1];
int nQ, nO;
PII option_value_pair;
string answer_list;

struct BlackBox
{
public:
	int next[1003], prev[1003], nToken;
	VS tokensV;

	string evaluate(int a, int b, string param1 = "", string param2 = "");
	string evaluation(VS &V, string p1 = "", string p2 ="");
};

inline string to_string(int x)
{
	stringstream S;
	S << x;
	return S.str();
}


inline int is_exception(string &S)
{
	return (S == EXCEPTION_MARKER);
}

inline int is_true(const string &S)
{
	return (S == TRUE_MARKER);
}

inline int is_number(string &S)
{
	for(int i = 0; i < S.size(); i++)
		if(S[i]>'9' || S[i]<'0')
			return 0;
	return 1;
}

inline int is_string(string &S)
{
	if(S.size() == 0) return 0;
	for(int i = 1; i < S.size() - 1; i++)
		if(S[i]>'z' || S[i]<'a')
			return 0;

	if(S[0]!='\"' || S[S.size()-1]!='\"') return 0;

	return 1;
}

inline int is_char(string &S)
{
	return S.size() == 3 && (S[1] >= 'a' && S[1] <= 'z') && S[0] == '\"' && S[2] == '\"';
}

inline int convert_to_number(string &S)
{
	int a;
	sscanf(S.c_str(), "%d", &a);
	return a;
}

inline string prime_p(string &S)
{
	if(!is_number(S)) return FALSE_MARKER;
	int a = convert_to_number(S);
	if(a == 2 || a == 3 || a == 5 || a == 7) return TRUE_MARKER;
	return FALSE_MARKER;
}

inline string factorial_p(string &S)
{
	if(!is_number(S)) return FALSE_MARKER;
	int a = convert_to_number(S);
	if(a == 1 || a == 2 || a == 6) return TRUE_MARKER;
	return FALSE_MARKER;
}

inline string square_p(string &S)
{
	if(!is_number(S)) return FALSE_MARKER;
	int a = convert_to_number(S);
	if(a==0 || a == 1 || a == 4 || a == 9) return TRUE_MARKER;
	return FALSE_MARKER;
}

inline string cubic_p(string &S)
{
	if(!is_number(S)) return FALSE_MARKER;
	int a = convert_to_number(S);
	if(a == 0 || a == 1 || a == 8) return TRUE_MARKER;
	return FALSE_MARKER;
}

inline string vowel_p(string &S)
{
	if(!is_char(S)) return FALSE_MARKER;
	char ch = S[1];
	if(ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u') return TRUE_MARKER;
	return FALSE_MARKER;
}

inline string consonant_p(string &S)
{
	if(!is_char(S)) return FALSE_MARKER;
	char ch = S[1];
	if(ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u') return FALSE_MARKER;
	return TRUE_MARKER;
}

inline string equal_check(string &S1, string &S2)
{
	if(is_exception(S1) || is_exception(S2)) return EXCEPTION_MARKER;
	if(S1 == S2) return TRUE_MARKER;
	return FALSE_MARKER;
}

inline string answer_idx(string idx)
{
	if(!is_number(idx)) return EXCEPTION_MARKER;
	int id = convert_to_number(idx);
	if(id<1 || id>nQ) return EXCEPTION_MARKER;
	return string("") + "\"" + answer_list[id] + "\"";
}

inline string answer_value_idx(string idx, string param1 = "", string param2 = "")
{
	if(!is_number(idx)) return EXCEPTION_MARKER;
	int id = convert_to_number(idx);
	if(id<1 || id>nQ) return EXCEPTION_MARKER;
	BlackBox B;
	return B.evaluation(Option[id][answer_list[id]-'a'+1], param1, param2);
}

void initialize(){}

VS parse(char *text)
{
	string S;
	VS ret;
	char ch;

	while(*text)
	{
		ch = *text;

		if(ch == '(') ret.push_back("(");
		else if(ch == ')') ret.push_back(")");
		else if(ch == ' ') ;
		else
		{
			S ="";
			while(ch && ch!='(' && ch!=')' && ch!=' ')
			{
				S += ch;
				text++;
				ch = *text;
			}

			ret.push_back(S);
			continue;
		}

		text++;
	}

	return ret;
}


string BlackBox::evaluate(int a, int b, string param1, string param2)
{
	if(tokensV[a] == "(")
	{
		a++;
		b--;
	}

	if(tokensV[a] == "(")
	{
		int c1 = next[a];
		int c2 = next[c1 + 1];

		string p1 = evaluate(c1 + 1, c2);
		if(c2 == b) return evaluate(a, c1, p1);

		string p2 = evaluate(c2 + 1, next[c2 + 1]);
		return evaluate(a, c1, p1, p2);
	}

	if(a == b)
	{
		if(is_number(tokensV[a]) || is_string(tokensV[a]) || tokensV[a] == "\"none-of-above\"")
			return tokensV[a];
	}

	if(tokensV[a] == "prime-p") return prime_p(param1);
	if(tokensV[a] == "factorial-p") return factorial_p(param1);
	if(tokensV[a] == "square-p") return square_p(param1);
	if(tokensV[a] == "cubic-p") return cubic_p(param1);
	if(tokensV[a] == "vowel-p") return vowel_p(param1);
	if(tokensV[a] == "consonant-p") return consonant_p(param1);
	
	if(tokensV[a] == "equal") 
	{
		int c;

		string p1 = evaluate(a + 1, c = next[a + 1], param1, param2);
		if(is_exception(p1)) return EXCEPTION_MARKER;
		string p2 = evaluate(c + 1, next[c + 1], param1, param2);

		return equal_check(p1, p2);
	}
	if(tokensV[a] == "option-value") 
	{
		BlackBox B;
		return B.evaluation(Option[option_value_pair.first][option_value_pair.second], param1, param2);
	}
	if(tokensV[a] == "answer")
	{
		string idx = evaluate(a + 1, next[a + 1]);
		return answer_idx(idx);
	}
	if(tokensV[a] == "answer-value")
	{
		string idx = evaluate(a + 1, next[a + 1]);
		return answer_value_idx(idx, param1, param2);
	}

	if(tokensV[a] == "first-question")
	{
		for(int i = 1; i <= nQ; i++)
			if(is_true(evaluate(a+1, next[a+1], to_string(i))))
				return to_string(i);
		return EXCEPTION_MARKER;
	}
	if(tokensV[a] == "last-question")
	{
		for(int i = nQ; i >= 1; i--)
			if(is_true(evaluate(a+1, next[a+1], to_string(i))))
				return to_string(i);
		return EXCEPTION_MARKER;
	}
	if(tokensV[a] == "only-question")
	{
		int cnt, id, i;

		cnt = 0;
		id = -1;
		for(i = 1; i <= nQ; i++)
			if(is_true(evaluate(a+1, next[a+1], to_string(i))))
			{
				cnt++;
				id = i;

				if(cnt > 1) return EXCEPTION_MARKER;
			}

		if(cnt == 1) return to_string(id);
		return EXCEPTION_MARKER;
	}
	if(tokensV[a] == "count-question")
	{
		int cnt, i;

		cnt = 0;
		for(i = 1; i <= nQ; i++)
			if(is_true(evaluate(a+1, next[a+1], to_string(i))))
			{
				cnt++;
			}

		return to_string(cnt);
	}
	if(tokensV[a] == "diff-answer")
	{
		int c;

		string idx1 = evaluate(a + 1, c = next[a+1]);
		if(is_exception(idx1)) return EXCEPTION_MARKER;
		if(!is_number(idx1))  return EXCEPTION_MARKER;
		int id1 = convert_to_number(idx1);
		if(id1 < 1 || id1 > nQ) return EXCEPTION_MARKER;

		string idx2 = evaluate(c + 1, next[c + 1]);
		if(is_exception(idx2)) return EXCEPTION_MARKER;
		if(!is_number(idx2))  return EXCEPTION_MARKER;
		int id2 = convert_to_number(idx2);
		if(id2 < 1 || id2 > nQ) return EXCEPTION_MARKER;

		return to_string(ABS(answer_list[id1] - answer_list[id2]));
	}

	if(tokensV[a] == "make-answer-diff-next-equal")
	{
		if(is_exception(param1)) return EXCEPTION_MARKER;
		int id1 = convert_to_number(param1);

		string numS = evaluate(a + 1, next[a + 1]);
		if(is_exception(numS)) return EXCEPTION_MARKER;
		if(!is_number(numS))  return EXCEPTION_MARKER;
		int num = convert_to_number(numS);

		int id2 = id1 + 1;
		if(id2 > nQ) return FALSE_MARKER;

		if( ABS(answer_list[id1] - answer_list[id2]) == num )
			return TRUE_MARKER;

		return FALSE_MARKER;
	}
	if(tokensV[a] == "make-answer-equal")
	{
		int c;

		string idx1 = evaluate(a + 1, c = next[a+1]);

		if(answer_idx(param1) == idx1)
			return TRUE_MARKER;
		return FALSE_MARKER;
	}
	if(tokensV[a] == "make-answer-is")
	{
		BlackBox B;
		VS V(tokensV.begin() + a + 1, tokensV.begin() + next[a + 1] + 1);

		return B.evaluation(V, answer_idx(param1));
	}
	if(tokensV[a] == "make-answer-value-equal")
	{
		int c;

		string idx1 = evaluate(a + 1, c = next[a+1]);

		if(answer_value_idx(param1) == idx1)
			return TRUE_MARKER;
		return FALSE_MARKER;
	}
	if(tokensV[a] == "make-answer-value-is")
	{
		BlackBox B;
		VS V(tokensV.begin() + a + 1, tokensV.begin() + next[a + 1] + 1);

		return B.evaluation(V, answer_value_idx(param1));
	}
	if(tokensV[a] == "make-is-multiple")
	{
		int c;

		if(is_exception(param1)) return EXCEPTION_MARKER;

		string numS = evaluate(a + 1, c = next[a+1]);
		if(is_exception(numS)) return EXCEPTION_MARKER;
		if(!is_number(numS))  return EXCEPTION_MARKER;
		int num = convert_to_number(numS);
		int a = convert_to_number(param1);

		if(a % num == 0) return TRUE_MARKER;
		return FALSE_MARKER;
	}
	if(tokensV[a] == "make-equal")
	{
		if(is_exception(param1)) return EXCEPTION_MARKER;

		string numS = evaluate(a + 1, next[a+1]);
		if(is_exception(numS)) return EXCEPTION_MARKER;

		if(numS == param1) return TRUE_MARKER;
		return FALSE_MARKER;
	}
	if(tokensV[a] == "make-not")
	{
		BlackBox B;
		VS V(tokensV.begin() + a + 1, tokensV.begin() + next[a + 1] + 1);

		string S = B.evaluation(V, param1);

		if(!is_true(S)) return TRUE_MARKER;
		return FALSE_MARKER;
	}
	if(tokensV[a] == "make-and")
	{
		int c;

		BlackBox B;
		VS V1(tokensV.begin() + a + 1, tokensV.begin() + (c = next[a + 1] + 1));
		string S1 = B.evaluation(V1, param1);

		if(!is_true(S1)) return FALSE_MARKER;

		VS V2(tokensV.begin() + c, tokensV.begin() + next[c] + 1);
		string S2 = B.evaluation(V2, param1);

		if(!is_true(S2)) return FALSE_MARKER;

		return TRUE_MARKER;
	}
	if(tokensV[a] == "make-or")
	{
		int c;

		BlackBox B;
		VS V1(tokensV.begin() + a + 1, tokensV.begin() + (c = next[a + 1] + 1));
		string S1 = B.evaluation(V1, param1);

		if(is_true(S1)) return TRUE_MARKER;

		VS V2(tokensV.begin() + c, tokensV.begin() + next[c] + 1);
		string S2 = B.evaluation(V2, param1);

		if(is_true(S2)) return TRUE_MARKER;

		return FALSE_MARKER;
	}
}

string BlackBox::evaluation(VS &V, string p1, string p2)
{
	nToken = V.size();
	stack<int> S;

	tokensV = V;

	for(int i = 0; i < nToken; i++)
	{
		next[i] = prev[i] = i;

		if(V[i] == "(") S.push(i);
		else if(V[i] == ")")
		{
			prev[i] = S.top();
			S.pop();
			next[prev[i]] = i;
		}
	}

	return evaluate(0, nToken - 1, p1, p2);
}

int check(int testing_question, int testing_option)
{
	testing_option -= 'a' - 1;
	option_value_pair = PII(testing_question, testing_option);

	if(Option[testing_question][testing_option][0] == "\"none-of-above\"")
	{
		for(int i = 1; i < nO; i++)
			if(check(testing_question, 'a' + i - 1) == 1)
				return 0;

		return 1;
	}

	BlackBox E;
	string result = E.evaluation(Question[testing_question]);

	if( is_true(result) ) return 1;

	return 0;
}

int correct()
{
	int testing_question, testing_option;

	FORAB(testing_question, 1, nQ)
		FORAB(testing_option, 'a', 'a' + nO - 1)
		{
			if(testing_option == answer_list[testing_question] && check(testing_question, testing_option) == 0)
				return 0;

			if(testing_option != answer_list[testing_question] && check(testing_question, testing_option) == 1)
				return 0;
		}

	return 1;
}

void bktk(int at, string S)
{
	if(at == nQ + 1)
	{
		answer_list = S;
		if(correct())
			printf("%s\n", S.substr(1).c_str());
		return;
	}

	for(int i = 1; i <= nO; i++)
	{
		bktk(at + 1, S + " abcde"[i]);
	}
}

int main()
{
	char line[1000];
	int i, j, ks = 1;

	while(scanf("%d %d", &nQ, &nO)!=EOF)
	{
		initialize();

		gets(line);
		for(i = 1; i <= nQ; i++)
		{
			gets(line);
			Question[i] = parse(line);

			for(j = 1; j <= nO; j++)
			{
				gets(line);
				Option[i][j] = parse(line);
			}

			gets(line);
		}

		printf("Case %d:\n", ks++);
		bktk(1, " ");
	}

	return 0;
}
