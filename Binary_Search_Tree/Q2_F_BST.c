//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1<<20 // 1MB
#define BUFFER_SIZE 1024

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
void inOrderTraversal(BSTNode *node);
void insertBSTNode(BSTNode **node, int value);
void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main_modified(){
    BSTNode *root = NULL;
    char inputLine[MAX_INPUT_SIZE];
	int max_input_numbers = sizeof(inputLine) / sizeof(inputLine[0]);

    printf("정수를 공백으로 구분하여 입력하세요: \n");

    if (fgets(inputLine, sizeof(inputLine), stdin) != NULL) {
        char *token = strtok(inputLine, " \n"); // strtok로 구분자 처리 ==> delim에 포함된 아무 문자라도 만나면 분리함.
        while (token != NULL) {
            int i = atoi(token);
            insertBSTNode(&root, i);
            token = strtok(NULL, " \n");
        }
    }
    
    printf("Binary Search Tree의 in-order traversal 결과: ");
    inOrderTraversal(root);
    printf("\n");
    
    removeAll(&root);
    
    return 0;
}

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the in-order traversal of the binary search tree;\n");
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
			printf("The resulting in-order traversal of the binary search tree is: ");
			inOrderTraversal(root); // You need to code this function
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
// 반복 버전
void inOrderTraversal(BSTNode *root){
	/* 문제: Write an iterative C function inOrderTraversal() that prints the in-
		order traversal of a binary search tree, using a stack.
		Note that you should only use push() or pop() operations when you add 
		or remove integers from the stack. 
		Remember to empty the stack at the end of the function.
	*/
	Stack stk;
	stk.top = NULL; // 초기화는 항상 필수!

    BSTNode* curr = root; // 탐색용 노드

    while (curr != NULL || !isEmpty(&stk)) {
        while (curr != NULL) {
            push(&stk, curr);
            curr = curr->left;
        }

        curr = pop(&stk);
        printf("%d\n", curr->item);
        curr = curr->right;
    }
}

// 재귀 버전
void inOrderTraversal_rcsv(BSTNode *root){
	if (root == NULL) // root라는 포인터 변수가 아무것도 가리키고 있지 않은가? (즉, 저장된 주소값이 NULL인가?)
		return;
	else{
		inOrderTraversal(root->left);
		printf("%d ", root->item);
		inOrderTraversal(root->right);
	}
}


///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL){
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}else{
		if (value < (*node)->item){
			insertBSTNode(&((*node)->left), value);
		}else if (value > (*node)->item){
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
	printf("PUSHED_%d_TO_%p\n", node->item, stack);
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

	printf("POPPED_%d_FROM_%p\n", ptr->item , s);

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
