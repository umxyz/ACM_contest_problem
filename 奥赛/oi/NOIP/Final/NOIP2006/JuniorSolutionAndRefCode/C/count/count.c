#include<stdio.h>
int smallest,biggest,length;
//smallest��С������biggest��������length���� 
int getnextone(char *a,int len)//��ȡ��һ��jam���ֵĺ���
//����1Ϊ�ɹ�
//����0Ϊʧ�� 
{
  int i,j; 
  if(a[len-1]-'a'+1<biggest)//������һλ��û�ﵽ�����ô���һλ+1 ������һ���� 
      {
        a[len-1]++;
        return 1;                 
      }
  for(i=len-2;i>=0;i--)
      if (a[i]<a[i+1]-1)
//���ǰһλ���һλ������1����ô��һ�����־���ǰһλ+1 
//�����׵Ŀ�����һ�� 
//ԭʼ�� if (a[i]-'a'<a[i+1]-'a'-1)
//�����Կ��������߶�����һ'a' �������Ż��������ʽ�� 
         {
            a[i]++;//�Ѿ��ҵ���һλ�� 
            for (j=i+1;j<length;j++)
              a[j]=a[j-1]+1;
/****************************************************
   ��Ϊ��������ǵ����ģ� ���Ժ����������ǰ�����+1
   ���Ծ���������������� 
*****************************************************/
			  
//�����ֱ����ԭ����jam�����ϸģ���ʡ�˿ռ� 
            return 1;
         }          
  return 0;
//����� �����Ǹ�for���һֱû��return 1˵�� һֱ��û�ҵ��Ǹ���
//���Ծ�û���ˡ�return 0; 
}



int main ()
{
    FILE *in=fopen("count.in","r");
    FILE *out=fopen("count.out","w");

    char jam[30];//��¼jam���ֵ����飬����㲻Ҫ�� 
    int i;
    fscanf(in,"%d %d %d",&smallest,&biggest,&length);
    fscanf(in,"%s",jam);
    fclose(in);
    for(i=0;i<5;i++)
      {
          if(!getnextone(jam,length))//�����������0��˵������û���ˣ�ֱ���˳� 
            break;
          else fprintf(out,"%s\n",jam);//����������jam���� 
      }
    fclose(out);
    return 0;
}
