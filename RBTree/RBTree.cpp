//
// Created by bingone on 16/2/29.
//

#include <stdio.h>
#include <stdlib.h>
#include "include/RBTree.h"

RBNode *RBcreate(void *key, void *value) {
    RBNode *ret = (RBNode *) malloc(sizeof(RBNode));
    if (ret == NULL)
        return ret;
    ret->key = key;
    ret->value = value;
    ret->left = NULL;
    ret->right = NULL;
    ret->color = RED;
    return ret;
}

RBTree *RBcreateTree(int (*keyCompare)(void *k1, void *k2), int (*valueCompare)(void *v1, void *v2)) {
    RBTree *ret = (RBTree *) malloc(sizeof(RBTree));
    if (ret == NULL)
        return ret;
    ret->keyCompare = keyCompare;
    ret->root = NULL;
    ret->size = 0;
    ret->valueCompare = valueCompare;
    return ret;
}

RBNode *RBfind(RBTree *tree, void *key) {
    RBNode *root = tree->root;
    RBNode *now = root;
    while (now != NULL) {
        if (CompareKeys(tree, key, now->key) == 0) {
            break;
        } else if (CompareKeys(tree, key, now->key) < 0) {
            now = now->left;
        } else {
            now = now->right;
        }
    }
    return now;
}

int RBupdate(RBTree *tree, RBNode *newNode) {
    RBNode *old = RBfind(tree, newNode->key);
    if (old == NULL)
        return FALSE;
    old->value = newNode->value;
    return TRUE;

}

RBNode *getGrandP(RBNode *now) {
    if (now == NULL || now->parent == NULL)
        return NULL;
    return now->parent->parent;
}

RBNode *getUncle(RBNode *now) {
    RBNode *t = getGrandP(now);
    if (t == NULL)
        return NULL;
    if (t->left == now->parent)
        return t->right;
    return t->left;

}

/**
 * when call rotate ,means the caller has made sure  3 Node ,ahaha
 */

void rotateRight(RBNode *now) {
    RBNode *grandP = getGrandP(now);
    RBNode *parent = now->parent;

    if (grandP != NULL) {
        if (parent == grandP->left)
            grandP->left = now;
        else
            grandP->right = now;
    }
    parent->parent = now;
    parent->left = now->right;

    now->right = parent;
    now->parent = grandP;
}

void rotateLeft(RBNode *now) {
    RBNode *grandP = getGrandP(now);
    RBNode *parent = now->parent;

    if (grandP != NULL) { //omit the grandP direction
        if (parent == grandP->left)
            grandP->left = now;
        else
            grandP->right = now;
    }
    parent->parent = now;
    parent->right = now->left;

    now->left = parent;
    now->parent = grandP;
}

// insert
// now != NULL
RBNode *RBinsertAdjust(RBTree *tree, RBNode *now) {
    RBNode *parent = now->parent;
    RBNode *uncle = getUncle(now);
    RBNode *grandP = getGrandP(now);
    RBNode *ret = tree->root;
//    case 1 just root or parent.color == BLACK
    if (parent == NULL) {
        tree->root = now;
        now->color = BLACK;
        return now;
    } else if (parent->color == BLACK) {
        return ret;
    } else if (uncle != NULL && uncle->color == RED) {
        parent->color = BLACK;
        uncle->color = BLACK;
        grandP->color = RED;
        return RBinsertAdjust(tree, grandP);
    } else if (grandP != NULL && parent == grandP->left) {
        if (grandP == ret) {
            ret = parent;
        }
        if (now == parent->right) {
            if (grandP == ret) {
                ret = now;
            }
            rotateLeft(now);
            now = now->left;
        }
        now->parent->color = BLACK;
        now->parent->parent->color = RED;
        rotateRight(now->parent);
        return ret;
    }
    else if (grandP != NULL && parent == grandP->right) {
        if (grandP == ret) {
            ret = parent;
        }
        if (now == parent->left) {
            if (grandP == ret) {
                ret = now;
            }
            rotateRight(now);
            now = now->right; // the node is still the bottom node,and

        }
        now->parent->color = BLACK;
        now->parent->parent->color = RED;
        rotateLeft(now->parent);
        return ret;
    }
    return ret;
}


