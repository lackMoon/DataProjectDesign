#include <stdio.h>
#include <stdlib.h>
#define PARKSIZE 5
typedef struct CarSite{
	char reach;           //����ĳ���
	int number;           //���ƺ�
	int day;			//���� 
	int time;             //ͣ��ʱ��
	struct CarSite *next; 
}CarSite,*CarMessage;

int top;     					//ͣ����ջ����,topΪջ��
CarMessage road,road_cur;		//������� 
int road_number; 				//����� 
void push(CarMessage arr[],int n,CarMessage node)	//����ͣ���� 
{
	if(top-1==n){					//ͣ��������
		road_cur->next=node;
		road_cur=road_cur->next;
		printf("ͣ��������\n");
		printf("%d��%dʱ:%d�ų�ͣ�ڱ����%d��λ\n",node->day,node->time,node->number,road_number);
		road_number++; //����ϵȴ��ĳ���Ŀ��һ
	}
	else{       		//ͣ����δ��
		arr[top]=node;
		printf("%d��%dʱ:%d�ų�ͣ��ͣ������%d��λ\n",node->day,node->time,node->number,top+1);
		top++;     								//topָ��������һλ
	}
}
void pop(CarMessage arr[],int n,CarMessage node)	//�뿪ͣ���� 
{
	int i,pop,index;             				//popΪ��ʱջ����indexΪ�����ĳ�λ 
	CarMessage pop_parking[PARKSIZE];   		//��ʱջ
	pop=0;
	for(i=0;i<top;i++){			 
		if(arr[i]->number==node->number)
		index=i;
	}
	for(top=top-1;top>=index;top--,pop++)	//��ջ����ʼ�������γ�ջֱ��Ŀ�공���볡 
	{
		pop_parking[pop]=arr[top];
	}
	printf("%d��%dʱ:%d���������뿪��ͣ��%dʱ\n",node->day,node->time,node->number,(node->day-pop_parking[--pop]->day)*24+node->time-pop_parking[--pop]->time);
	pop--;
	top++;
	for(pop;pop>=0;pop--,top++)	     //�����������λ�ջ 
	{	
		arr[top]=pop_parking[pop];
	}
	if(road->next!=NULL){
		push(arr,n,road->next);
		road->next=road->next->next;
		road_number--;
	}
}
CarMessage bubblesort(CarMessage L)//����ʱ��ð������ 
{	
	CarMessage pre,cur,temp;
    for(pre=L->next;pre!=NULL;pre=pre->next){
    	for(cur=pre->next;cur!=NULL;cur=cur->next){
    		if(pre->time>cur->time&&pre->day>=cur->day){
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
	CarMessage Car,current_Node,LR,s,parking[PARKSIZE];
	int i;
	road=(CarMessage)malloc(sizeof(CarSite));
	LR=(CarMessage)malloc(sizeof(CarSite));
	current_Node=LR;
	road_cur=road;
	top=0;
	road_number=1;
	printf("��ʼ��������:\n");
	for(i=0;;i++)
	{
		Car=(CarMessage)malloc(sizeof(CarSite));
		if(scanf("%c,%d,%d,%d",&Car->reach,&Car->number,&Car->day,&Car->time)!=4){
			printf("�������\n");
			exit(0);
		}     
		Car->next=NULL;
		if(Car->reach=='E'||Car->reach=='e')
		{
			break;        
		}
		current_Node->next=Car;
		current_Node=current_Node->next;
		getchar();
	}
	LR=bubblesort(LR);
	s=LR->next;
	while(s!=NULL)
	{
		if(s->reach=='A'||s->reach=='a')
			push(parking,PARKSIZE,s);
		else
			pop(parking,PARKSIZE,s);
		s=s->next;
	}
	return 0;
}
