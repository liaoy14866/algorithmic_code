#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#define ULL unsigned long long
#define LL long long
using namespace std;
char an[10010],bn[1000100];
int lena,lenb,cnt;
int next[10010];
int T;
void init(){
	scanf("%s",an+1); scanf("%s",bn+1); next[1]=0;
	lena=strlen(an+1); lenb=strlen(bn+1); cnt=0;
}
void work(){
	int vi,vj;
	for(vi=2;vi<=lena;vi++){
		for(vj=next[vi-1];vj&&an[vj+1]!=an[vi];vj=next[vj]);
		if(an[vj+1]==an[vi])vj++;
		next[vi]=vj;
	}
	vj=0;
	for(vi=1;vi<=lenb;vi++){
		for(;vj&&an[vj+1]!=bn[vi];vj=next[vj]);
		if(an[vj+1]==bn[vi])vj++;
		if(vj==lena){
			cnt++;
			vj=next[vj];
		}
	}
	printf("%d\n",cnt);
}
int main(){
	scanf("%d\n",&T);
	for(;T;T--){
		init();
		work();
	}
}
