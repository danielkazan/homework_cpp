#include <iostream>
using namespace std;
 
//Дерево отрезков.
struct segment_tree{
    long *tree;
    
    
    //Конструктор.
    segment_tree(int length){
        tree = new long[4*length+1];
    }
    
    //Построение дерева отрезков по массиву a.
    void build(int *a, int v, int tree_l, int tree_r){
        if(tree_l == tree_r) tree[v] = a[tree_l];
        else{
            int tree_m = (tree_l + tree_r)/2;
            build(a, v*2, tree_l, tree_m);
            build(a, v*2+1, tree_m+1, tree_r);
            tree[v] = tree[v*2] + tree[v*2+1];
        }
    }
    //Сумма на отрезке from до to.
    int sum(int v, int tree_l, int tree_r, int l, int r) {
  if (l > r)
    return 0;
  if (l == tree_l && r == tree_r)
    return tree[v];
  int tree_m = (tree_l + tree_r) / 2;
  return sum (v*2, tree_l, tree_m, l, min(r,tree_m))
    + sum (v*2+1, tree_m+1, tree_r, max(l,tree_m+1), r);
    }
    
    //Присваивание значения на позиции pos веса new_val.
    void update(int v, int tree_l, int tree_r, int pos, int new_val){
        if(tree_l == tree_r) tree[v] = new_val;
        else{
            int tree_m = (tree_l + tree_r)/2;
            if(pos <= tree_m){
                update(v*2, tree_l, tree_m, pos, new_val);
            }
            else{
                update(v*2+1, tree_m+1, tree_r, pos, new_val);
            }
            tree[v] = tree[v*2] + tree[v*2+1];
        }
    }
    
    
    
    //Поиск k-го нуля отрезка.
    int find_kth (int v, int tree_l, int tree_r, int max_w) {
      if (max_w > tree[v])
        return -1;
      if (tree_l == tree_r)
        return tree_l;
      int tree_m = (tree_l + tree_r) / 2;
      if (tree[v*2] >= max_w)
        return find_kth (v*2, tree_l, tree_m, max_w);
      else
        return find_kth (v*2+1, tree_m+1, tree_r, max_w - tree[v*2]);
    }
};
 
int main() {
    int n, m, *value;
    cin >> n;
    //Заполнение массива числами.
    value = new int[n+1];
    for(int i = 1; i <= n; ++i){
        cin >> value[i];
    }
    //Построение дерева отрезков.
    segment_tree tree(n);
    tree.build(value, 1, 1, n);
    //Нахождение суммы на отрезке
    cin >> m;
    int type, x, y, v, from, to;
    for(int i = 0; i < m; ++i){
        cin >> from >> to;
        cout << tree.sum(1, 0, n - 1,from, to) << '\n';
        }
    
    return 0;
}