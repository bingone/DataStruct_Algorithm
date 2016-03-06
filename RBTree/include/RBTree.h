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

    int (*valueCompare)(void *v1, void *v2);

    int (*keyCompare)(void *k1, void *k2);
} RBTree;
#define CompareKeys(d, key1, key2) \
    (((d)->keyCompare) ? \
        (d)->keyCompare(key1, key2) : \
        (key1) == (key2))
#define GetGrandP(x)\
    (x->parent->parent)
#define GetUncle(x)\
    ((GetGrandP(x)->left) == (x->parent)?(GetGrandP(x)->right):(GetGrandP(x)->left))

extern RBNode *RBcreate(void *key, void *value);

extern RBTree *RBcreateTree(int (*keyCompare)(void *k1, void *k2), int (*valueCompare)(void *v1, void *v2));

extern RBNode *RBfind(RBTree *tree, void *key);

extern int RBupdate(RBTree *tree, RBNode *newNode);

extern RBNode *getGrandP(RBNode *now);

extern RBNode *getUncle(RBNode *now);

extern void rotateLeft(RBNode *now);

extern void rotateRight(RBNode *now);

extern RBNode *RBinsertAdjust(RBTree *tree, RBNode *now);

extern RBNode *RBinsert(RBTree *tree, RBNode *newNode);

extern void RBremove(RBNode *del, RBNode *rep);

extern void RBdeleteAdjust(RBTree *tree, RBNode *now);

extern int RBdelete(RBTree *tree, void *key);

extern void RBdeleteTree(RBTree *tree);

extern void RBdeleteDirect(RBNode *now);

extern void RBprintSimple(RBNode *now, int level);

extern void RBprintTree(RBNode *now, int level);

extern int defaultKeyCompare(void *k1, void *k2);

extern int defaultValCompare(void *v1, void *v2);

#endif //RBTREE_RBTREE_H
