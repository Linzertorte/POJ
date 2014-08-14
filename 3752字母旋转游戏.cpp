#include<iostream>
#include<vector>
#include<string.h>
#include<stdio.h>
#include<stack>
#include<algorithm>
#include<stdlib.h>
#include<queue>
#include<utility>
using namespace std;
int N,M;
int get_total(int m){
    int X = M-2*(m-1);
    int Y = N-2*(m-1);
    int total = 2*(X+Y)-4;
    return total;
}
int get(int i,int j){
    int m = min(i,j);
    m = min(m,M+1-i);
    m = min(m,N+1-j);
    int off = 0;
    for(int k=1;k<m;k++)
        off += get_total(k);
    int total = get_total(m);
    int X = M-2*(m-1), Y = N-2*(m-1);
    int dx = i-m, dy = j-m;
    if(dx==0) return off+dy+1;
    if(dy==0) return off+total-dx+1;
    if(dy==Y-1) return off+Y + dx;
    return off+Y + Y - dy + X-2;
    
}
int main(){
    cin>>M>>N;
    for(int i=1;i<=M;i++){
        for(int j=1;j<=N;j++){
            printf("   %c",(get(i,j)-1)%26+'A');
           
        }
        cout<<endl;
    }
}
