//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 5 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;	// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	//큐의 길이(문제에 따라 사용여부 다르다)
	ListNode *head;
	//큐의 front 제일 먼저 들어온 노드를 가리킨다.
	/*보통 rear 포인터도 필요하지만 연결리스트에 head만 쓰고 
    rear는 동적으로 탐색해서 사용한다. 
	*/
} LinkedList;	// You should not change the definition of LinkedList

                                                          
typedef struct _queue
{
	LinkedList ll;
	/*Queue 구조체 포인터 q의 멤버
	ll라는 연결리스트트에 접근하기 위해서는 '->' 사용
	*/
	/*내부에 연결리스트를 포함하고 있다.
	ll.head가 front 
	새 노드는 마지막 노드 뒤에 연결 
	삭제는 head에서 진행한다. 
	*/
} Queue;  // You should not change the definition of Queue

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void recursiveReverse(Queue *q);

// You may use the following functions or you may write your own
void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *q);
void removeAllItemsFromQueue(Queue *q);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll; //연결리스트 변수 ll 하나 생성
	Queue q;

	c = 1;

	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initialize the Queue as an empty queue
	q.ll.head = NULL;
	q.ll.size = 0;


	printf("1: Insert an integer into the Queue:\n");
	printf("2: Recursively reverse the queue;\n");
	printf("0: Quit:\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the queue: ");
			scanf("%d", &i);
			enqueue(&q, i);
			printf("The resulting queue is: ");
			printList(&q.ll);
			break;
		case 2:
			recursiveReverse(&q); // You need to code this function
			printf("The resulting reversed queue is: ");
			printList(&(q.ll));
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

////////////////////////////////////////////////////////////

void recursiveReverse(Queue *q)
//큐의 값을 재귀적으로 역순으로 바꾸는 함수 
{

    if (isEmptyQueue(q))
	   return;
	int item =dequeue(q); 
	//dequeue 함수호출을 통해 앞의 요소를 꺼냄
	recursiveReverse(q); //재귀 호출로 나머지를 뒤집음
	enqueue(q,item); //꺼낸 값을 뒤에 다시 추가

  

}

//////////////////////////////////////////////////////////////////

void removeAllItemsFromQueue(Queue *q)
{
	//재귀로 뒤집은 후 큐를 초기화 할 때
	//프로그램 종료 전에 메모리를 정리할 때 
	int count, i;
	if (q == NULL)
		return;
	count = q->ll.size;

	for (i = 0; i < count; i++)
		dequeue(q);
		//count 동안 모든 요소 pop시켜주기
}
//////////////////////////////////////////////////////////////////////////////////

void removeAllItems(LinkedList *ll)
{
	//연결리스트 자체를 메모리 해제하면서 완전히 초기화화
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		//모든 노드를 따라가면서 free로 메모리 해제
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

///////////////////////////////////////////////////////////////////////////////

void enqueue(Queue *q, int item) {
	insertNode(&(q->ll), q->ll.size, item);
	// 큐의 rear에 노드를 추가하는 함수
	//매번 연결리스트 끝까지 따라가서 삽입 O(n)
}

int dequeue(Queue *q) {
	//큐의 Front에 노드를 제거하여 반환하는 함수
	int item;

	if (!isEmptyQueue(q)) {
		/*queue가 비었는지 확인하는 함수
		큐가 비어있지 않을 때만 아래 코드를 실행 한다.*/

		item = ((q->ll).head)->item;
		/*
		q->ll :큐 안에 있는 연결리스트
		(q->ll).head => 연결리스트의 맨 앞 노드
		((q.ll).head)->item : 그 맨 앞 노드의 값

		즉 큐의 front 값을 꺼내서 item 변수에 저장한다
		*/

		removeNode(&(q->ll), 0);
		/*연결리스트에서 0번째 노드(맨 앞)를 삭제하는 함수
		&(q->ll): 연결리스트 포인터 전달
		front 노드를 삭제*/


		return item; // 앞에서 꺼낸 값을 함수 결과로 반환

	}
	return -1;
}

int isEmptyQueue(Queue *q) {
	if ((q->ll).size == 0)
		return 1;
	//큐가 비었는지 확인하기 큐의 사이즈가 0 이라면 빈거

	return 0;
}

void printList(LinkedList *ll){
	/*
	큐(연결리스트)에 있는 모든 값을 앞에서 부터 
	차례대로 출력하는 함수
	*/

	ListNode *cur;
	/*현재 노드를 가리킬 포인터 변수 cur 선언
	리스트를 순회할 때 사용할 루프용 포인터
	현재의 위치를 추적하는 역할
	*/
	if (ll == NULL)
		return;
	/*포인터 ll자체가 NULL이면 리스트가 아예 존재하지
	않는 상황이므로 바로 return
	*/
	
	cur = ll->head;
	/*
	리스트의 첫번째 노드를 가리킴
	연결리스트는 항상 head부터 시작해서 순회
	*/
	if (cur == NULL)
		printf("Empty");
	/*맨 앞 확인했는데 null 이면 비어있다.
	리스트는 존재하지만 첫 번째 노드가 없는거임
	빈 리스트 처리!
	*/
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
		/*
		리스트의 끝(NULL)까지 반복하며
		현재 노드의 item을 출력하고
		다음 노드로 이동 
		*/
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){
	/*
    [함수 개요]

	연결리스트에서 특정 인덱스 위치에 있는 노드의
	포인터를 찾아서 반환해주는 함수

	ll: 노드를 찾을 연결리스트의 포인터
	index: 찾고자 하는 노드의 위치(인덱스는 0부터 시작)

	[반환값]
	해당 인덱스에 있는 노드의 주소(포인터) temp
	해당 인덱스가 없다면 NULL

	*/

	ListNode *temp;
	// 현재 순회 중인 노드를 가리킬 포인터

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;
	/*
	리스트 포인터가 비어 있거나
	음수 인덱스거나
	리스트 크기를 넘는 인덱스일 경우 
	=> 존재하지 않는 노드를 찾는 것이므로 NULL 반환
	*/

	temp = ll->head;
	//위의 case가 아니라면 head부터 탐색 시작

	if (temp == NULL || index < 0)
		return NULL;
	//head가 비어있다? => 연결리스트가 비어있음

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
		//temp==NULL이면 리스트 끝에 도달한 것
			return NULL;
		index--;
		/*
		index는 인자로 준 위치부터 0이 될때까지 
		줄어들면서 
		temp가 index가 0까지 줄어들때동안
		한칸씩 ++ 되면서 다음 노드를 탐색

		즉 index는 남은 거리 카운트 하는 용도
		
		*/
	}

	return temp;
	/*
	노드를 가리키는 포인터
	찾은 노드의 주소를 반환한다.

	findNode() 함수를 사용하는 쪽에서는
	그 노드를 직접 다룰 수 있는 포인터를 받게됨


	[예시]

	ListNode *result =find(&ll,2);
	=>result는 ll 리스트에서 index 2번째 노드를 가리킴

	printf("%d",result->item);->index 2번째 값 출력
	result->item =100; -> index 2번째 값 수정 가능
	*/
}

