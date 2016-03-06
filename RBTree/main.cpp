#include <iostream>
#include "include/RBTree.h"

#define ARR_LEN 10
#define INT_RANGE 1000
int arrKey[ARR_LEN];
int arrVal[ARR_LEN];


int main() {
    printf("Hello, World!\n");
    RBTree *tree = RBcreateTree(defaultKeyCompare,defaultValCompare);
    srand(time(NULL));
    for (int i = 0; i < ARR_LEN; i++) {
        arrKey[i] = rand()%INT_RANGE;
        arrVal[i] = rand()%INT_RANGE;
        RBNode *now = RBcreate(arrKey + i, arrVal + i);
        RBinsert(tree, now);
        RBprintSimple(now, 0);
    }
    int level = 0;
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    RBprintTree(tree->root, level);
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    // test insert end
    RBNode *node = RBfind(tree,(void*)(arrKey+rand()%ARR_LEN));
    RBprintSimple(node,0);
    // test find end
    RBdelete(tree,node->key);
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    RBprintTree(tree->root, level);
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    return 0;
}