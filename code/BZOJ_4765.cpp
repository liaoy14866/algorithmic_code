#include<cstdio>
#include<cmath>
#include<ctime>
#include<algorithm>
using namespace std;
char ch; bool f;
inline void read(int &a){
    f=1;
    for(ch=getchar();ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=0;
    for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
    if(!f)a=-a;
}
int n,m,Threshold,Num,root;
int top;
int Arrmap[100010];
struct rec{
    int x,ne;
}Arre[200010];
void ins(int f,int s){
    top++; Arre[top].x=s; Arre[top].ne=Arrmap[f]; Arrmap[f]=top;
}
int val[100010];
unsigned long long Subval[100010];
int PIH[100010],Size[100010],Belong[100010];
void DFS1(int f,int x){
    int v; Subval[x]=val[x]; Size[x]=1; PIH[x]=++top;
    for(v=Arrmap[x];v;v=Arre[v].ne)if(Arre[v].x!=f){
        DFS1(x,Arre[v].x); Subval[x]+=Subval[Arre[v].x]; Size[x]+=Size[Arre[v].x];
    }
}
unsigned long long BIT[100010];
void Change(int p,int w){
    for(;p<=n;p+=p&-p)BIT[p]+=w;
}
unsigned long long Getsum(int p){
    unsigned long long sum=0; for(;p;p-=p&-p)sum+=BIT[p]; return sum;
}
int F[100010][350];
void DFS2(int f,int x){
	int v;
	for(v=1;v<=Num;v++)F[x][v]=F[f][v];
	F[x][Belong[x]]++;
	for(v=Arrmap[x];v;v=Arre[v].ne)if(Arre[v].x!=f)DFS2(x,Arre[v].x);
}
struct block{
    unsigned long long ans;
}B[350];
int pl,pr;
unsigned long long ans;
int main(){
    int i,j,u,v,deta,l,r,opt;
    read(n); read(m);
    for(i=1;i<=n;i++)read(val[i]);
    for(i=1;i<=n;i++){
        read(u); read(v); if(!u||!v){
            if(!u)root=v;else root=u; continue;
        }
        ins(u,v); ins(v,u);
    }
    top=0; DFS1(0,root);
    Threshold=ceil(sqrt(n)); Num=n/Threshold; if(Num*Threshold<n)Num++;
    for(i=1;i<=Num;i++){
        l=(i-1)*Threshold+1; r=i*Threshold; if(r>n)r=n;
        for(j=l;j<=r;j++)B[i].ans+=Subval[j],Belong[j]=i;
    }
    DFS2(0,root);
    for(i=1;i<=n;i++)Change(PIH[i],val[i]);
    for(i=1;i<=m;i++){
        read(opt);
        if(opt==1){
            read(u); read(v); deta=v-val[u]; val[u]=v; Change(PIH[u],deta);
            for(j=1;j<=Num;j++)B[j].ans+=(unsigned long long)F[u][j]*deta;
        }else{
            read(l); read(r); ans=0; pl=Belong[l]; pr=Belong[r];
            for(j=pl+1;j<=pr-1;j++)ans+=B[j].ans;
            if(pl!=pr){
                for(j=pl*Threshold;j>=l;j--)ans+=Getsum(PIH[j]+Size[j]-1)-Getsum(PIH[j]-1);
                for(j=(pr-1)*Threshold+1;j<=r;j++)ans+=Getsum(PIH[j]+Size[j]-1)-Getsum(PIH[j]-1);
            }else for(j=l;j<=r;j++)ans+=Getsum(PIH[j]+Size[j]-1)-Getsum(PIH[j]-1);
            printf("%llu\n",ans);
        }
    }
}