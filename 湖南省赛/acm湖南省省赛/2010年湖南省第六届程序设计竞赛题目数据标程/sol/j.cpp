#include<vector> 
#include<map> 
#include<string>
#include<cstring>
#include<cstdio>
#include<cstdlib>
using namespace std;

struct rec
{
	int flag;
	int x;
	string y;
	int z;
    rec() { flag=0; x=0; y=""; z=0; }    
};

bool operator<(rec a,rec b)
{
	if (a.flag!=b.flag)
		return a.flag<b.flag;
	if (a.x!=b.x)
		return a.x<b.x;
	if (a.y!=b.y)
		return a.y<b.y;
	return a.z<b.z;
}

rec v[100];
map<rec,rec> a[100000];
string s;
int n;
int zhan[100000];
int used[100000];
int used1[100000];

rec parsemap(int x,int y);

int dfs(int x)
{
	for (map<rec,rec>::iterator it=a[x].begin();it!=a[x].end();it++)
	{
		if (it->second.flag==2)
		{
			if (used[it->second.z]==0)
			{
				used[it->second.z]=1;
				used1[it->second.z]=1;
				if (dfs(it->second.z)) return 1;
				used1[it->second.z]=0;
			}
			else if (used1[it->second.z]==1) return 1;
		}
	}
	return 0;
}

int test(int x)
{
	int top,bottom;
	top=0;bottom=1;
	memset(used,0,sizeof(used));
	memset(used1,0,sizeof(used1));
	used[x]=1;
	used1[x]=1;
	return dfs(x);
}

rec parsekey(int x,int y)
{
	rec p;
	while (s[x]==' ') x++;
	while (s[y]==' ') y--;
	if (s[x]=='\'')
	{
		p.flag=1;
		p.x=0;
		p.y=s.substr(x+1,y-x-1);
		p.z=0;
	}
	else
	{
		p.flag=0;
		p.x=atoi(s.substr(x,y-x+1).c_str());
		p.y="";
		p.z=0;
	}
	return p;
}

pair<rec,rec> parsepair(int x,int y)
{
	pair<rec,rec> ans;
	int i;
	for (i=x;i<=y;i++)
		if (s[i]==':') break;
	ans.first=parsekey(x,i-1);
	
	i++;
	for (;i<=y;i++)
		if (s[i]!=' ') break;


	if (s[i]=='{')
	{
		ans.second=parsemap(i,y);
	}
	else
	{
		ans.second=parsekey(i,y);
	}
	return ans;
}

rec parsemap(int x,int y)
{
	int i,j,prev,cnt;
	pair<rec,rec> tmp;
	rec ans;
	ans.flag=2;
	ans.x=0;
	ans.y="";
	ans.z=n;
	n++;
	cnt=0;
	for (i=x;i<=y;i++)
		if (s[i]!=' ') cnt++;
	if (cnt==2)
	{
		return ans;
	}
	j=0;
	i=x+1;
	prev=x;
	while (1)
	{
		for (;i<y;i++)
		{
			if (s[i]=='{') j++;
			if (s[i]=='}') j--;
			if ((j==0)&&(s[i]==',')) break;
		}
		tmp=parsepair(prev+1,i-1);
		a[ans.z][tmp.first]=tmp.second;
		if (i==y)
		{
			break;
		}
		prev=i;
		i++;
	}
	return ans;
}

pair<int,rec> parseleft(int x,int y)
{
	pair<int,rec> p;
	rec q;
	int i,l,r;
	for (i=x;i<=y;i++) if (s[i]!=' ') break;

	p.first=s[i]-'a';
	p.second.flag=-1;
	p.second.x=0;
	p.second.y="";
	p.second.z=0;
	while (1)
	{
		i++;
		for (;i<=y&&i<s.length();i++)
			if (s[i]=='[') break;
		l=i;
		for (;i<=y&&i<s.length();i++)
			if (s[i]==']') break;
		r=i;
		if (i>y) break;
		q=parsekey(l+1,r-1);
		if (p.second.flag==-1)
		{
			p.first=v[p.first].z;
			p.second=q;
		}
		else
		{
			p.first=a[p.first][p.second].z;
			p.second=q;
		}
	}
	return p;
}

rec parseright(int x,int y)
{
	rec ans;
	while (s[x]==' ') x++;
	while (s[y]==' ') y--;
	if ((s[x]>='a')&&(s[x]<='z'))
	{
		pair<int,rec> tmp=parseleft(x,y);
		if (tmp.second.flag==-1)
		{
			ans.flag=2;
			ans.x=0;
			ans.y="";
			ans.z=v[tmp.first].z;
		}
		else
		{
			ans=a[tmp.first][tmp.second];
		}
		return ans;
	}
	if (s[x]=='{')
	{
		ans=parsemap(x,y);
		return ans;
	}
	ans=parsekey(x,y);
	return ans;
}

int main()
{
	int i,p;
	char ss[300];
	n=0;
	for (i=0;i<26;i++)
		v[i].z=-1;
	while (1)
	{
		ss[0]=0;
		gets(ss);
		if (ss[0]==0) break;
		s=ss;
		p=s.find_first_of('=');
		if (p==-1)
		{
			p=s.find_first_of('(');
			pair<int,rec> tmp=parseleft(p+1,s.length()-2);
			int ind;
			if (tmp.second.flag==-1)
				ind=v[tmp.first].z;
			else
				ind=a[tmp.first][tmp.second].z;
			if (s[0]=='l')
			{
				printf("%d\n",a[ind].size());
			}
			else
			{
				printf("%d\n",test(ind));
			}
		}
		else
		{
			p=s.find_first_of('=');
			pair<int,rec> tmp=parseleft(0,p-1);
			if (tmp.second.flag==-1)
				v[tmp.first]=parseright(p+1,s.length()-1);
			else
				a[tmp.first][tmp.second]=parseright(p+1,s.length()-1);
		}
	}
	return 0;
}
