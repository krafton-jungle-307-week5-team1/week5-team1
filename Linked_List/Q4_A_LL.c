//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 4 */

//pdf 문제 보고 풀어야됨
//remove 노드는 head를 지워준다.

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode
// typedef 로 ListNode라고 별명 붙여줌
// struct _listnode의 자료형인 next의 주소를 가지고 있는 포인터

/*
연결 리스트의 하나의 노드를 정의

item은 노드가 저장할 실제 데이터
struct_listnode *next : 다음 노드를 가리키는 포인터
*/
typedef struct _linkedlist
{
	int size;
	ListNode *head; // 시작 노드를 가리키는 포인터
} LinkedList;			// You should not change the definition of LinkedList
/*
전체 연결리스트 구조를 정의
int size : 연결리스트에 들어있는 노드의 개수
ListNode *head : 리스트의 시작 노드를 가리키는 포인터
이 구조체 하나로 연결리스트 전체 관리 가능

head,tail,size같은 정보를 한꺼번에 다룰 수 있다.

*/

//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveEvenItemsToBack(LinkedList *ll);
/*함수 1번
짝수 값을 가진  (value) 노드들을 모두 뒤로 보내기*/
void printList(LinkedList *ll);
//함수 2번 
void removeAllItems(LinkedList *ll);
//함수 3번
ListNode * findNode(LinkedList *ll, int index);
/*
함수 4번
노드 하나의 주소(포인터)를 반환
전체 연결리스트와 특정 인덱스를 매개변수로 받는다.
ListNode라는 사용자 정의type인거임
원래 이름은 struct_listnode(구조체)=>ListNode

*/
int insertNode(LinkedList *ll, int index, int value);
/*함수 5번 아마도 node삽입?
value가 item 값일듯
주소값은 매개변수로 넘겨주는게 아니라
함수 안에서 malloc() 으로 새로 만들어서 관리

malloc으로 할당해주고 리스트 구조에 맞게 next 조정
*/
int removeNode(LinkedList *ll, int index);
//함수 6번 아마도 노드삭제


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all even integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);
		//1.2.0 중에 입력받기

		switch (c) // c 값이 뭐냐에 따라 case문 실행행
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveEvenItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving even integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void moveEvenItemsToBack(LinkedList *ll)
{
	/* 
	
	내가 생각한 로직
	1. findNode로 짝수 값 찾아서 새로운 큐나 list에 넣어주기(틀림)
	=> 그냥 바로 index계산 로직을 통해 ListNode형 포인터 변수(cur)에 넣어주고
	=> 어떤 노드를 가리키는 주소를 저장함

	2. insertNode로 기존의 리스트에 차례대로 다시 insert,append해주기(맞음)
	ll-> size를 통해서 맨끝에 삽입해주기
	
	*/

	if (ll == NULL || ll -> size == 0)
	   return; //만약 리스트 자체가 존재하지 않으면 그냥 리턴
	
	int index = 0;
	int count = 0;
	int originalSize = ll->size; //ll의 멤버에 다가감

	while(count < originalSize) { //원래의 리스트 크기 만큼만 반복
		ListNode *cur =findNode(ll,index);
		//index번호의 노드 탐색시작 (짝수인지 아닌지)
		if (cur == NULL) break; // 만약 노드가 비어있으면  break

		if(cur->item%2 == 0){ //만약 현재 탐색한 노드의 item값이 짝수라면
			int even = cur ->item; 
			//int형 even변수에 cur노드의 item값을 넣어 준다.
			removeNode(ll,index);
			insertNode(ll,ll->size,even); //마지막부분에 추가
		}
		else{
			index++; // 만약 홀수라면 index추가해주기 remove함수 호출할때
			//짝수인 index값만 넣어줘야 한다. 
		}
		count++; //원래 리스트 만큼만 순회 해줘야 한다.

		

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


ListNode *findNode(LinkedList *ll, int index){

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
