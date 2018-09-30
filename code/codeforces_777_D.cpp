#include<cstdio>
#include<string>
char c;
inline void read(int &a){
	c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,ans;
std::string A[510000];
int main(){
	int i,j,len; bool fl;
	read(n);
	for(i=1;i<=n;i++){
		for(c=getchar();c!='#';c=getchar());
		for(c=getchar();c!='\n';c=getchar())A[i].push_back(c);
		for(j=0;j<A[i].size();j++)fprintf(stderr,"%c",A[i][j]);
		fprintf(stderr,"\n");
	}
	for(i=n;i>=2;i--){
		fl=0;
		for(j=0;j<A[i].size();j++)
		if(A[i-1][j]>A[i][j]){fl=0;break;}
		else if(A[i-1][j]<A[i][j]){fl=1;break;}
		if(fl)continue;
		j--;
		for(;A[i-1].size()>j+1;A[i-1].erase(A[i-1].size()-1,1));
	}
	for(i=i;i<=n;i++){
		printf("#");
		for(j=0;j<A[i].size();j++)putchar(A[i][j]);
		puts("");
	}
}