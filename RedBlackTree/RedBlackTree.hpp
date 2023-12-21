/***
 * 赤黒木の実装
 * 参考: Introduction to Algorithm
 * TODO: 性質が正しく満たされることの証明を書いとく.
*/
#include<iostream>
#include<vector>
#include<cassert>

// 赤黒木のcolor属性の値
typedef enum{
    BLACK,
    RED
}RB_COLOR;

// ノードを表す構造体
template<typename U> struct Node{
    Node *p;
    Node *l;
    Node *r;
    U key;
    RB_COLOR color;
};

// 赤黒木のクラス
template<typename U> class RedBlackTree{
    private:
        Node<U>* NIL;
        Node<U>* root;
        std::vector<U> inorder_list;
        std::vector<U> preorder_list;
        std::vector<U> postorder_list;
        int is_init_orders_list;
        // xを基準に左回転する.
        void left_rotate(Node<U>* x){
            Node<U>* y = x->r;
            x->r = y->l;
            if(y->l!=NIL){
                y->l->p = x;
            }
            y->p = x->p;
            y->l = x;
            if(x->p==NIL){
                root = y;
            }
            else if(x==x->p->l){
                x->p->l = y;
            }
            else{
                x->p->r = y;
            }
            x->p = y;
        }

        // xを基準に右回転する.
        void right_rotate(Node<U>* x){
            Node<U>* y = x->l;
            x->l = y->r;
            if(y->r!=NIL){
                y->r->p = x;
            }
            y->p = x->p;
            y->r = x;
            if(x->p==NIL){
                root = y;
            }
            else if(x==x->p->l){
                x->p->l = y;
            }
            else{
                x->p->r = y;
            }
            x->p = y;
        }
        // insertによって違反した性質を回復するための操作
        void insert_fixup(Node<U>* z){
            while(z->p->color==RB_COLOR::RED){
                if(z->p == z->p->p->l){
                    // zの親が左の子だった場合
                    Node<U>* y = z->p->p->r;
                    if(y->color == RB_COLOR::RED){
                        // case1:zの叔父が赤だった場合
                        z->p->p->color = RB_COLOR::RED; // これは必ず黒色のため(property4より)
                        z->p->color = RB_COLOR::BLACK;
                        y->color = RB_COLOR::BLACK;
                        z = z->p->p;
                    }
                    else{
                        if(z == z->p->r){
                            // case2:zのおじが黒でzが右の子だった場合
                            // case3の回転操作を行いたいためにあらかじめ回転していい形にしておく
                            z = z->p;
                            left_rotate(z);
                        }
                        // case3: zのおじが黒でzが左の子だった場合
                        z->p->color = RB_COLOR::BLACK; // 回転後の色を合わせるため黒にする.
                        z->p->p->color = RB_COLOR::RED;
                        right_rotate(z->p->p);
                    }
                }
                else{
                    // zの親が右の子だった場合(左と対称的)
                    // ちゃんと確認していないため, うまく動作しなかったらここが問題の可能性あり
                    Node<U>*y = z->p->p->l;
                    if(y->color == RB_COLOR::RED){
                        // case1: zのおじが赤だった場合
                        z->p->p->color = RB_COLOR::RED;
                        z->p->color = RB_COLOR::BLACK;
                        y->color = RB_COLOR::BLACK;
                        z = z->p->p;
                    }
                    else{
                        if(z == z->p->l){
                            // case2: zのおじが黒でzが左の子だった場合
                            z = z->p;
                            right_rotate(z);
                        }
                        // case3: zのおじが黒でzが右の子だった場合
                        z->p->color = RB_COLOR::BLACK;
                        z->p->p->color = RB_COLOR::RED;
                        left_rotate(z->p->p);
                    }
                }
            }
            root->color = RB_COLOR::BLACK;
        }

        // delete_atによって違反した性質を回復する.
        void delete_at_fixup(Node<U>* x){
            while(x!=root && x->color==RB_COLOR::BLACK){
                if(x->p->l == x){
                    // 左の子の場合
                    Node<U>* w = x->p->r; // 兄弟を持っておく
                    if(w->color == RB_COLOR::RED){
                        // case1: wが赤の場合
                        // 赤が隣接することはないため, x->pは黒
                        w->color = RB_COLOR::BLACK;
                        x->p->color = RB_COLOR::RED;
                        left_rotate(x->p);
                        w = x->p->r;
                    }
                    if(w->l->color == RB_COLOR::BLACK && w->r->color == RB_COLOR::BLACK){
                        // case2: wが黒で2つの子が黒の場合
                        w->color = RB_COLOR::RED;
                        x = x->p;
                    }
                    else{
                        if(w->r->color == RB_COLOR::BLACK){
                            // case3: wが黒で左の子が赤, 右の子が黒の場合
                            w->l->color = RB_COLOR::BLACK;
                            w->color = RB_COLOR::RED;
                            right_rotate(w);
                            w = x->p->r;
                        }
                        // case4: wが黒で右の子が赤の場合
                        w->color = x->p->color;
                        x->p->color = RB_COLOR::BLACK;
                        w->r->color = RB_COLOR::BLACK;
                        left_rotate(x->p);
                        x = root;
                    }
                }
                else{
                    // 右の子の場合. 左の子と対称的になる.
                    Node<U>* w = x->p->l;
                    if(w->color == RB_COLOR::RED){
                        // case1: wが赤の場合
                        w->color = RB_COLOR::BLACK;
                        x->p->color = RB_COLOR::RED;
                        right_rotate(x->p);
                        w = x->p->l;
                    }
                    if(w->l->color == RB_COLOR::BLACK && x->r->color == RB_COLOR::BLACK){
                        // case2: wが黒で2つの子が黒の場合
                        w->color = RB_COLOR::RED;
                        x = x->p;
                    }
                    else{
                        if(w->l->color == RB_COLOR::BLACK){
                            // case3: wが黒で右の子が赤, 左の子が黒の場合
                            w->r->color = RB_COLOR::BLACK;
                            w->color = RB_COLOR::RED;
                            left_rotate(w);
                            w = x->p->l;
                        }
                        // case4: wが黒で左の子が赤の場合
                        w->color = x->p->color;
                        x->p->color = RB_COLOR::BLACK;
                        w->l->color = RB_COLOR::BLACK;
                        right_rotate(x->p);
                        x = root;
                    }
                }
            }
            x->color = RB_COLOR::BLACK;
        }

        // uを根とする部分木をvを根とする部分木に置き換える
        void transplant(Node<U>* u,Node<U>* v){
            v->p = u->p;
            if(u->p == NIL){
                root = v;
            }
            if(u->p->l==u){
                u->p->l = v;
            }
            else{
                u->p->r = v;
            }
        }
        // subrootを根とする木に含まれる節点を削除する
        void delete_node(Node<U>* subroot){
            if(subroot == NIL) return;
            delete_node(subroot->l);
            delete_node(subroot->r);
            delete subroot;
        }
    public:
        RedBlackTree(const std::vector<U> init_tree={}){
            NIL = new Node<U>;
            NIL->l = NIL;
            NIL->r = NIL;
            NIL->color = RB_COLOR::BLACK;
            root = NIL;
            is_init_orders_list = 1;
            // 配列の要素を赤黒木にinsert
            for(U key : init_tree){
                Node<U>* node = new Node<U>;
                node->key = key;
                insert(node);
            }
        }
        ~RedBlackTree(){
            delete_node(root);
            delete NIL;
        }
        // 根を返す
        Node<U>* get_root(){
            return root;
        }
        // subrootを根とする木に含まれる要素の最小値を求める. (次節点を求めるためにも使われる)
        Node<U>* minimize(Node<U>* subroot){
            Node<U>* z = subroot;
            while(z->l != NIL){
                z = z->l;
            }
            return z;
        }
        // 要素zを追加する
        void insert(Node<U>* z){
            Node<U>* y = NIL;
            Node<U>* x = root;
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
            z->l = NIL;
            z->r = NIL;
            z->color = RB_COLOR::RED;
            // 1つ目の要素を挿入する場合
            if(y == NIL){
                root = z;
            }
            else if(y->key > z->key){
                // 左の子として挿入する場合
                y->l = z;
            }
            else{
                // 右の子として挿入する場合
                y->r = z;
            }
            // red-black-tree propertiesを回復する処理
            insert_fixup(z);
        }


        // 要素zを削除する.
        void delete_at(Node<U>* z){
            Node<U>* y = z;
            RB_COLOR y_origin_color = y->color;
            Node<U>* x = NIL;
            if(z->l == NIL){
                // 左の子がない場合
                x = z->r;
                transplant(z,z->r);
            }
            else if(z->r == NIL){
                // 右の子がない場合
                x = z->l;
                transplant(z,z->l);
            }
            else{
                // 子を2つ持つ場合
                y = minimize(z->r);
                y_origin_color = y->color;
                x = y->r;
                if(z->p == y){
                    // 次節点がzの子だった場合
                    x->p = y; // xがNILの時の対処
                }
                else{
                    // 子ではなかった場合
                    transplant(y,y->r);
                    y->r = z->r;
                    y->r->p = y;
                }
                transplant(z,y);
                y->l = z->l;
                y->l->p = y;
                y->color = z->color;
            }
            if(y_origin_color == RB_COLOR::BLACK){
                delete_at_fixup(x);
            }
        }
        // order_listを全て初期化する
        void init_orders_list(){
            preorder_list.clear();
            inorder_list.clear();
            postorder_list.clear();
            is_init_orders_list = 1;
        }
        // 要素の昇順(中順)を返す
        std::vector<U> sort(){
            if(!is_init_orders_list){
                return inorder_list;
            }
            solve_order(root);
            is_init_orders_list = 0;
            return inorder_list;
        }
        // 先行順を返す
        std::vector<U> preorder(){
            if(!is_init_orders_list){
                return preorder_list;
            }
            solve_order(root);
            is_init_orders_list = 0;
            return preorder_list;
        }

        // 後行順を返す
        std::vector<U> postorder(){
            if(!is_init_orders_list){
                return postorder_list;
            }
            solve_order(root);
            is_init_orders_list = 0;
            return postorder_list;
        }
        // subrootを根とした部分木を先行順・中順・後行順で要素を並べたものをpushする
        void solve_order(const Node<U>* subroot){
            if(subroot == NIL) return;
            preorder_list.push_back(subroot->key);
            solve_order(subroot->l);
            inorder_list.push_back(subroot->key);
            solve_order(subroot->r);
            postorder_list.push_back(subroot->key);
        }

        // 要素zを持つノードを探索する. 見つけたらそのポインタを返して, なければNILを返す.
        Node<U>* find(U z){
            Node<U>* x = root;
            while(x!=NIL){
                if(x->key == z){
                    return x;
                }
                else if(x->key > z){
                    x = x->l;
                }
                else{
                    x = x->r;
                }
            }
            return NIL;
        }

        // 要素zを持つノードが存在するかどうか判定する
        int is_find(U z){
            if(find(z)!=NIL){
                return 1;
            }
            else{
                return 0;
            }
        }
        // 赤黒木が空かどうか
        int empty(){
            if(root == NIL){
                return true;
            }
            else{
                return false;
            }
        }
};
