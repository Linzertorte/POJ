#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<utility>
#include<queue>
#include<math.h>
#include<limits.h>
using namespace std;
const double eps = 1e-7;
const int P = 5000;
const int L = 1001;
int l,p;
int fun[L];
struct Edge{
    int v,w;
    Edge(){}
    Edge(int _v,int _w):v(_v),w(_w){}
};
vector<Edge> elist[L];
int bellman_ford(double x){
    double dist[L];
    queue<int> Q;
    int inque[L],in[L];
    memset(inque,0,sizeof inque);
    memset(in,0,sizeof in);
    for(int i=1;i<=l;i++)
        Q.push(i), dist[i] = 0, in[i] = 1, inque[i] = 1;
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        inque[u] = 0;
        for(int i=0;i<elist[u].size();i++){
            Edge &e = elist[u][i];
            int v = e.v;
            double w = e.w*x - fun[v];
            if(dist[v]>dist[u]+w){
                dist[v] = dist[u] + w;
                if(!inque[v]){
                    inque[v] = 1;
                    Q.push(v);
                    in[v]++;
                    if(in[v]>l) return true;
                }
            }
        }
    }
    return false;
}
int main()
{
    scanf("%d%d",&l,&p);
    for(int i=1;i<=l;i++)
        scanf("%d",fun+i);
    int u,v,w;
    for(int i=0;i<p;i++){
        scanf("%d%d%d",&u,&v,&w);
        elist[u].push_back(Edge(v,w));
    }
    double l = 0.0, r = 1000.0;
    double mid;
    while(fabs(l-r)>eps){
        mid = (l+r)/2;
        if(bellman_ford(mid)) l = mid;
        else r = mid;
    }
    printf("%.2f\n",l);
    return 0;
}
