//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//////////////////////////////////   linked list /////////////////////////////////

typedef struct _listnode{
   int item;
   struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
   ListNode *tail;
} LinkedList;

////////////////////////////////// stack //////////////////////////////////////////

typedef struct stack{
	LinkedList ll;
} Stack;

////////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int isStackPairwiseConsecutive(Stack *s);

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);

void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int c, value;

    Stack s;

    s.ll.head=NULL;
	s.ll.size =0;
	s.ll.tail =NULL;

    c =1;

    printf("1: Insert an integer into the stack:\n");
    printf("2: Check the stack is pairwise consecutive:\n");
    printf("0: Quit:\n");

    while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the stack: ");
			scanf("%d", &value);
			push(&s, value);
			printf("The stack is: ");
            printList(&(s.ll));
			break;
		case 2:
            if(isStackPairwiseConsecutive(&s))
            {
                printf("The stack is pairwise consecutive.\n");
            }
            else{
                printf("The stack is not pairwise consecutive.\n");
            }
            removeAllItems(&(s.ll));
            break;
		case 0:
			removeAllItems(&(s.ll));
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////

// 문제 :
// 입력 받은 스택에 있는 값들이, 연속적이면서 쌍을 이루는 값들인지 확인하는 함수를 구현하라.
// 조건 - 단, 함수는 push(), pop() 함수만을 이용하라.

// ex) STACK : 5-4-2-1 		=> (5, 4) and (2, 1)  따라서 True
// ex) STACK : 4-5-6-7 		=> (4, 5) and (6, 7)  따라서 True
// ex) STACK : 6-5-4-2-1 	=> (6, 5) and (4) and (2, 1)  따라서 False


// 문제 해결 로직
// 1. 스택에 있는 값의 개수가 홀수거나, 아무것도 없다면? 	 	  => False (return 0)
// 2. 스택에 있는 값을 꺼내 저장한 이후, 그 다음 값과 연속한지 비교.
// 3. 만약 스택에서 꺼낸 수가 이전에 저장한 수와 연속하지 않는다? 	=> False (return 0)
// 4. False를 한번도 거치지 않고 스택의 모든 값을 확인했다?	 	  => True (return 1)
// 5. 인자로 받은 스택은 다시 그대로 보존해야 한다.




