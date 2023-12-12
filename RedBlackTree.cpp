/***
 * 参考: Introduction to Algorithm
*/
#include<iostream>
#include<vector>

using namespace std;
typedef enum{
    BLACK,
    RED
}RB_COLOR;
struct Node{
    Node *p;
    Node *l;
    Node *r;
    int key;
    RB_COLOR color;
};
class RedBlackTree{
    private:
        Node* NIL;
        Node* root;
    public:
        RedBlackTree(const vector<int> init_tree){
            // TODO:サイズ回の挿入を行う 
            root = NIL;
        }
        // xを基準に左回転する.
        void left_rotate(Node* x){
            Node* y = x->r;
            x->r = y->l;
            if(y->l!=NIL){
                y->l->p = x;
            }
            y->p = x->p;
            if(x==root){
                root = y;
            }
            else if(x==x->p->l){
                x->p->l = y;
            }
            else{
                x->p->r = y;
            }
            y->l = x;
            x->p = y;
        }

        // xを基準に右回転する.
        void right_rotate(Node* x){
            Node* y = x->l;
            x->l = y->r;
            if(y->r!=NIL){
                y->r->p = x;
            }
            y->p = x->p;
            if(x==root){
                root = y;
            }
            else if(x==x->p->l){
                x->p->l = y;
            }
            else{
                x->p->r = y;
            }
            y->r = x;
            x->p = y;
        }
        // 要素zを追加する
        void insert(Node* z){
            Node* y = NIL;
            Node* x = root;
            while(x!=NIL){
                y = x;
                if(z->key < x->key){
                    x = x->l;
                }
                else{
                    x = x->r;
                }
            }
            z->p = y;
            // 1つ目の要素を挿入する場合
            if(x == root){
                root = z;
            }
            else if(y->key < z->key){
                // 左の子として挿入する場合
                y->l = z;
            }
            else{
                // 右の子として挿入する場合
                y->r = z;
            }
            z->l = NIL;
            z->r = NIL;
            z->color = RB_COLOR::RED;
            // red-black-tree propertiesを回復する処理
            insert_fixup(z);
        }

        // insertによって違反した性質を回復するための操作
        void insert_fixup(Node* z){
            while(z->p->color==RB_COLOR::RED){
                if(z->p == z->p->p->l){
                    // zの親が左の子だった場合
                    Node* y = z->p->p->r;
                    if(y->color == RB_COLOR::RED){
                        // case1:zの叔父が赤だった場合
                        z->p->p->color = RB_COLOR::RED; // これは必ず黒色のため(property4より)
                        z->p->color = RB_COLOR::BLACK;
                        y->color = RB_COLOR::BLACK;
                        z = z->p->p;
                    }
                    else if(z == z->p->r){
                        // case2:zのおじが黒でzが右の子だった場合
                        // case3の回転操作を行いたいためにあらかじめ回転していい形にしておく
                        z = z->p;
                        left_rotate(z);
                    }
                    // case3: zのおじが黒でzが左の子だった場合
                    z->p->color = RB_COLOR::BLACK; // 回転後の色を合わせるため黒にする.
                    z->p->p->color = RB_COLOR::RED;
                    right_rotate(z);
                }
                else{
                    // zの親が右の子だった場合(左と対称的)
                    // ちゃんと確認していないため, うまく動作しなかったらここが問題の可能性あり
                    Node*y = z->p->p->l;
                    if(y->color == RB_COLOR::RED){
                        // case1: zのおじが赤だった場合
                        z->p->p->color = RB_COLOR::RED;
                        z->p->color = RB_COLOR::BLACK;
                        y->color = RB_COLOR::BLACK;
                        z = z->p->p;
                    }
                    else if(z == z->p->l){
                        // case2: zのおじが黒でzが左の子だった場合
                        z = z->p;
                        left_rotate(z);
                    }
                    // case3: zのおじが黒でzが右の子だった場合
                    z->p->color = RB_COLOR::BLACK;
                    z->p->p->color = RB_COLOR::RED;
                    left_rotate(z);
                }
            }
        }
};