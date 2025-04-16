//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 5
		 Implementing 'remove node' operation for BST*/
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
BSTNode* removeNodeFromTree(BSTNode *root, int value);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS2(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS2(BSTNode *root){
	// 1. 스택 초기화 및 예외 처리
	Stack *stack1 = malloc(sizeof(Stack));
	Stack *stack2 = malloc(sizeof(Stack));

	if (stack1 == NULL || stack2 == NULL) {
		printf("메모리 오류 - 할당 실패!\n");
		return;
	}

	stack1->top = NULL;
	stack2->top = NULL;

	if (root == NULL) {
		printf("트리가 비어 있음!\n");
		return;
	}

	// 2. 루트 노드를 스택 1에 푸시
	push(stack1, root);

	// 3. 반복문 - 스택 1이 비어있지 않은 동안 
	while (!isEmpty(stack1)) {
		// 3.1. 스택 1의 top 노드를 pop하여 temp에 저장
		BSTNode *temp = pop(stack1);
		push(stack2, temp);

		// 3.2. temp의 left 자식 노드가 NULL이 아니면 스택 1에 푸시
		if (temp->left !=NULL)
			push(stack1, temp->left);

		// 3.3. temp의 right 자식 노드가 NULL이 아니면 스택 1에 푸시
		if (temp->right !=NULL)
			push(stack1, temp->right);
	}
	
	// 4. 반복문 - 스택 2가 비어있지 않은 동안 
	while (!isEmpty(stack2)) {
		// 4.1. 스택 2의 top 노드를 pop하여 temp에 저장
		BSTNode *temp = pop(stack2);
		// 4.2. temp의 item을 출력
		printf("%d\n", temp->item);
	}

	// 5. 뒤처리 - 스택 1, 스택 2 해제
	free(stack1);
	free(stack2);
}

/* Given a binary search tree and a key, this function
   deletes the key and returns the new root. Make recursive function. */
BSTNode* removeNodeFromTree(BSTNode *root, int value){
	/* 베이스 케이스:
		만약 root가 NULL이면(즉, 트리가 비어있거나 재귀 호출 중에 해당 서브트리가 없다면) 그냥 root를 반환 */
	if (root == NULL)
		return root;

	/* 재귀 호출을 통한 탐색:
		만약 value가 현재 노드의 item보다 작으면 좌측 서브트리에서,
		value가 현재 노드의 item보다 크면 우측 서브트리에서 삭제할 노드를 찾도록 재귀 호출
		같은 건 아래 `} else {` 블록 확인 */
	if (value < root->item) {
		root->left = removeNodeFromTree(root->left, value);
	} else if (value > root->item) {
		root->right = removeNodeFromTree(root->right, value);
	} else {
		/* 삭제 대상 노드를 찾은 경우 (value == root->item):
			자식이 하나 이하이면? 
				좌측 자식이 NULL이면 오른쪽 자식을 임시 포인터에 저장하고, 현재 노드를 free한 후 temp(오른쪽 서브트리)로 대체
				오른쪽 자식이 NULL이면 좌측 자식을 임시 포인터에 저장하고, 현재 노드를 free한 후 temp(좌측 서브트리)로 대체 */
		if (root->left == NULL) { 
			BSTNode *temp = root->right;
			free(root);
			return temp;
		}
		if (root->right == NULL) { 
			BSTNode *temp = root->left;
			free(root);
			return temp;
		}

		/* (cont.) 삭제 대상 노드를 찾은 경우 (value == root->item): 
			두 자식이 모두 있는 경우:
				우측 서브트리내 최솟값인 노드(중위 후계자, 즉, inorder successor)를 검색
				그 노드의 item값을 현재 노드에 복사 => 재귀 호출을 통해 오른쪽 서브트리에서 중위 후계자 노드를 삭제 */
		BSTNode *temp = root->right;

		while (temp && temp->left != NULL)
			temp = temp->left; // 좌측으로 타고 들어감 (우측 서브트리의 최솟값 = 서브트리내 가장 좌측 값)
		
		root->item = temp->item;
		root->right = removeNodeFromTree(root->right, temp->item);

		return root;
	}
}
///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;
	printf("pushed_%d_to_%p\n", node->item, stack);

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
