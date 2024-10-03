#include <bits/stdc++.h>
using namespace std;

char a, b, start;
int c, d[101][101], n;

int Floyd_Warshall(){
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if( (d[i][k]&&d[k][j]) && (d[i][j] < d[i][k]+d[k][j]) ) // 如果兩數都不為0，且兩點相加大於原本長度
                    d[i][j] = d[i][k]+d[k][j];// 則i到j改為相加(較長)的長度
    }
    // 找起點到終點的最長距離
    int M=0;
    for(int i=0;i<n;i++) M=max(M, d[start-'A'][i]);
    return M;
}
int main(){
    while(cin>>start>>n){
        // 這句在競程比較常見，用來初始化陣列
        memset(d, 0, sizeof(d));
        for(int i=0;i<n;i++){
            cin>>a>>b>>c;
            // 如果測資重複，則取大的存入
            if(c > d[a-'A'][b-'A']) d[a-'A'][b-'A']=c;
        }
        cout<<Floyd_Warshall()<<"\n";
   }
}
/*
 * 這題其實是常見的最小路徑，不過反過來變成最長而已
 * 用Floyd-Warshall解摟
 * 不難看出來是用枚舉+dp
 */