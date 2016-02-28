/*
 * skip_list_test.c
 *
 *  Created on: 2015年12月21日
 *      Author: bingone
 */


#include <stdio.h>
#include <stdlib.h>
#include "include/skip_list.h"
#include <assert.h>
int main(){

	skip_list *sl = create_skip_list();
	keyType key;
	valueType value;
	for(int i = 0;i<5;i++){
		key = random();
		value = random();
		printf("insert key:%d \t value:%d\n",key,value);
		if(!insert_skip_node(sl,key,value)){
			assert(0);
		}
	}
	print_r_skip_list(sl);

	skip_node *ret = search_skip_list(sl,key);

	printf("find key:%d,value:%d\n",key,*ret);
	remove_skip_list(sl,key);
	print_r_skip_list(sl);

	return 0;
}
