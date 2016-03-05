#include <iostream>
#include "include/RBTree.h"

#define ARR_LEN 10
int arrKey[ARR_LEN];
int arrVal[ARR_LEN];


int main() {
    printf("Hello, World!\n");
    RBTree *tree = RBcreateTree(defaultKeyCompare,defaultValCompare);
    srand(time(NULL));
    for (int i = 0; i < ARR_LEN; i++) {
        arrKey[i] = rand();
        arrVal[i] = rand();
        RBNode *now = RBcreate(arrKey + i, arrVal + i);
        RBinsert(tree, now);
        RBprintSimple(now, 0);
    }
    int level = 0;
    RBprintTree(tree->root, &level);
    return 0;
}