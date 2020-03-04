#include<cstdio>
#include<cstring>

const int maxl=10+1;
const int maxr=1000+10;

char s[maxl];
int reg[maxl],ram[maxr];

int main()
{
    int num;
//    freopen("5.in","r",stdin);
//    freopen("5.ans","w",stdout);
    scanf("%d",&num);
    memset(reg,0,sizeof(reg));
    memset(ram,0,sizeof(ram));
    for(int i=0;i<num;i++)
        scanf("%d",&ram[i]);
    int flag=0,idx=0,i=0;
    while(1)
    {
        int a=ram[i]/100,b=ram[i]/10%10,c=ram[i]%10;
        idx++;
//        printf("idx:%d\n",idx);
        switch(a)
        {
            case 1:flag=1;break;
            case 2:reg[b]=c;break;
            case 3:reg[b]+=c;reg[b]%=1000;break;
            case 4:reg[b]*=c;reg[b]%=1000;break;
            case 5:reg[b]=reg[c];break;
            case 6:reg[b]+=reg[c];reg[b]%=1000;break;
            case 7:reg[b]*=reg[c];reg[b]%=1000;break;
            case 8:reg[b]=ram[reg[c]];break;
            case 9:ram[reg[c]]=reg[b];break;
            case 0:if(reg[c]){i=reg[b];continue;}break;
        }
        if(flag)
            break;
        i++;
    }
    printf("%d\n",idx);
    return 0;
}
