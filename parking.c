#include <stdio.h>
#include <stdlib.h>
typedef struct CarSite{
	char reach;
	int number;
	int time;
	struct CarSite *next;
}CarSite,*CarMessage;
int top,road_number;
void push(CarMessage arr[],int n,CarMessage node)	//����ͣ���� 
{
	if(top-1==n){
		printf("ͣ��������\n");
		printf("%dʱ:%d�ų�ͣ�ڱ����%d��λ\n",node->time,node->number,road_number);
		road_number++;
	}
	arr[top]=node;
	printf("%dʱ:%d�ų�ͣ��ͣ������%d��λ\n",node->time,arr[top]->number,top+1);
	top++;
}
void pop(CarMessage arr[],int n,CarMessage node)	//��ͣ���� 
{
	int i,pop,index;
	CarMessage pop_parking[5];
	pop=0;
	for(i=0;i<top;i++){			 
		if(arr[i]->number==node->number)
		index=i;
	}
	for(top=top-1;top>=index;top--,pop++)	//��ջ����ʼ�������γ�ջֱ��Ŀ�공���볡 
	{
		pop_parking[pop]=arr[top];
	}
	printf("%dʱ:%d���������뿪��ͣ��%dʱ\n",node->time,node->number,node->time-pop_parking[--pop]->time);
	pop--;
	top++;
	for(pop;pop>=0;pop--,top++){		//�����������λ�ջ 
		arr[top]=pop_parking[pop];
	}
}
CarMessage bubblesort(CarMessage L){	//ð������ 
	CarMessage pre,cur,temp;
    for(pre=L->next;pre!=NULL;pre=pre->next){
    	for(cur=pre->next;cur!=NULL;cur=cur->next){
    		if(pre->time>cur->time){
    			temp=(CarMessage)malloc(sizeof(CarSite));
    			temp->reach=pre->reach;
    			temp->number=pre->number;
    			temp->time=pre->time;
    			pre->reach=cur->reach;
    			pre->number=cur->number;
    			pre->time=cur->time;
    			cur->reach=temp->reach;
    			cur->number=temp->number;
    			cur->time=temp->time;
			}
		}
	}
	return L;
}
int main()
{
	CarMessage Car,current_Node,LR,s,parking[5];
	int i;
	LR=(CarMessage)malloc(sizeof(CarSite));
	current_Node=LR;
	top=0;
	road_number=1;
	printf("��ʼ��������:\n");
	for(i=0;;i++){
		Car=(CarMessage)malloc(sizeof(CarSite));
		scanf("%c",&Car->reach);
		scanf("%d",&Car->number);
		scanf("%d",&Car->time);
		Car->next=NULL;
		if(Car->reach=='E'||Car->reach=='e'){
			break;
		}
		current_Node->next=Car;
		current_Node=current_Node->next;
		getchar();
	}
	LR=bubblesort(LR);
	s=LR->next;
	while(s!=NULL){
		if(s->reach=='A'||s->reach=='a')
			push(parking,5,s);
		else
			pop(parking,5,s);
		s=s->next;
	}
	return 0;
}
