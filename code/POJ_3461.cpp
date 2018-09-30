#include<cstdio>
int T,lena,lenb;
char an[100010],bn[1000010],c;
int next[100010];

int main(){
	scanf("%d\n",&T);
	//在之后，字符串下标起始位置为1。为了使得下标起始位置为1，用getchar读入。于是在这里scanf的时候要%d\n
	while(T){
		T--; int i,time=0;
		for(i=1,c=getchar();c!='\n'&&c!=-1;c=getchar(),i++)an[i]=c; lena=i-1;
		for(i=1,c=getchar();c!='\n'&&c!=-1;c=getchar(),i++)bn[i]=c; lenb=i-1;//getchar读入。注意len=i-1
		next[0]=0;//做KMP
		for(int i=2;i<=lena;i++){
			int j=next[i-1];
			while((an[i]!=an[j+1])&&(j>0))j=next[j];
			if(an[i]==an[j+1])j++;next[i]=j;
		}
		int j=0;
		for(int i=1;i<=lenb;i++){
			while((an[j+1]!=bn[i])&&(j>0))j=next[j];
			if(an[j+1]==bn[i])j++;
			if(j==lena){time++;j=next[j];}
		}
		printf("%d\n",time);//输出
	}
	return 0;
}