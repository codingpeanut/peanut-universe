#include <iostream>
using namespace std;

int r[100000]={};
//用遞迴找到老大是誰
int find_root(int x){
    if(r[x]==x) return x; //如果他自己就是他那群的源頭，那代表他是自己的朋友
    return find_root(r[x]);
}
//讓老大代表全部的小弟
void attach(int x, int y){
    int root_x=find_root(x); //找到x的源頭
    int root_y=find_root(y); //找到y的源頭
    if(root_x!=root_y){
        r[root_x]=root_y; //讓x的源頭歸順於y的源頭 (若要反過來也可以)
    }
}
int main(){
    //I/O加速
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N, M, Q, A, B;
    N=M=Q=A=B=0;
    cin>>N>>M>>Q;
    for(int i=1;i<=N;i++) r[i]=i;
    for(int i=1;i<=M;i++){
        cin>>A>>B;
        attach(A, B);
    }
    while(Q--){
        cin>>A>>B;
        //如果A和B老大一樣，代表A和B是朋友
        if(find_root(A)==find_root(B)){
            cout<<":)"<<'\n';
        }else{
            cout<<":("<<'\n';
        }
    }
}
/*
 * 會用到 Disjoint Set Union (DSU)
 * 其實只是遞迴而已
 * https://hackmd.io/@CLKO/rkRVS_o-4?type=view
 * I/O加速詳細原理
 * https://hackmd.io/@wiwiho/CPN-io-optimization
 */