int isStackPairwiseConsecutive(Stack *s)
{
	// ver1.
	// 스택이 연결 리스트로 이뤄져 있으니, 새로 리스트를 만들어서 pop한 데이터를 저장.
	// 저장된 데이터와, 새로 pop한 데이터를 비교하며 연속성 확인.
	
	// 1. 스택에 있는 값의 개수가 홀수거나, 아무것도 없을 때,
	if (s->ll.head == NULL || s->ll.size % 2 != 0)
		return 0;

	// 스택에 있는 값을 꺼내, 저장할 리스트 선언 및 초기화.
	LinkedList *new_list = malloc(sizeof(LinkedList));
	new_list->head = NULL;
	new_list->size = 0;
	new_list->tail = NULL;
		
	// 2. 스택에 있는 값을 꺼내 저장한 이후, 그 다음 값과 연속한지 비교.
	while (s->ll.head != NULL)
	{
		// 스택에서 pop을 통해 가져온 값이,
		int temp = pop(s);
		
		// 만약 연결 리스트가 비어있다면, 리스트에 그냥 데이터 삽입.
		if (new_list->size == 0)
			insertNode(new_list, 0, temp);

		// 그게 아니라면, 리스트의 끝에 pop 데이터 삽입.
		else
		{
			ListNode *cur = new_list->head;
			
			// 리스트의 끝에 접근
			while (cur->next != NULL)
				cur = cur->next;
			
			// 일단 연속하면 모두 리스트에 넣고,
			if (cur->item - temp == 1 || cur->item - temp == -1)
				insertNode(new_list, new_list->size, temp);
				
			else {
				// 만약 연속한 숫자의 개수가 짝수개라면, 계속 리스트에 넣고,
				if (new_list->size % 2 == 0)
					insertNode(new_list, new_list->size, temp);
					
				// 3. 만약 스택에서 꺼낸 수가 이전에 저장한 수와 연속하지 않는다? 	=> False (return 0)
				else
				{
					// 스택을 동적 할당했기 때문에, 모두 메모리 해제 후 False
					removeAllItems(new_list);
					free(new_list);					
					return 0;
				}				
			}
		}
	}
	
	// False를 한번도 거치지 않고 스택의 모든 값을 확인했는데, 홀수개라면, False. 짝수면 True.
	int res = new_list->size % 2;

	removeAllItems(new_list);
	free(new_list);

	if (res)
		return 0;
	else
		return 1;


	// 트러블 슈팅
	// - 문제에서 push, pop을 이용하라 했지만, push는 사용하지 않음.
	// - 즉, 스택을 활용한 문제였지만, 연결 리스트로 접근하여 해결.
	// - 함수가 끝났을 때 리스트 데이터가 살아있을 필요성이 없는데, malloc을 사용.
	// - 주어진 스택의 보존이 되지 않음.
	// - 주어진 스택이 짝수일 때만 계산해야 한다는 점을 이용해 좀 더 효율적으로 접근할 수 있음.
	// - 한 쌍씩 연속하면 된다는 점을 이용해, 스택에서 값을 두개씩 꺼내 비교하면 효율적임.


	// 따라서 문제 해결 로직을 부분적으로 수정. - 2, 3번.
	
	// 문제 해결 로직
	// 1. 스택에 있는 값의 개수가 홀수거나, 아무것도 없다면? 	 => False (return 0)
	// 2. 스택에 있는 값을 꺼낼 때, 하나씩 확인하기 보단, 둘 씩 꺼내서 연속하는지 체크
	// 3. 만약 스택에서 꺼낸 수 둘이 연속하지 않는다? 		    => False (return 0)
	// 4. False를 한번도 거치지 않고 스택의 모든 값을 확인했다?	 => True (return 1)
	// 5. 인자로 받은 스택은 다시 그대로 보존해야 한다.

	// ver2. 
	// 리스트말고, 스택과 push, pop을 활용하여 접근.
	
	// 1. 스택에 있는 값의 개수가 홀수거나, 아무것도 없다면? 	 => False (return 0)
    if (s->ll.head == NULL || s->ll.size % 2 != 0)
        return 0;

	// 스택에 있는 값을 꺼낼 때(pop),
	// 원래 스택으로 복원하기 위해 pop한 데이터를 임시 스택에 저장
    Stack tempStack;
    tempStack.ll.head = NULL;
    tempStack.ll.size = 0;

	// 연속한 한 쌍이 유지되고 있는지를 판별하기 위한 변수.
    int pairwise = 1;

	// 2. 스택에 있는 값을 꺼낼 때, 하나씩 확인하기 보단, 둘 씩 꺼내서 연속하는지 체크
    while (!isEmptyStack(s))
    {
		// 스택에서 한번에 두개의 값을 꺼내어 비교.
        int first = pop(s);
        int second = pop(s);
		
		// 원래 입력된 스택의 복원을 위해 임시 스택에 다시 push.
		push(&tempStack, first);
		push(&tempStack, second);

		// 꺼낸 두개의 값이 연속하지 않다면,
        if (abs(first - second) != 1)
        {
			// 3. 만약 스택에서 꺼낸 수 둘이 연속하지 않는다? => False (return 0)
			pairwise = 0;

			// 연속하면서, 한쌍이 아닌 스택이라는걸 알았으면 그만 탐색해도 됨.
			break;
		}    

    }
	// 4. False를 한번도 거치지 않고 스택의 모든 값을 확인했다?	 => True (return 1)

    
	// 5. 인자로 받은 스택은 다시 그대로 보존해야 한다.
    while (!isEmptyStack(&tempStack))
    {
        push(s, pop(&tempStack));
    }

    return pairwise;
	
}

// 결론
// 두가지 방법을 비교했을 때,
// - ver1. 은 삽입할 때마다, 리스트에 가장 마지막 값과 비교하기 때문에, 리스트를 전체 순회하여 N^2의 시간 복잡도를 가짐.
// - ver2. 는 스택을 한번만 순회하면 되기 때문에, N의 시간 복잡도를 가짐.


//////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item){
   insertNode(&(s->ll), 0, item);
}

int pop(Stack *s){
   int item;
   if(!isEmptyStack(s)){
    item = ((s->ll).head)->item;
    removeNode(&(s->ll), 0);
    return item;
   }
    return INT_MIN;
}

int peek(Stack *s){
   return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s){
   if ((s->ll).size == 0)
      return 1;
   return 0;
}

//////////////////////////////////////////////////////////////////////////////////

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
