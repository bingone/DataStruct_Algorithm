//
// Created by bingone on 16/2/29.
//

#include <stdio.h>
#include <stdlib.h>
#include "include/RBTree.h"

RBNode *create(void *key, void *value) {
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

RBNode *find(RBTree *tree, void *key) {
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

int update(RBTree *tree, RBNode *newNode) {
    RBNode *old = find(tree, newNode->key);
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

void rotateLeft(RBNode *now) {
    RBNode *parent = now->parent;

    parent->right = now->left;
    now->left->parent = parent;

    now->left = now->left->right;
    now->parent = parent->right;
    parent->right->right = now;
}

void rotateRight(RBNode *now) {
    RBNode *parent = now->parent;

    parent->left = now->right;
    now->right->parent = parent;

    now->right = now->right->left;
    now->parent = parent->left;
    parent->left->left = now;

}

// insert
// now != NULL
RBNode *insertAdjust(RBTree *tree, RBNode *now) {
    RBNode *parent = now->parent;
    RBNode *uncle = getUncle(now);
    RBNode *grandP = getGrandP(now);
//    case 1 just root or parent.color == BLACK
    if (parent == NULL) {
        tree->root = now;
        now->color = BLACK;
        return now;
    } else if (parent->color == BLACK) {
        return now;
    } else if (uncle != NULL && uncle->color == RED) {
        parent->color = BLACK;
        uncle->color = BLACK;
        grandP->color = RED;
        insertAdjust(tree, getGrandP(now));
        return NULL;
    } else if (now == parent->left && grandP != NULL &&
               grandP->right == parent) { // child and parent are not in one line ,RL
        rotateRight(parent);
        now = now->right; // the node is still the bottom node,and
        now->parent->color=BLACK;
        now->parent->parent->color=RED;
        rotateLeft(now);
    } else if (now == parent->right && grandP != NULL &&
               grandP->left == parent) { // child and parent are not in one line ,LR
        rotateLeft(parent);
        now = now->left;
        now->parent->color=BLACK;
        now->parent->parent->color=RED;
        rotateRight(now);
    }

}


RBNode *insert(RBTree *tree, RBNode *newNode) {
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
    insertAdjust(tree, now);
    return now;
}