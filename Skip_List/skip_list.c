/*
 * skip_list.c
 *
 *  Created on: 2015年12月21日
 *      Author: bingone
 */


#include "include/skip_list.h"
#include <stdio.h>
#include <stdlib.h>

int randomLevel(){
    int level=1;
    while (rand()%2)
        level++;
    level=(MAX_LEVEL>level)? level:MAX_LEVEL;
    return level;
}

skip_node* create_skip_node(int level,keyType key,valueType value){
	skip_node *t  = new_skip_node(level,skip_node);
	if(!t)
		return NULL;
	t->key = key;
	t->value = value;
	return t;
}
skip_list* create_skip_list(){
	skip_list *sl = (skip_list *)malloc(sizeof(skip_list));
	if(sl == NULL)
		return NULL;
	skip_node *t  = create_skip_node(MAX_LEVEL,0,0);
	if(t == NULL){
		free(sl);
		return NULL;
	}
	sl->head = t;
	sl->level = 0; // init level
	for(int i = 0;i<MAX_LEVEL;i++){
		sl->head->next[i] = NULL;
	}
	srand(time(0));
	return sl;
}
valueType *search_skip_list(skip_list *sl,keyType key){
	skip_node *p = sl->head;
	skip_node *q = NULL;
	for(int level = sl->level-1;level>=0;level--){
		while(((q=p->next[level]) && q->key<key)){
			p = q;
		}
		if(q && q->key == key)
			return &q->value;
	}
	return NULL;
}

int insert_skip_node(skip_list *sl,keyType key,valueType value){
	skip_node *q=NULL,*p=sl->head;
	skip_node *update[MAX_LEVEL];
	for(int level = sl->level-1;level>=0;level--){
		while((q=p->next[level]) && q->key<=key)
			p = q;
		update[level]=p;
	}
	if(q && q->key == key){
		q->value = value;
		return 1;
	}
	int level = randomLevel();
	if(level > sl->level){
		for(;sl->level<level;sl->level++)
			update[sl->level] = sl->head;
	}
	q = create_skip_node(level,key,value);
	if(!q){
		return 0;
	}
	for(int i=level-1; i>=0; --i){
		q->next[i]=update[i]->next[i];
	    update[i]->next[i]=q;
	}
	return 1;
}

void free_skip_list(skip_list *sl){
	skip_node *p=sl->head;
	while(p){
		skip_node *q = p->next[0];
		free(p);
		p=q;
	}
	free(sl);
}

void print_r_skip_list(skip_list *sl){
	skip_node *p = sl->head,*q = NULL;
	for(int level=sl->level-1;level>=0;level--){
		q=p->next[level];
		printf("level:%d\n",level+1);
		while(q){
			printf("ptr:%p key:%d val:%d\t",q, q->key, q->value);
			q=q->next[level];
		}
		printf("\n");
	}
}

void remove_skip_list(skip_list *sl,keyType key){
	skip_node *q=NULL,*p=sl->head;
	skip_node *update[MAX_LEVEL];
	for(int level = sl->level-1;level>=0;level--){
		update[level] = NULL;
		while((q=p->next[level]) && q->key<key)
			p = q;
		update[level]=p;
	}
	if(!q || q->key != key)
		return;
	for(int i = sl->level - 1;i>=0;i--){
		if(update[i] == q){
			update[i]->next[i] = q->next[i];
			if(sl->head->next[i] == NULL)
				sl->level--;
		}
	}
	free(q);
}
