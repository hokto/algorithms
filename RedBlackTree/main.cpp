#include<iostream>
#include "RedBlackTree.hpp"


using namespace std;
int main(){
    // verified (https://algo-method.com/tasks/920 )
    /*
    int Q;
    cin>>Q;
    RedBlackTree rb;
    while(Q--){
        int op;
        cin>>op;
        if(op==0){
            int k;
            cin>>k;
            Node* node = new Node;
            node->key = k;
            rb.insert(node);
        }
        else if(op==1){
            int k;
            cin>>k;
            if(rb.is_find(k)){
                cout<<"Yes"<<endl;
            }
            else{
                cout<<"No"<<endl;
            }
        }
        else if(op==2){
            int k;
            cin>>k;
            if(rb.is_find(k)){
                rb.delete_at(rb.find(k));
                cout<<"Complete"<<endl;
            }
            else{
                cout<<"Error"<<endl;
            }
        }
    }
    return 0;
    */
    // verified(https://algo-method.com/tasks/442)
    /*
    int N;
    cin>>N;
    vector<int> A(N);
    for(int& a : A) cin>>a;
    RedBlackTree<int> rb(A);
    for(int v : rb.sort()) cout<<v<<" ";
    cout<<endl;
    return 0;
    */
   // verified(https://atcoder.jp/contests/abc137/tasks/abc137_d) 
   int N,M;
   cin>>N>>M;
   RedBlackTree<pair<long long,int>> rb;
   vector<vector<long long>> D(M+1);
   for(int i=0;i<N;i++){
    int A;
    long long B;
    cin>>A>>B;
    if(A>M) continue;
    D[A].push_back(B);
   }
    long long ans = 0;
    for(int A=1;A<=M;A++){
        for(long long B : D[A]){
            Node<pair<long long,int>>* node = new Node<pair<long long,int>>;
            node->key = {-B,A};
            rb.insert(node);
        }
        if(!rb.empty()){
            Node<pair<long long,int>>* min = rb.minimize(rb.get_root());
            ans += -1*min->key.first;
            rb.delete_at(min);
        }
    }
    cout<<ans<<endl;
}