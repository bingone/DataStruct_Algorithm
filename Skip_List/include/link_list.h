
#ifndef _LINK_LIST
#define _LINK_LIST
typedef struct link_node{
	int data;
	struct link_node *next;
}link_node;
extern link_node* link_find(int data);
extern int link_insert(link_node **head,int data);
extern void link_remove(link_node **head, int data);
extern void link_print_r(link_node **head);
extern void link_destory(link_node **head);
#endif
