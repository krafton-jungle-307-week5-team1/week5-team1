//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////
typedef struct _btnode{
	int item; //노드에 저장될 값
	struct _btnode *left; //왼쪽과 자식 노드 포인터
	struct _btnode *right; //오른쪽 자식 노드 포인터
} BTNode;   // You should not change the definition of BTNode

//이진 트리와 BST에서 공통으로 사용하는 노드 구조

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode{
    BTNode *btnode; //스택에 저장할 트리 노드 주소
    struct _stackNode *next; 
    /*
    다음 스택노드의 주소를 가지고 있음(연결리스트 구조)

    "스택"이라는 자료구조에 트리 노드를 잠깐 
    저장하기 위한 중간 저장소


    트리에서 left와 right는 트리 노드들끼리 연결을 의미
    => 트리의 구조

    stackNode 
    =>트리의 구조를 탐색 or 순회하거나 연산을 하기 위해
    잠깐 스택 자료구조 안에 트리 노드 포인터를 저장
    
    */
    
}StackNode;
/*
트리의 순회(전위/중위/후위/레벨순 등)에서
재귀 대신 스택을 써서 구현할 때 필요
*/

typedef struct _stack{
    StackNode *top; 
}Stack; //스택큐에서 봤던 스택 구조체

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int maxHeight(BTNode *node);
//트리의 가장 높은 높이를 구해라

BTNode *createBTNode(int item);

BTNode *createTree();
void push( Stack *stk, BTNode *node);
BTNode* pop(Stack *stk);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    int c;
    char e;
	c = 1;

    BTNode *root;
    root = NULL;

    printf("1: Create a binary tree.\n");
    printf("2: Find the maximum height of the binary tree.\n");
    printf("0: Quit;\n");

    while(c != 0){
        printf("\nPlease input your choice(1/2/0): ");
        if(scanf("%d", &c) > 0)
        {
            switch(c)
            {
            case 1:
                removeAll(&root);
                root = createTree();
                printf("The resulting binary tree is: ");
                printTree(root);
                printf("\n");
                break;
            case 2:
                c = maxHeight(root);
                printf("The maximum height of the binary tree is: %d\n",c);
                removeAll(&root);
                break;
            case 0:
                removeAll(&root);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
		}
        else
        {
            scanf("%c",&e);
        }

    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int maxHeight(BTNode *node)
{
    /*
    트리의 최대 깊이(또는 높이,height)를 구하는 함수
    루트부터 가장 깊은 리프 노드까지 내려가는 데 걸리는
    최대 경로 길이를 구하여라

    [함수 이름 분석]
    BTNode *node : 트리의 루트 노드 포인터(또는 서브트리 루트)
    반환값 int : 해당 트리의 최대 깊이

    [트리의 높이란?]

    루트 노드에서부터 가장 깊은 리프 노드까지의 
    경로에 포함된 노드 수

    루프에서 리프까지 가장 많은 edge 수 (depth) + 1

    [동작흐름]
    1. 만약 NULL 이면 높이 0()
    2. 왼쪽 서브트리 높이 재귀적으로 구한다.
    3. 오른쪽도 재귀적으로 구하기
    4. 둘 중 큰 쪽에 +1 해서 현재 노드 높이 계산

    */

    if (node == NULL)
        return 0;

    int leftHeight = maxHeight(node -> left);
    int rightHeight = maxHeight(node -> right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight ) ;
    //조건 맞으면 오른쪽 값으로 조건 불만족시 왼쪽 값으로 
    
}

///////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item){
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


//////////////////////////////////////////////////////////////////////////////////

BTNode *createTree()
{
    Stack stk;
    BTNode *root, *temp;
    char s;
    int item;

    //만약 입력하는 내용이 문자라면 null 노드로 처리

    stk.top = NULL;
    root = NULL;

    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if(scanf("%d",&item) > 0)
    {
        root = createBTNode(item);
        push(&stk,root);
    }
    else
    {
        scanf("%c",&s);
    }

    while((temp =pop(&stk)) != NULL)
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if(scanf("%d",&item)> 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if(scanf("%d",&item)>0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        if(temp->right != NULL)
            push(&stk,temp->right);
        if(temp->left != NULL)
            push(&stk,temp->left);
    }
    return root;
}

void push( Stack *stk, BTNode *node){
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if(temp == NULL)
        return;
    temp->btnode = node;
    if(stk->top == NULL){
        stk->top = temp;
        temp->next = NULL;
    }
    else{
        temp->next = stk->top;
        stk->top = temp;
    }
}

BTNode* pop(Stack *stk){
   StackNode *temp, *top;
   BTNode *ptr;
   ptr = NULL;

   top = stk->top;
   if(top != NULL){
        temp = top->next;
        ptr = top->btnode;

        stk->top = temp;
        free(top);
        top = NULL;
   }
   return ptr;
}

void printTree(BTNode *node){
    if(node == NULL) return;

    printTree(node->left);
    printf("%d ",node->item);
    printTree(node->right);
}

void removeAll(BTNode **node){
    if(*node != NULL){
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}
