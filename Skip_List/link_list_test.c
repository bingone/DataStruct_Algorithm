/*
 ============================================================================
 Name        : link_list_test.c
 Author      : bingone
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "include/link_list.h"
int main() {
	link_node *head = NULL;
	int d;
	for(int i = 0;i<10;i++){
		if(i==5){
			d=random();
			link_insert(&head,d);
		}else{
			link_insert(&head,random());
		}
	}
	link_print_r(&head);
	link_remove(&head,d);
	link_print_r(&head);
	printf("data:%d\n",d);
	link_destory(&head);
}
