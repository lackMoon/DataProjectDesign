#include <stdio.h>
#include <stdlib.h>
typedef struct LNode{
	int index;		//每项指数
	float ratio;		//每项系数
	struct LNode *next;
}LNode,*LinkList;
/*----函数声明-----*/ 
LinkList InsertList(LinkList L,int n);
void PolyPrint(LinkList L);
void ArraySort(LinkList arr[],int n);
LinkList PolySum(LinkList La,LinkList Lb);
/*----------------*/
void CreateList(int n,int m)  			//创建链表 
{
	int i;
	LinkList La,Lb,p,Lc;
	La=(LinkList)malloc(sizeof(LNode));
	La=InsertList(La,n);
	printf("第一个多项式建立完成\n");
	PolyPrint(La);
	Lb=(LinkList)malloc(sizeof(LNode));
	Lb->next=NULL;
	Lb=InsertList(Lb,m);
	printf("第二个多项式建立完成\n");
	PolyPrint(Lb);
	Lc=PolySum(La,Lb);
	printf("多项式相加结果为:");
	PolyPrint(Lc);
}
LinkList InsertList(LinkList L,int n){	//插入链表 
	LinkList p,current_Node;
	LinkList q[n];
	int i;
	current_Node=L;
	for(i=0;i<n;i++){
		p=(LinkList)malloc(sizeof(LNode));
		printf("请输入第%d项系数:",i+1);
		scanf("%f",&p->ratio);
		if(p->ratio==0){
			continue;
		}
		printf("请输入第%d项指数:",i+1);
		scanf("%d",&p->index);
		p->next=NULL;
		q[i]=p;
		}
		ArraySort(q,n);
		for(i=0;i<n;i++){
			if(q[i]->index==current_Node->index){
				current_Node->ratio+=q[i]->ratio;
			}
			else{
			current_Node->next=q[i];
			current_Node=current_Node->next;
			}
		}
		current_Node=NULL;
	return L;
}
void ArraySort(LinkList arr[],int n)		//对节点数组进行排序 
{
	int i,j;
	LinkList temp;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(arr[i]->index<arr[j]->index){
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}	
}
void PolyPrint(LinkList L){				//输出多项式 
	LinkList s;
	s=L->next;
	while(s){
		if(s->index!=0)
		printf("%.1fx^%d",s->ratio,s->index);
		else
		printf("%.1f",s->ratio);
		if(s->next!=NULL){
			printf("+");
		}
		s=s->next;
	}
	printf("\n");
}
LinkList PolySum(LinkList La,LinkList Lb){		//多项式相加 
	LinkList a,b,c;
	LinkList Lc=(LinkList)malloc(sizeof(LNode));
	a=La->next;
	b=Lb->next;
	c=Lc;
	while(a){
		while(b){
			if(a->index>b->index){
				c->next=a;
				a=a->next;
				c=c->next;
			}
			else if(a->index<b->index){
				c->next=b;
				b=b->next;
				c=c->next;
			}
			else{
				a->ratio+=b->ratio;
				c->next=a;
				a=a->next;
				b=b->next;
				c=c->next;
			}
		}
		c->next=a;
		a=a->next;
		c=c->next;
	}
	return Lc;
}
int main()			//主函数 
{
	int m,n;
	printf("请输入第一个多项式项数:");
	if(scanf("%d",&n)!=1){	
		printf("请输入数字\n");
		return 0;
	}
	printf("请输入第二个多项式项数:");
	if(scanf("%d",&m)!=1){
		printf("请输入数字\n");
		return 0;
	}
	CreateList(n,m);
	return 0;
}
