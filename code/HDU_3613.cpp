#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#define ULL unsigned long long
#define LL long long
using namespace std;
char ch;
bool fh;
inline void read(int &a) {
	for(fh=0,ch=getchar(); ch<'0'||ch>'9'; ch=getchar())if(ch=='-')fh=1;
	for(a=0; ch>='0'&&ch<='9'; ch=getchar())(a*=10)+=ch-'0';
	if(fh)a=-a;
}
const int none=1e9+7;
char an[500010];
int lena;
char bn[500010];//反串
int lenb;
int ne[500010];
int extend[500010];
int T;
void exkmp() {
	//a是模式串（小串），b是主串，求b[i..lenb]与a的最长公共前缀
	//next[i]表示a[i..lena]与a的最长公共前缀
	int vi,vj;
	ne[1]=lena;
	for(vi=1; an[vi]==an[vi+1]&&vi<lena; vi++);
	ne[2]=vi-1;
	int po=2;
	for(vi=3; vi<=lena; vi++)
		if(vi+ne[vi-po+1]<po+ne[po])ne[vi]=ne[vi-po+1];
		else {
			vj=po+ne[po]-vi>=1?po+ne[po]-vi+1:1;
			for(; an[vj]==an[vi+vj-1]&&vi+vj-1<=lena; vj++);
			ne[vi]=vj-1;
			po=vi;
		}
	for(vi=1; bn[vi]==an[vi]&&vi<=lena&&vi<=lenb; vi++);
	extend[1]=vi-1;
	po=1;
	for(vi=2; vi<=lenb; vi++)
		if(vi+ne[vi-po+1]<po+extend[po])extend[vi]=ne[vi-po+1];
		else {
			vj=po+extend[po]-vi>=1?po+extend[po]-vi+1:1;
			for(; an[vj]==bn[vi+vj-1]&&vj<=lena&&vi+vj-1<=lenb; vj++);
			extend[vi]=vj-1;
			po=vi;
		}
}
int val[26];
int vsum[500010];
int preval[500010],sufval[500010];
inline bool prepalin(int p) {
	//判断[1..p]
	return extend[lena-p+1]>=p>>1;
}
void work() {
	int vi;
	for(vi=1; vi<=lena; vi++)vsum[vi]=vsum[vi-1]+val[an[vi]-'a'];
	for(vi=1; vi<=lena; vi++)bn[vi]=an[lena-vi+1];
	exkmp();
	for(vi=1; vi<lena; vi++)
		preval[vi]=prepalin(vi)?vsum[vi]:0;
	for(vi=1; vi<=lena; vi++)swap(an[vi],bn[vi]);
	exkmp();
	for(vi=1; vi<lena; vi++)
		sufval[lena-vi+1]=prepalin(vi)?vsum[lena]-vsum[lena-vi]:0;
	int ans=-none;
	for(vi=1;vi<lena;vi++)ans=max(ans,preval[vi]+sufval[vi+1]);
	printf("%d\n",ans);
}
void init() {
	int vi;
	for(vi=0; vi<26; vi++)scanf("%d",&val[vi]);
	scanf("\n");
	scanf("%s",an+1);
	lena=lenb=strlen(an+1);
}
int main() {
	freopen("T.in","r",stdin);
	scanf("%d",&T);
	for(; T; T--) {
		init();
		work();
	}
}