RBNode *RBinsert(RBTree *tree, RBNode *newNode) {
    RBNode *root = tree->root;
    RBNode *now = root;
    while (now != NULL) {
        if (CompareKeys(tree, newNode->key, now->key) <= 0) {
            if (now->left == NULL) {
                now->left = newNode;
                newNode->parent = now;
                break;
            } else {
                now = now->left;
            }
        } else if (CompareKeys(tree, newNode->key, now->key) > 0) {
            if (now->right == NULL) {
                now->right = newNode;
                newNode->parent = now;
                break;
            } else {
                now = now->right;
            }
        }
    }
    now = newNode;
    tree->size++;
    tree->root = RBinsertAdjust(tree, now);
    return now;
}

void RBremove(RBNode *del, RBNode *rep) {
    if (del == NULL) return;
    if (del->parent != NULL) {
        if (del == del->parent->left) {
            del->parent->left = rep;
        } else {
            del->parent->right = rep;
        }
    }
    if (rep != NULL)
        rep->parent = del->parent;
    free(del);
}

/**
 * if entrance the func ,meaning the node's color deleted is balck.
 *
 * add parms parent,because nowNode maybe NULL
 */
void RBdeleteAdjust(RBTree *tree, RBNode *now, RBNode *parent) {

    RBNode *ret = tree->root;

    // case 1 now's color is RED
    if (now != NULL && now->color == RED) {
        now->color = BLACK;
        return;
    }
    if(parent == NULL){
        return;
    }
    // case 2 uncle's is red
    if (parent->left == now && parent->right != NULL && parent->right->color == RED) {
        if (parent == ret) {
            tree->root = parent->right;
        }
        rotateLeft(parent->right);
        parent->color = RED;
        parent->parent->color = BLACK;
        RBdeleteAdjust(tree, now, parent);
        return;
    } else if (parent->right == now && parent->left != NULL && parent->left->color == RED) {
        if (parent == ret) {
            tree->root = parent->left;
        }
        rotateRight(parent->left);
        parent->color = RED;
        parent->parent->color = BLACK;
        RBdeleteAdjust(tree, now, parent);
        return;
    }

    // case 3 uncle's color is black,and uncle's children are both black
    if (parent->left == now && parent->right != NULL && (parent->right->left == NULL ||
                                                         parent->right->left->color == BLACK) &&
        (parent->right->right == NULL ||
         parent->right->right->color == BLACK)) {

        parent->right->color = RED;
        RBdeleteAdjust(tree, parent, parent->parent);
        return;
    } else if (parent->right == now && parent->left != NULL && (parent->left->right == NULL ||
                                                                parent->left->right->color == BLACK) &&
               (parent->left->left == NULL ||
                parent->left->left->color == BLACK)) {

        parent->left->color = RED;
        RBdeleteAdjust(tree, parent, parent->parent);
        return;
    }

    //case 4 uncle's color is black,uncle's left node color red,right black
    if (parent->left == now && parent->right != NULL && parent->right->color == BLACK &&
        parent->right->left != NULL && parent->right->left->color == RED &&
        (parent->right->right == NULL || parent->right->right->color == BLACK)) {

        rotateRight(parent->right->left);
//        now->parent->right->color = BLACK;
        parent->right->color = BLACK;
//        now->parent->right->right->color = RED;
//        if (parent->right->right != NULL)
            parent->right->right->color = RED;
        RBdeleteAdjust(tree, now, parent);
        return;
    } else if (parent->right == now && parent->left != NULL && parent->left->color == BLACK &&
               parent->left->right != NULL && parent->left->right->color == RED &&
               (parent->left->left == NULL || parent->left->left->color == BLACK)) {

        rotateLeft(parent->left->right);
//        now->parent->left->color = BLACK;
        parent->left->color = BLACK;
//        now->parent->left->left->color = RED;
//        if (parent->left->left != NULL)
            parent->left->left->color = RED;
        RBdeleteAdjust(tree, now, parent);
        return;
    }

    // case 5
    if (parent->left == now && parent->right != NULL && parent->right->color == BLACK &&
        parent->right->right != NULL && parent->right->right->color == RED) {
        if (parent == ret) {
            tree->root = parent->right;
        }
        rotateLeft(parent->right);
//        now = parent;
        parent->color = BLACK;
        parent->parent->color = RED;
//        if (now->parent->right != NULL)
            parent->parent->right->color = BLACK;

    } else if (parent->right == now && parent->left != NULL && parent->left->color == BLACK &&
               parent->left->left != NULL && parent->left->left->color == RED) {
        if (parent == ret) {
            tree->root = parent->left;
        }
        rotateRight(parent->left);
//        now = parent;
        parent->color = BLACK;
        parent->parent->color = RED;
//        if (now->parent->left != NULL)
            parent->parent->left->color = BLACK;
    }
}


