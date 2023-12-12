/**
 *  問題:https://www.geeksforgeeks.org/largest-rectangular-area-in-a-histogram-using-stack/
 *  stackを使ったO(N)解法
 */

#include<iostream>
#include<vector>
#include<stack>

using namespace std;

int main(){
    int N;
    cin>>N;
    vector<long long> bar(N+2);

    // 最初と最後に番兵を設ける
    bar[0] = -1;
    bar[N+1] = 0;
    for(int i=0;i<N;i++){
        cin>>bar[i+1];
    }

    stack<long long> st;
    st.push(0); // 最初のバーを入れておく

    long long max_area = 0; // 最大の面積を格納
    // 残りのバーに対して処理を実行
    for(int i=1;i<N+2;i++){
        /*
            現在のスタックのトップよりも小さいか同じバーであれば、
            現在のスタックのトップのバーを縦の長さとする最大の面積を計算
        */
        while(bar[st.top()] >= bar[i] ){
            int top = st.top();
            st.pop();
            long long area = 1LL * (i-st.top()-1) * bar[top];
            if(max_area < area) max_area = area;
        }
        st.push(i);
    }
    cout<<max_area<<endl; 
}