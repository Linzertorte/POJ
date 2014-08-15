#include<iostream>
#include<vector>
#include<string.h>
#include<stdio.h>
#include<stack>
#include<algorithm>
#include<stdlib.h>
#include<queue>
#include<utility>
#include<float.h>
#include<math.h>
#include<stdlib.h>
#include<limits.h>
#include<string>
#include<numeric>
#include<map>
using namespace std;
typedef pair<int,int> PII;
const int N = 500;
char board[N][N+5];
int R,C;
inline bool inboard(int i,int j){
    return i>=0 && i<R && j>=0 && j<C;
}
inline bool rigid(int i,int j){
    return inboard(i,j) && board[i][j]!='E' && board[i][j]!='#';
}
inline bool non_empty(int i,int j){
    return inboard(i,j) && board[i][j]!='#';
}
int dist[N*N][3];

int bfs(){
    memset(dist,-1,sizeof(dist));
    int si,sj,sp;
    int x,y;
    bool found = false;
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++)
            if(board[i][j]=='X') {
                si=i,sj=j;
                found = true;
                break;
            }
        if(found) break;
    }
    sp = 0;
    if(inboard(si+1,sj) && board[si+1][sj]=='X') sp = 1;
    else if(inboard(si,sj+1) && board[si][sj+1]=='X') sp=2;
    dist[si*C+sj][sp] = 0;
    queue<PII> Q;
    Q.push(make_pair(si*C+sj,sp));
    while(!Q.empty()){
        PII head = Q.front();
        Q.pop();
        int i = head.first/C, j = head.first%C, p = head.second;
        int d = dist[head.first][p];
        if(p==0){
            //standing
            if(board[i][j]=='O') return d;
            //up 
            if(non_empty(i-1,j)&&non_empty(i-2,j) && dist[(i-2)*C+j][1]==-1){
                dist[(i-2)*C+j][1] = d+1;
                Q.push(make_pair((i-2)*C+j,1));
            }
            if(non_empty(i+1,j)&&non_empty(i+2,j) && dist[(i+1)*C+j][1]==-1){
                dist[(i+1)*C+j][1] = d+1;
                Q.push(make_pair((i+1)*C+j,1));
            }
            if(non_empty(i,j-1)&&non_empty(i,j-2) && dist[i*C+j-2][2]==-1){
                dist[i*C+j-2][2] = d+1;
                Q.push(make_pair((i)*C+j-2,2));
            }
            if(non_empty(i,j+1)&&non_empty(i,j+2) && dist[(i)*C+j+1][2]==-1){
                dist[(i)*C+j+1][2] = d+1;
                Q.push(make_pair((i)*C+j+1,2));
            }
            
            
        }else if(p==1){
            //vertical
            if(rigid(i-1,j) && dist[(i-1)*C+j][0]==-1){
                dist[(i-1)*C+j][0]=d+1;
                Q.push(make_pair((i-1)*C+j,0));
            }
            if(rigid(i+2,j) && dist[(i+2)*C+j][0]==-1){
                dist[(i+2)*C+j][0]=d+1;
                Q.push(make_pair((i+2)*C+j,0));
            }
            if(non_empty(i,j-1)&&non_empty(i+1,j-1) && dist[(i)*C+j-1][1]==-1){
                dist[(i)*C+j-1][1] = d+1;
                Q.push(make_pair((i)*C+j-1,1));
            }
            if(non_empty(i,j+1)&&non_empty(i+1,j+1) && dist[(i)*C+j+1][1]==-1){
                dist[(i)*C+j+1][1] = d+1;
                Q.push(make_pair((i)*C+j+1,1));
            }
            
            
        }else{
            //horizontal
            
            if(rigid(i,j-1) && dist[(i)*C+j-1][0]==-1){
                dist[(i)*C+j-1][0]=d+1;
                Q.push(make_pair((i)*C+j-1,0));
            }
            if(rigid(i,j+2) && dist[(i)*C+j+2][0]==-1){
                dist[(i)*C+j+2][0]=d+1;
                Q.push(make_pair((i)*C+j+2,0));
            }
            if(non_empty(i-1,j)&&non_empty(i-1,j+1) && dist[(i-1)*C+j][2]==-1){
                dist[(i-1)*C+j][2] = d+1;
                Q.push(make_pair((i-1)*C+j,2));
            }
            if(non_empty(i+1,j)&&non_empty(i+1,j+1) && dist[(i+1)*C+j][2]==-1){
                dist[(i+1)*C+j][2] = d+1;
                Q.push(make_pair((i+1)*C+j,2));
            }
            
        }
    }
    return -1;
}
int main(){
    while(scanf("%d%d",&R,&C), R||C){
        for(int i=0;i<R;i++)
            scanf("%s",board[i]);
        int ans = bfs();
        if(ans==-1) printf("Impossible\n");
        else printf("%d\n",ans);
    }
    return 0;
}
