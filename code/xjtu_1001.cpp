#include<cstdio>
#include<algorithm>
#include<vector>
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
	int num[2];//当前节点左支的数字个数与右支的数字个数
};
node Trie[200010*34];
int num[34][2];
int top;
int A[34];
int n;
inline void newnode() {
	top++;
}
void Plus() {
	int p,l,v;
	for(l=0,p=1; Trie[p].s[1]; l++,p=Trie[p].s[0]) {
		swap(Trie[p].s[0],Trie[p].s[1]);
		swap(Trie[p].num[0],Trie[p].num[1]);
		v=Trie[p].num[0]^Trie[p].num[1];
		num[l][0]^=v;
		num[l][1]^=v;
	}
	swap(Trie[p].s[0],Trie[p].s[1]);
	swap(Trie[p].num[0],Trie[p].num[1]);
	v=Trie[p].num[0]^Trie[p].num[1];
	num[l][0]^=v;
	num[l][1]^=v;
}
void insert(int w) {
	int l,p;
	for(l=0; l<32; l++)A[l]=0;
	for(l=0; w; l++,w>>=1)A[l]=w&1;
	for(l=0,p=1; l<32; p=Trie[p].s[A[l]],l++) {
		if(!Trie[p].s[A[l]]) {
			newnode();
			Trie[p].s[A[l]]=top;
		}
		Trie[p].num[A[l]]^=1;
		num[l][A[l]]^=1;
	}

}
int ans;
void Count() {
	int l,p2;
	ans=0;
	for(l=0,p2=1; l<32; l++,p2<<=1)ans+=num[l][1]*p2;
}
int main() {
	freopen("T.in","r",stdin);
	read(n);
	int vi,opt,w;
	top=1;
	for(vi=1; vi<=n; vi++) {
		read(opt);
		if(opt==1)Plus();
		else {
			read(w);
			insert(w);
		}
		Count();
		printf("%d\n",ans);
	}
}

