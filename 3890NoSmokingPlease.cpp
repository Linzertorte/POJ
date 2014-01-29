#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
#define N 1000010
#define E N<<2
#define typec int // type of cost
const typec inf = 0x3f3f3f3f; // max of cost
struct edge { int x, y, nxt; typec c; } bf[E];
int ne, head[N], cur[N], ps[N], dep[N];
void addedge(int x, int y, typec c)
{
    bf[ne].x = x; bf[ne].y = y; bf[ne].c = c;
    bf[ne].nxt = head[x]; head[x] = ne++;
    bf[ne].x = y; bf[ne].y = x; bf[ne].c = c;
    bf[ne].nxt = head[y]; head[y] = ne++;
}
long long flow(int n, int s, int t)
{
    typec tr;
    long long res = 0;
    int i, j, k, f, r, top;
    while (1) {
        memset(dep, -1, n * sizeof(int));
        for (f = dep[ps[0] = s] = 0, r = 1; f != r;)
            for(i=ps[f++],j=head[i];j;j=bf[j].nxt)
            {
                if(bf[j].c && -1==dep[k=bf[j].y]){
                    dep[k]=dep[i]+1;ps[r++]=k;
                    if(k==t) {f=r;break;}
                }
            }
        if(-1 == dep[t]) break;
        memcpy(cur, head, n * sizeof(int));
        for(i=s,top=0;;){
            if(i==t) {
                for(k=0,tr=inf;k<top;++k)
                    if(bf[ps[k]].c<tr) tr=bf[ps[f=k]].c;
                for(k=0;k<top;++k)
                    bf[ps[k]].c -= tr, bf[ps[k]^1].c+=tr;
                res += tr; i=bf[ps[top=f]].x;
            }
            for(j=cur[i];cur[i];j=cur[i]=bf[cur[i]].nxt)
                if(bf[j].c && dep[i]+1 == dep[bf[j].y]) break;
            if(cur[i]){
                ps[top++]=cur[i];
                i=bf[cur[i]].y;
            }else {
                if(0==top) break;
                dep[i]=-1;i=bf[ps[--top]].x;
            }
            
        }
    }
    return res;
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        ne=2;
        memset(head,0,sizeof(head));
        int r;int c;
        int r0,c0,r1,c1;
        scanf("%d %d",&r,&c);
        scanf("%d %d",&r0,&c0);
        scanf("%d %d",&r1,&c1);
        int s=r0*c+c0;
        int tt=r1*c+c1;
        int cap;
        for(int i=0;i<r;i++)
            for(int j=0;j<c-1;j++)
            {
                scanf("%d",&cap);
                if(cap)addedge(i*c+j,i*c+j+1,(cap+1)*1000);
            }
        for(int i=0;i<r-1;i++)
            for(int j=0;j<c;j++)
            {
                scanf("%d",&cap);
                if(cap)addedge(i*c+j,(i+1)*c+j,(cap+1)*1000);
            }
        
        
        printf("%lld\n",flow(r*c,s,tt));
        
    }
    return 0;
}
