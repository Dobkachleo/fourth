/** \file tree.cpp
*   \brief Tree implementation code
*/

#include <stdio.h>
#include <conio.h>
#include <locale.h>

/** \struct List
*   \brief Struct is implementation of singly-linked list
*/
struct List {
	int number;
	List *next;
	int depth;
};

/** \struct Tree
*	\brief Struct is implementation of non-binary tree
*/

struct Tree {
	int size;
	List *nodes;
};

/** \fn void Push(List **head, int data)
*   \brief Function pushes new element at the end of list
*
*	\param **head - list head pointer-pointer
*   \param value - value of element
*	\param d - depth of element
*   <br>tmp - temporary list
*/
void Push(List **head, int value, int d) {
	List *tmp=new List;
	tmp->number=value;
	tmp->depth=d;
	tmp->next=*head;
	*head=tmp;
};

/** \fn List* Get(List* head, int i)
*	\brief Function returns pointer to i-th element
*
*	\param *head - list head pointer
*	\param i - place of element
*	<br>k - counter
*/
List* Get(List* head, int i) {
	int k=0;
	while ((k<i)&&head) {
		head=head->next;
		k++;
	}
	return head;
}

/** \fn void Insert(List *head, int i, int val)
*	\brief Function inserts i-th element
*
*	\param *head - list head pointer
*	\param i - place of new element
*	\param val - value of i-th element
*	\param d - depth of element
*	<br>*tmp - temporary list pointer
*/
void Insert(List *head, int i, int val, int d) {
	List *tmp=NULL;
	int k=0;
	while ((k<i)&&head->next) {
		head=head->next;
		k++;
	}
	tmp=new List;
	tmp->number=val;
	tmp->depth=d;
	if (head->next) tmp->next=head->next;
	else tmp->next = NULL;
	head->next=tmp;
}

/** \fn void Pop(List **head, int n)
*	\brief Function deletes i-th element
*
*	\param **head - list head pointer-pointer
*	\param i - place of old element
*	<br>*prev - list pointer returning (i-1)-th place
*	<br>*then - list pointer returning place of the next element
*	<br>val - value of this element
*/
void Pop(List **head, int i) {
	if (*head==NULL) return;
	else {
		List *prev=Get(*head, i-1);
		List *then=prev->next;
		int val=then->number;
		int d=then->depth;
		prev->next=then->next;
		delete then;
	}
}

/** \fn int length(List *head)
*	\brief Function returns length of list
*
*	\param *head - list head pointer
*	<br>i - counter. After count it turns to length
*/
int length(List *head) {
	int i=0;
	while (head) {
		head=head->next; i++;
	}
	return i;
}

/** \fn void PopBack(List **head)
*	\brief Function deletes zero element
*
*	\param **head - list head pointer-pointer
*	<br>*prev - list pointer returning penultimate place
*/
void PopBack(List **head) {
	if (*head==NULL) return;
	else {
		List *prev=Get(*head, length(*head)-2);
		prev->next=NULL;
	}
}

/** \fn int Find(List *head, int set)
*	\brief Function returns value of selected element
*
*	\param *head - list head pointer
*	\param set - place of desirable element
*	<br>*p - list head backup pointer
*/
int Find(List *head, int set) {
	List *p=head;
	for (int i=0; i<length(head)-set-1; i++) p=p->next;
	return p->number;
}

/** \fn void ShowReverse(List *head)
*	\brief Function returns list in reverse order
*
*	\param *head - list head pointer
*	\param n - number of elements
*	<br>i - counter
*/
void ShowReverse(List *head, int n) {
	int i=n;
	while (head) {
		for (int k=0; k<head->depth; k++) printf("\t");
		printf("%d\n",head->number);
		head=head->next; i--;
	}
}

/** \fn void ShowFirst(List *head)
*	\brief Function returns the first element of list
*
*	\param *head - list head pointer
*/
void ShowFirst(List *head) {
	while (head->next) head=head->next;
	for (int i=0; i<head->depth; i++) printf("\t");
	printf("%d\n",head->number);
}

/** \fn void ShowDirect(List *head, int n)
*	\brief Function returns list in direct order
*
*	\param *head - list head pointer
*	\param n - number of elements
*/
void ShowDirect(List *head, int n) {
	for (int i=n; i>0; i--) {
		ShowFirst(head);
		PopBack(&head);
	}
}

/** \fn void ShowSimm(Tree *tree)
*	\brief Function shows tree structure in simmetrical walk
*
*	\param *tree - tree pointer
*	<br>tmp - temporary variable for list element data
*	<br>dep - temporary variable for the same element depth
*/
void ShowSimm(Tree *tree) {
	int tmp,dep;
	if (tree==NULL) return;
	else {
		tmp=Find(tree[1].nodes,0);
		dep=Get(tree[1].nodes,length(tree[1].nodes)-1)->depth;
		PopBack(&tree[1].nodes);
		ShowFirst(tree[1].nodes);
		PopBack(&tree[1].nodes);
		for (int i=0; i<dep; i++) printf("\t");
		printf("%d\n",tmp); ShowDirect(tree[1].nodes,length(tree[1].nodes));
		
		ShowFirst(tree[0].nodes);

		for (int i=1; i<tree->size; i++)
			if (length(tree[i].nodes)>1) ShowDirect(tree[i].nodes,length(tree[i].nodes));

		if (length(tree[0].nodes)>2) {
			for (int i=0; i<3; i++) PopBack(&tree[0].nodes);
			ShowDirect(tree[0].nodes,length(tree[0].nodes));
		}
	}
}

int main()
{
	setlocale(LC_ALL,"rus");

	Tree *root=new Tree; root[0].nodes=NULL; List* tree_sim=NULL;
	Push(&root[0].nodes, 12, 0); Push(&root[0].nodes, 5, 1); Push(&root[0].nodes, 9, 1); Push(&root[0].nodes, 10, 1);
	Push(&tree_sim, 12, 0); Push(&tree_sim, 5, 1); Push(&tree_sim, 9, 1); Push(&tree_sim, 10, 1);
	root->size=4; for (int i=1; i<root->size; i++) root[i].nodes=NULL;

	Push(&root[1].nodes, Find(root[0].nodes,1), 1); Push(&root[1].nodes, 3, 2); Push(&root[1].nodes, 7, 2);
	Insert(tree_sim,1,3,2); Insert(tree_sim,1,7,2); Insert(tree_sim,0,11,2);
	root->size+=2; for (int i=4; i<root->size; i++) root[i].nodes=NULL;

	Push(&root[2].nodes, Find(root[1].nodes,1), 2); Push(&root[3].nodes, Find(root[1].nodes,2), 2);
	Push(&root[4].nodes, Find(root[0].nodes,2), 1); Push(&root[4].nodes, 11, 2);
	Push(&root[5].nodes, Find(root[4].nodes,1), 2); Push(&root[6].nodes, Find(root[0].nodes,3), 1);
	List* tree2=NULL;
	int p=length(tree_sim);
	for (int i=0; i<p; i++)
		Push(&tree2,Find(tree_sim,i),Get(tree_sim,p-i-1)->depth);
	printf("Direct walk\n"); ShowDirect(tree_sim,7);
	printf("\nReverse walk\n"); ShowReverse(tree2,7);
	printf("\nSymmetrical walk\n"); ShowSimm(root);

	getch();
}