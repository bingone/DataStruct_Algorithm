/*
 ============================================================================
 Name        : link_list.c
 Author      : bingone
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "include/link_list.h"
int link_insert(link_node **head,int data){
	link_node *cur = (link_node *)malloc(sizeof(link_node));
	if(cur == NULL)
		return 0;
	cur->data = data;
	cur->next = *head;
	*head = cur;
	return 1;
}

void link_remove(link_node **head, int data){
	for(link_node **cur = head;*cur != NULL;){
		link_node *en = *cur;
		if(en->data == data){
			*cur = en->next;
			free(en);
		}else{
			cur = &en->next; // 这样写是为了en=*cur;这个服务
		}
	}
}
void link_destory(link_node **head){
	for(link_node *cur = *head;cur != NULL;){
		link_node *pre=cur;
		cur=cur->next;
		free(pre);
	}
}
void link_print_r(link_node **head){
	link_node *cur = *head;
	for(int cnt = 0;cur!=NULL;cnt++,cur=cur->next){
		printf("%d. data=%d\n",cnt,cur->data);
	}
}