int insertNode(LinkedList *ll, int index, int value){

	/*
    [함수 개요]

	연결리스트에 '새로운 노드'를 지정한 위치(index)에 
	삽입하는 함수 findnode 사용

	ll: 삽입할 연결리스트의 포인터(주소를 받아서 직접 수정)
	주소로 안받으면 복사해서 넘겨주기 때문에 실제 수정이 아님님
	index: 삽입할 위치(0부터 시작)
	value: 새로 삽입할 노드의 데이터

	[반환값]
	0: 성공
	-1: 실패

	*/

	ListNode *pre, *cur;
	/*
	pre: 삽입 위치의 앞 노드를 가리킴
	cur: 기존에 있던 노드(삽입할 노드 뒤에 붙일 노드)
	*/

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		//리스트가 비었거나, index가 0일 때때
		cur = ll->head;
		//기존의 head를 cur에 저장
		ll->head = malloc(sizeof(ListNode));
		//새 노드를 만들고, head를 새 노드로 설정
		//if줄 지나서 다음 코드드 실행


		if (ll->head == NULL)
		//메모리 할당 실패 시 프로그램 종료, 예외처리
		{
			exit(0);
		}
		ll->head->item = value;
		//새 노드에 데이터를 저장
		ll->head->next = cur;
		//새 노드의 다음 노드로 cur를 연결
		ll->size++;
		//리스트에 하나 추가했으니까 크기 1증가
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	
	//중간 or 끝에 삽입할 경우 
	/*
	ex)insertNode(&ll,2,99) : index 2 위치에 99 삽입

	*/
	if ((pre = findNode(ll, index - 1)) != NULL){
		/*
		삽입하려는 위치 바로 앞의 노드를 찾기(index-1)
		이걸 pre가 가리키게 함
		*/
		cur = pre->next;
		/*
		cur는 원래 pre다음에 있던 노드
		새로 삽입될 노드 '뒤'에 붙을 노드
		*/
		pre->next = malloc(sizeof(ListNode));
		/*새 노드를 만들어서 pre->next가 가리키게 한다
		pre(삽입할 위치 앞에 있는)->newNode 연결됨
		
		*/
		if (pre->next == NULL)
		{
			exit(0);
		}
		pre->next->item = value;
		//새 노드에 값 넣기
		pre->next->next = cur;
		//새 노드의 next는 원래 pre다음 노드 였던 cur
		ll->size++;
		return 0;
	}

	return -1; //실패했을 때 반환 값
}


int removeNode(LinkedList *ll, int index){

	/*
	[함수 정의 요약]
	LinkedList *ll: 삭제 대상이 될 연결리스트의 포인터
	int index: 삭제할 노드의 위치

	[반환값]
	0: 성공
	-1: 실패
	*/

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;
	//위의 함수들과 same 리스트자체가 비었거나 인덱스가 음수거나 size 이상이거나

	// If removing first node, need to update head pointer
	if (index == 0){
		//첫번째 노드를 삭제하는경우 (head)
		cur = ll->head->next; 
		//head의 next 노드 즉, 두번째 노드를 임시보관관
		free(ll->head); //첫 번 째 노드를 메모리 해제
		ll->head = cur; //헤드를 cur에 넣어둔 두번째 노드로 바꾸기
		ll->size--; //하나 삭제했으니까 사이즈 줄이기기
		return 0;//성공했으니까 0반환환
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		//중간이나 끝 노드 삭제하는 경우
		//인덱스는 내가 삭제하고싶다고 말한 노드의 위치
		/*
		index 바로 앞 노드를 찾아서 pre에 저장하고
		그게 null이 아니면 아래의 코드 실행
		*/

		if (pre->next == NULL)
			return -1;

		cur = pre->next;//현재 삭제할 노드를 가리키는 포인터
		/*
		pre: 삭제 대상의 바로 앞 노드
		pre->next 삭제 대상노드
		*/
		pre->next = cur->next;
		//삭제대상 cur을 건너뛰고 다음노드로 이어지게 연결결
		free(cur);
		//메모리에서 cur이 가리키는 노드를 free로 해제
		ll->size--;
		//리스트에서 노드 하나 줄었으니까 크기 감소

		return 0;
	}

	return -1;
}
