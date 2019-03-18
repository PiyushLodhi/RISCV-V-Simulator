#include <bits/stdc++.h>
using namespace std;
char memory[1000][8];
char res[20];
int len;
int len_word(string s)
{
	if(s==".word")
		return 8;
	if(s==".byte")
		return 2;
}
void dectohex(string s)
{
	string s1;
	int j=s.length();
	int u=1,d=0,x,i1=0;
	while(i1<j)
	{
		x=(int)s[i1]-48;
		d=d*u+x;
		i1++;
		u=10;
	}
	s1="";
	s="";
	j=0;
	while(d!=0)
	{
		x=d%16;
		if(x<10)
		x=x+48;
		else
		x=x+55;
	s1[j++]=x;
	d=d/16;
	}
	u=0;
	len=j;
	while(j>0)
	{
		res[u++]=s1[j-1];
		j--;
	}
}

void writ_mem(string s,int *i,int *j,int i1)
{
	int x;
	int i2=0,t;
	string s1=s;
	if(s[1]!='x')
	{
		dectohex(s);
		if(len%2!=0)
		{
			len=len+1;
			res[len-1]=res[len-2];
			res[len-2]='0';
		}
		x=len;
		int y=len;
		if((*j)==8)
		{
			(*i)++;
			(*j)=0;
		}
		while(y>1)
		{
			 t=res[y-1];
			 int t1=res[y-2];
			 memory[*i][(*j)++]=t1;
			 if((*j)==8)
			 {
				 (*i)++;
					*j=0;
			}
			 memory[*i][(*j)++]=t;
			 if((*j)==8)
			 {
				 (*i)++;
					*j=0;
			}
			 i2++;
			 y=y-2;
			 i1=i1-2;
		}		
			 while(i1>0)
			 { 
		 memory[*i][(*j)]='0';
					(*j)=(*j)+1;
					i1--;
					if((*j)>=8)
					{
						(*i)=(*i)+1;
						(*j)=(*j)%8;
					}
			}
	}
	 else
	 { s1[1]='0';
	 int y=s1.length();
	 x=2;
	 if((*j)==8)
	 {
		 (*i)++;
		(*j)=0;
	}
	while(x<y)
	{
		res[x-2]=s1[x];
		x++;
	}
	y=y-2;
		 while(y>1)
		{
			 t=res[y-1];
			 int t1=res[y-2];
			 memory[*i][(*j)++]=t1;
			 //cout<<*i;
			 if((*j)==8)
			 {
				 (*i)++;
					*j=0;
			}
			 memory[*i][(*j)++]=t;
			 if((*j)==8)
			 {
				 (*i)++;
					*j=0;
			}
			 i2++;
			 y=y-2;
			 i1=i1-2;
		}		
	 
			  while(i1>0)
			 {
					memory[*i][(*j)]='0';
		 (*j)=(*j)+1;
		 i1--;
			 if((*j)>=8)
			 {(*i)=(*i)+1;
			 (*j)=(*j)%8;}
	}
	 }	 
	
	
}
int main()
{
	ifstream fp("Q2.txt",ios::out);
	string s;
	int i=0,j=0,i1,x;
	map <string,int> data_row;
	map <string,int> data_column;
	fp>>s;	
	if(s==".data")											//starting of .data
	while(fp>>s)
	{
		if(s==".text")										//starting of .text
			break;
		x= s.length();
		if(s[x-1]==':')										//starting of new variable
			{
				data_row.insert(pair<string, int>(s,i));
				data_column.insert(pair<string, int>(s,j));
				cout<<s<<" "<<i<<" "<<j<<endl;
				continue;
			}
		if(s[0]=='.')										// stores information about .word or .byte
			{
				i1=len_word(s);
				continue;
			}
		writ_mem(s,&i,&j,i1);
	}
	for(int i3=0;i3<7;i3++)
	{
		for(int i4=0;i4<8;i4++)
			cout<<memory[i3][i4];
		cout<<endl;
	}
return 0;
}