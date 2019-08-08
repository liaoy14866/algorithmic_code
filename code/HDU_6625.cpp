#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
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
struct node {
	int s[2];
	int num;
	int Arrmap;//记录这个数字的位置
};
node Trie[2][32*100010];//0是A，1是B
int top[2];
struct po {
	int x,ne;
};
po Arre[100010<<1];
int Rtop;
inline void addpos(int opt,int p,int x) {
	Rtop++;
	Arre[Rtop].x=x;
	Arre[Rtop].ne=Trie[opt][p].Arrmap;
	Trie[opt][p].Arrmap=Rtop;
}
int T;
int n;
int A[2][100010];
int tmp[32];
int maxv;
inline void newnode(int opt) {
	top[opt]++;
	Trie[opt][top[opt]]=(node) {
		0,0,0,0
	};
}
inline void insert(int opt,int x,int pos) {
	int p=1,vi,vl;
	for(vl=0,vi=x; vl<=maxv; vl++,vi>>=1)tmp[vl]=vi&1;
	for(vl=maxv,p=1; vl>=0; p=Trie[opt][p].s[tmp[vl]],vl--) {
		Trie[opt][p].num++;
		if(!Trie[opt][p].s[tmp[vl]])newnode(opt),Trie[opt][p].s[tmp[vl]]=top[opt];
	}
	Trie[opt][p].num++;
	addpos(opt,p,pos);
}
int vis[2][100010];
int cnt;//时间戳
struct inf {
	int p,x,opt;
};
inf Stk[100010<<1];
int stktop;
inline int Find(int opt,int x) {
	//返回与x匹配的最优秀的数字的位置
	int p=1,vi,vl;
	for(vl=0,vi=x; vl<=maxv; vl++,vi>>=1)tmp[vl]=vi&1;
	for(vl=maxv,p=1; vl>=0; p=Trie[opt][p].s[tmp[vl]^vi],vl--)
		vi=(Trie[opt][Trie[opt][p].s[tmp[vl]]].num==0);
	return Arre[Trie[opt][p].Arrmap].x;
}
inline void Del(int opt,int x) {
	//删除x数字
	int p=1,vi,vl;
	for(vl=0,vi=x; vl<=maxv; vl++,vi>>=1)tmp[vl]=vi&1;
	for(vl=maxv,p=1; vl>=0; p=Trie[opt][p].s[tmp[vl]],vl--)
		Trie[opt][p].num--;
	Trie[opt][p].num--;
	Trie[opt][p].Arrmap=Arre[Trie[opt][p].Arrmap].ne;
}
int Ans[100010];
int Atop;
inline void DO(int opt,int vi) {
	int tmpos,bel;
	vis[opt][vi]=cnt;
	Stk[++stktop]=(inf) {
		vi,A[opt][vi],opt
	};
	for(; stktop;) {
		bel=Stk[stktop].opt;
		tmpos=Find(bel^1,Stk[stktop].x);
		if(stktop>=2&&A[bel^1][tmpos]==Stk[stktop-1].x) {
			Ans[++Atop]=Stk[stktop].x^Stk[stktop-1].x;
			Del(bel,Stk[stktop].x);
			Del(bel^1,Stk[stktop-1].x);
			//记录答案
			stktop-=2;
		} else {
			Stk[++stktop]=(inf) {
				tmpos,A[bel^1][tmpos],bel^1
			};
			vis[bel^1][tmpos]=cnt;
		}
	}
}
inline void work() {
	read(n);
	int vi;
	for(vi=1; vi<=n; vi++)read(A[0][vi]),maxv=max(maxv,A[0][vi]);
	for(vi=1; vi<=n; vi++)read(A[1][vi]),maxv=max(maxv,A[1][vi]);
	maxv=ceil(log2(maxv));
	for(vi=1; vi<=n; vi++)insert(0,A[0][vi],vi);
	for(vi=1; vi<=n; vi++)insert(1,A[1][vi],vi);
	cnt++;
	for(vi=n; vi>=1; vi--) {
		if(vis[0][vi]!=cnt)DO(0,vi);
		if(vis[1][vi]!=cnt)DO(1,vi);
	}
	sort(Ans+1,Ans+n+1);
	printf("%d",Ans[1]);
	for(vi=2; vi<=n; vi++)printf(" %d",Ans[vi]);
	printf("\n");
}
inline void init() {
	top[0]=top[1]=1;
	Trie[0][1]=Trie[1][1]=(node) {
		0,0,0,0
	};
	Atop=0;
	Rtop=0;
	maxv=0;
}
int main() {
	freopen("T.in","r",stdin);
	freopen("T.out","w",stdout);
	read(T);
	for(; T; T--) {
		init();
		work();
	}
}