/**
 * 1. find the del key in RBTree
 * 2. find the real del key
 * 3.
 */
int RBdelete(RBTree *tree, void *key) {
    RBNode *now = RBfind(tree, key);
    RBNode *del = now;
    RBNode *parent = NULL;
    if (now == NULL)
        return FALSE;
    if (now->left == NULL && now->right == NULL) {
        now = NULL;
    } else if (now->left == NULL && now->right != NULL) {
        now = now->right;
    } else if (now->right == NULL && now->left != NULL) {
        now = now->left;
    } else {
        del = now->left;
        while (del->right != NULL) {
            del = del->right;
        }
        // 不交换颜色属性，这里吃亏了。
        now->key = del->key;
        now->value = del->value;
        now = del->left;
    }
    tree->size--;
    // if the node's color ,OK,valid
    if (del->color == RED) {
        RBremove(del, now);
        return TRUE;
    }

    parent = del->parent;
    // now the die'color is Black
    if (del == tree->root) {
        tree->root = now;
    }
    RBremove(del, now);

    RBdeleteAdjust(tree, now, parent);
    return TRUE;
}

void RBdeleteDirect(RBNode *now) {
    if (now == NULL)
        return;
    RBdeleteDirect(now->left);
    RBdeleteDirect(now->right);
    free(now);
}

void RBdeleteTree(RBTree *tree) {
    if (tree == NULL)
        return;
    RBdeleteDirect(tree->root);
    free(tree);
}

void RBprintNode(RBNode *now, int level) {
    if (now == NULL) {
        printf("now={NULL}\n");
        return;
    }
    char leftSpe[64], rightSpe[64], parentSpe[64];
    char *parent = parentSpe, *left = leftSpe, *right = rightSpe;
    if (now->key == NULL)
        now->key = (void *) "NULL";
    if (now->value == NULL)
        now->value = (void *) "NULL";
    if (now->parent == NULL)
        parent = (char *) "NULL";
    else {
        sprintf(parent, "%p", now->parent);
    }

    if (now->left == NULL)
        left = (char *) "NULL";
    else {
        sprintf(left, "%p", now->left);
    }
    if (now->right == NULL)
        right = (char *) "NULL";
    else {
        sprintf(right, "%p", now->right);
    }
    while (level--) printf("\t");
    printf("{ptr=%p,key=%d,value=%d,parent=%s,color=%s,left=%s,right=%s}\n", now, *(int *) now->key,
           *(int *) now->value,
           parent, now->color == BLACK ? "BLACK" : "RED",
           left, right);
}

void RBprintSimple(RBNode *now, int level) {
    if (now == NULL)
        return;
    printf("{key=%d,val=%d,level=%d}\n", *(int *) now->key, *(int *) now->value, level);
}

void RBprintTree(RBNode *now, int level) {
    if (now == NULL)
        return;
    if (now->left != NULL) {
        RBprintTree(now->left, level + 1);
    }

    RBprintNode(now, level);
    if (now->right != NULL) {
        RBprintTree(now->right, level + 1);
    }
}

int defaultKeyCompare(void *k1, void *k2) {
    int c1 = *(int *) k1;
    int c2 = *(int *) k2;
    if (c1 == c2)
        return 0;
    if (c1 < c2)
        return -1;
    if (c1 > c2)
        return 1;
}

int defaultValCompare(void *v1, void *v2) {
    int c1 = *(int *) v1;
    int c2 = *(int *) v2;
    if (c1 == c2)
        return 0;
    if (c1 < c2)
        return -1;
    if (c1 > c2)
        return 1;
}