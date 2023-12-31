# 二分探索木の挿入操作
二分探索木に要素 $z$ を持つ節点を挿入する動作.\
挿入後も二分探索木の性質を満たす必要があるため, 挿入位置を工夫する必要がある.\
挿入位置の探索は単純で, 根から探索していき, 現在見ている節点との値の大小関係によって右の子・左の子へと遷移していく.\
そして, 葉節点に辿り着くことができればそこが挿入位置となる.\
![bst-insert1](https://github.com/hokto/algorithms/assets/33248495/d702c795-6c2e-4185-88d2-2357332f78d8)\
*(a) $x=4<z$ の様子*\
![bst-insert2](https://github.com/hokto/algorithms/assets/33248495/7f33525f-ef67-43f9-9c76-78b2943fb942)\
*(b) $x=9>z$ の様子*\
![bst-insert3](https://github.com/hokto/algorithms/assets/33248495/a5360603-89c6-488b-9aff-c05495c27e34)\
*(c) $x=NIL$ の様子*\
![bst-insert4](https://github.com/hokto/algorithms/assets/33248495/fb3af30b-4855-42f8-bd5e-44bdb8d29a7d)\
*(d) $z$ の最終挿入位置*\
*Fig1. $z=8$ を二分探索木に挿入する様子*

挿入にかかる計算時間は, 根から高さまでの探索であることから, 高さ $h$ に対し, $O(h)$ となる.

ただし, 高さは挿入順によって綺麗にバランスすることもあれば片方に集中することもあるため, ある程度バランスできるように赤黒木に拡張する.
|![bst-insert-balanced](https://github.com/hokto/algorithms/assets/33248495/2ed7713a-2f26-429f-87e0-6153faffa1fe)|![bst-fig2](https://github.com/hokto/algorithms/assets/33248495/13bb363e-a5d4-44f8-a871-195798f21e3b)|
|---|---| 
|Fig2. 挿入順 $\{3,2,1,4,9\}$ の場合|Fig3. 挿入順 $\{1,2,3,4,9\}$ の場合|
