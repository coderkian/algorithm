#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct josephusnode{
	struct josephusnode *next;
	int item;
}jnode;

jnode *jnodeinitial(int n){
	int i=0;
	jnode *head = (jnode*)malloc(sizeof(jnode));
	memset(head, 0, sizeof(jnode));
	head->item=1;
	jnode *tail = head;
	for(i=1; i<n; i++){
		tail->next = (jnode*)(malloc(sizeof(jnode)));
		tail = tail->next;
		tail->item = i+1;
	}
	tail->next = head;
	return head;
}

void reviewjnode(jnode *head){
	jnode *n = head;
	while(n->next != head){ 
		printf(" %d ", n->item);
		n = n->next;
	}
	printf(" %d \n", n->item);
}

int listjosephus(jnode *head){
	jnode *n = head;
	while(n->next!=n){
		jnode *t  = n->next;
		n->next = t->next;
		n = n->next;
		free(t);
	}
	int retv = n->item;
	free(n);
	return retv;
}

int mathjosephus(int n){
	int x=n, y=n;
	while(n){
		y = n;
		n &= n-1;
	}
	x = ~y&x;
	x = 1+(x<<1);
	return x;
}

int main(int argc, char **argv){
	int n = atoi(argv[1]);	
	jnode *jhead = jnodeinitial(n);
	printf("list :j(%d)=%d \n",n,listjosephus(jhead));
	printf("math :j(%d)=%d \n",n,mathjosephus(n));
	return 0;
}
