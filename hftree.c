#include <stdio.h>
#include <stdlib.h>
typedef struct HFNode{
	char character;
	int weight,parent,lchild,rchild;
}HFNode,*HuffCode;
void CreateTree(int n);
void selectmin(HuffCode arr[],int n,int *min_node,int *small_node);

void selectmin(HuffCode arr[],int n,int *min_node,int *small_node)
{
	int i;
	*min_node=n;
	for(i=0;i<n;i++){
		if(arr[i]->weight<arr[*min_node]->weight && arr[i]->parent==0){
			*small_node=*min_node;
			*min_node=i;
		}
	}
}
void CreateTree(int n)
{
	HuffCode NodeArray[2*n-1];
	HuffCode NewNode,Node;
	int i,m,weight,min_node,small_node;
	char c;
	m=2*n-1;
	for(i=0;i<m;i++){
		Node=(HuffCode)malloc(sizeof(HFNode));
		Node->lchild=0;
		Node->rchild=0;
		Node->parent=0;
		NodeArray[i]=Node;
	}
	for(i=0;i<n;i++){
		printf("请输入字符:");
		c=getchar();
		NodeArray[i]->character=c;
		getchar();
	}
	for(i=0;i<n;i++){
		printf("请输入权值:");
		scanf("%d",&weight);
		NodeArray[i]->weight=weight;
		getchar();
	}
	for(i=n;i<m;i++){
		NewNode=(HuffCode)malloc(sizeof(HFNode));
		selectmin(NodeArray,i,&min_node,&small_node);
		NewNode->weight=NodeArray[min_node]->weight+NodeArray[small_node]->weight;
		NewNode->lchild=min_node;
		NewNode->rchild=small_node;
		NodeArray[min_node]->parent=i;
		NodeArray[small_node]->parent=i;
		NodeArray[i+1]=NewNode;
	}
	printf("哈夫曼树建立完成");
}

int main()
{
	int n;
	printf("请输入字符集大小:");
	scanf("%d",&n);
	CreateTree(n);
}
