//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 5 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
void frontBackSplitLinkedList(LinkedList* ll, LinkedList *resultFrontList, LinkedList *resultBackList);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *l);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c = 1; 
	int i;
	LinkedList ll;
	LinkedList resultFrontList, resultBackList;

	//Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	//Initialize the front linked list as an empty linked list
	resultFrontList.head = NULL;
	resultFrontList.size = 0;

	// Initialize the back linked list as an empty linked list
	resultBackList.head = NULL;
	resultBackList.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Split the linked list into two linked lists, frontList and backList:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
	    printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The resulting linked lists after splitting the given linked list are:\n");
			frontBackSplitLinkedList(&ll, &resultFrontList, &resultBackList); // You need to code this function
			printf("Front linked list: ");
			printList(&resultFrontList);
			printf("Back linked list: ");
			printList(&resultBackList);
			printf("\n");
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		case 0:
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////


// ListNode
// 	int item;
// 	struct _listnode *next;

// LinkedList
// 	int size;
// 	ListNode *head;


// void frontBackSplitLinkedList(LinkedList* ll, LinkedList *resultFrontList, LinkedList *resultBackList);

// void printList(LinkedList *ll);
// void removeAllItems(LinkedList *l);
// ListNode * findNode(LinkedList *ll, int index);
// int insertNode(LinkedList *ll, int index, int value);
// int removeNode(LinkedList *ll, int index);


void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
{
	// 1차 시도 : 자를 지점 정하고, 하나하나 노드 만들어주면서 리스트에 각자 넣어주기

	// if (ll->head == NULL)
	// 	return;

	// int front_size;
	
	// if (ll->size%2 == 0)
	// 	front_size = ll->size/2;
	// else
	// 	front_size = ll->size/2+1;

	
	// ListNode *new_Node = malloc(sizeof(ListNode));
	
	// new_Node->item = ll->head->item;
	// new_Node->next = NULL;
	
	// resultFrontList->head = new_Node;
	// resultFrontList->size++;
	
	// ListNode *cur = resultFrontList->head;
	
	// for (int i = 1;i<front_size;i++)
	// {
	// 	ListNode *new_Node = malloc(sizeof(ListNode));
		
	// 	new_Node->item = findNode(ll, i)->item;
	// 	new_Node->next = NULL;

	// 	cur->next = new_Node;
	// 	cur = cur->next;

	// 	resultFrontList->size++;
	// }
	
	// ListNode *new_back = malloc(sizeof(ListNode));

	// new_back->item = findNode(ll, front_size)->item;
	// new_back->next = NULL;
	
	// resultBackList->head = new_back;
	// resultBackList->size++;
	
	// cur = resultBackList->head;

	// for (int i = 1; i < ll->size - front_size; i++)
	// {
	// 	ListNode *new_Node = malloc(sizeof(ListNode));
		
	// 	new_Node->item = findNode(ll, front_size + i)->item;
	// 	new_Node->next = NULL;

	// 	cur->next = new_Node;
	// 	cur = cur->next;

	// 	resultBackList->size++;
	// }
	

	// 2차 시도 : 자를 곳 정하고, 먼저 똑같은 리스트를 만들어놓은 뒤에, 자르기

	// if (ll->head == NULL)
	// 	return;

	// int front_size;
	
	// if (ll->size%2 == 0)
	// 	front_size = ll->size/2;
	// else
	// 	front_size = ll->size/2+1;

	// LinkedList *new_list = malloc(sizeof(LinkedList));
	// ListNode *new_Node = malloc(sizeof(ListNode));

	// new_list->head = new_Node;
	// new_list->size = 1;

	// new_Node->item = ll->head->item;
	// new_Node->next = NULL;

	// ListNode *cur = new_list->head;

	// for (int i = 1; i < ll->size ; i++)
	// {
	// 	ListNode *new_Node = malloc(sizeof(ListNode));
	// 	new_Node->item = findNode(ll, i)->item;
	// 	new_Node->next = NULL;

	// 	cur->next = new_Node;
	// 	cur = cur->next;

	// 	new_list->size++;
	// }

	// resultFrontList->head = new_list->head;
	// cur = findNode(new_list, front_size-1);
	// resultBackList->head = cur->next;
	// cur->next = NULL;

	// resultFrontList->size = front_size;
	// resultBackList->size = ll->size - front_size;

	// free(new_list);

	// 3차 시도 : findNode는 시간복잡도에서 불리하므로, 한번 순회하면서 각각에 다 넣기.

	if (ll->head == NULL)
	return;

	int front_size;

	if (ll->size%2 == 0)
		front_size = ll->size/2;
	else
		front_size = ll->size/2+1;

	ListNode *cur;
	ListNode *ll_cur = ll->head;

	int cnt = 0;

	while (ll_cur != NULL)
	{
		ListNode *new_Node = malloc(sizeof(ListNode));
		new_Node->item = ll_cur->item;
		new_Node->next = NULL;

		if (cnt < front_size)
		{
			if (resultFrontList->head == NULL)
			{
				resultFrontList->head = new_Node;
				cur = resultFrontList->head;
			}
			else
			{			
				cur->next = new_Node;
				cur = cur->next;
			}
			
			resultFrontList->size++;			
		}
		else
		{
			if (resultBackList->head == NULL)
			{
				resultBackList->head = new_Node;
				cur = resultBackList->head;
			}
			else
			{			
				cur->next = new_Node;
				cur = cur->next;
			}
			
			resultBackList->size++;
		}

		ll_cur = ll_cur->next;
		cnt++;
	}
	

}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
