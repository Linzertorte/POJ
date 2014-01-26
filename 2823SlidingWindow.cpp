#include<iostream>
#include<stdio.h>
#include<limits.h>
#define MAXN 1000000
using namespace std;
struct TreeNode{
    int l,r,max,min;
};
TreeNode tree[3*MAXN];
int A[MAXN];
int low[MAXN],high[MAXN];
void build(int t,int l,int r)
{
    tree[t].l=l,tree[t].r=r;
    if(l==r){
        tree[t].max=tree[t].min=A[l];
        return;
    }
    int mid=(l+r)>>1;
    build(t<<1,l,mid);
    build(t<<1|1,mid+1,r);
    tree[t].max=max(tree[t<<1].max,tree[t<<1|1].max);
    tree[t].min=min(tree[t<<1].min,tree[t<<1|1].min);
    
}
int getMin(int t,int l,int r)
{
    if(tree[t].l>=l && tree[t].r <= r) return tree[t].min;
    int mid=(tree[t].l+tree[t].r)>>1;
    int ans=INT_MAX;
    if(l<=mid) ans=min(ans,getMin(t<<1,l,r));
    if(r>mid) ans=min(ans,getMin(t<<1|1,l,r));
    return ans;
}
int getMax(int t,int l,int r)
{
    if(tree[t].l>=l && tree[t].r <= r) return tree[t].max;
    int mid=(tree[t].l+tree[t].r)>>1;
    int ans=INT_MIN;
    if(l<=mid) ans=max(ans,getMax(t<<1,l,r));
    if(r>mid) ans=max(ans,getMax(t<<1|1,l,r));
    return ans;
}
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    if(k>n) k=n;
    for(int i=0;i<n;i++) scanf("%d",A+i);
    build(1,0,n-1);
    for(int i=k-1;i<n;i++)
        low[i-k+1]=getMin(1,i-k+1,i),high[i-k+1]=getMax(1,i-k+1,i);
    
    for(int i=0;i<n-k+1;i++)
    {
        if(i) printf(" ");
        printf("%d",low[i]);
    }
    printf("\n");
    for(int i=0;i<n-k+1;i++)
    {
        if(i) printf(" ");
        printf("%d",high[i]);
    }
    printf("\n");
    
    
    
    
    return 0;
}
