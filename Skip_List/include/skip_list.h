#ifndef _SKIP_LIST
#define _SKIP_LIST
#define MAX_LEVEL 5
#define new_skip_node(n,type) ((type*)malloc(sizeof(type)+n*sizeof(type*)))
#define list_entry(ptr, type, member) \
((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

typedef int keyType;
typedef int valueType;
typedef struct skip_node{
	keyType key;
	valueType value;
	struct skip_node *next[1]; // 这里和**next不同，初始化内容不确定.指针常量与指针变量的区别
}skip_node;
typedef struct skip_list{
	int level;
	skip_node *head;
}skip_list;

skip_node* create_skip_node(int level,keyType key,valueType value);
skip_list* create_skip_list();
int insert_skip_node(skip_list *sl,keyType key,valueType value);
valueType *search_skip_list(skip_list *sl,keyType key);
void remove_skip_list(skip_list *sl,keyType key);
void free_skip_list(skip_list *sl);
void print_r_skip_list(skip_list *sl);
#endif
