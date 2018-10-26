#include <stdio.h>
#include <stdlib.h>
typedef struct LNode{
	int index;		//ÿ��ָ��
	float ratio;		//ÿ��ϵ��
	struct LNode *next;
}LNode,*LinkList;
/*----��������-----*/ 
LinkList InsertList(LinkList L,int n);
void PolyPrint(LinkList L);
void ArraySort(LinkList arr[],int n);
LinkList PolySum(LinkList La,LinkList Lb);
/*----------------*/
void CreateList(int n,int m)  			//�������� 
{
	int i;
	LinkList La,Lb,p,Lc;
	La=(LinkList)malloc(sizeof(LNode));
	La=InsertList(La,n);
	printf("��һ������ʽ�������\n");
	PolyPrint(La);
	Lb=(LinkList)malloc(sizeof(LNode));
	Lb->next=NULL;
	Lb=InsertList(Lb,m);
	printf("�ڶ�������ʽ�������\n");
	PolyPrint(Lb);
	Lc=PolySum(La,Lb);
	printf("����ʽ��ӽ��Ϊ:");
	PolyPrint(Lc);
}
LinkList InsertList(LinkList L,int n){	//�������� 
	LinkList p,current_Node;
	LinkList q[n];
	int i;
	current_Node=L;
	for(i=0;i<n;i++){
		p=(LinkList)malloc(sizeof(LNode));
		printf("�������%d��ϵ��:",i+1);
		scanf("%f",&p->ratio);
		if(p->ratio==0){
			continue;
		}
		printf("�������%d��ָ��:",i+1);
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
void ArraySort(LinkList arr[],int n)		//�Խڵ������������ 
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
void PolyPrint(LinkList L){				//�������ʽ 
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
LinkList PolySum(LinkList La,LinkList Lb){		//����ʽ��� 
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
int main()			//������ 
{
	int m,n;
	printf("�������һ������ʽ����:");
	if(scanf("%d",&n)!=1){	
		printf("����������\n");
		return 0;
	}
	printf("������ڶ�������ʽ����:");
	if(scanf("%d",&m)!=1){
		printf("����������\n");
		return 0;
	}
	CreateList(n,m);
	return 0;
}
