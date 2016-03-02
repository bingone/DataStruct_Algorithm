//
// Created by bingone on 16/2/29.
//

#ifndef RBTREE_RBTREE_H
#define RBTREE_RBTREE_H
#define TRUE 1
#define FALSE 0
#define RED 0
#define BLACK 1
typedef struct RBNode {
    RBNode *parent;
    RBNode *left;
    RBNode *right;
    int color;
    void *key;
    void *value;
} RBNode;
typedef struct RBTree {

    RBNode *root;
    int size;
    int (*valueCompare)(void *v1,void *v2);
    int (*keyCompare)(void *k1,void *k2);
} RBTree;
#define CompareKeys(d, key1, key2) \
    (((d)->keyCompare) ? \
        (d)->keyCompare(key1, key2) : \
        (key1) == (key2))
#define GetGrandP(x)\
    (x->parent->parent)
#define GetUncle(x)\
    ((GetGrandP(x)->left) == (x->parent)?(GetGrandP(x)->right):(GetGrandP(x)->left))
#endif //RBTREE_RBTREE_H
