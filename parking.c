/*
	LR:������(����)������bubblesort��������
	Road:��������У���push�������popRoad�������road_numberΪ����������� 
	parking:ͣ������ջ����push��ջ��pop��ջ,topΪջ��������indexΪĿ�공������ 
	pop_parking����ʱ���(ջ)����pop�����д��ͣ������ʱ��·�ĳ��� 
	����ȫΪ��ʱ����(ѭ������������) 
*/
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
CarMessage Road,road_cur;		//������� 
int road_number; 				//����� 
void push(CarMessage arr[],int n,CarMessage node)	//����ͣ���� 
{
	if(top==n){					//ͣ��������
		CarMessage temp;
		temp=(CarMessage)malloc(sizeof(CarSite));	//�βθ�ֵ������ֱ�Ӵ��ݵ�ַ 
		temp->reach=node->reach;
		temp->number=node->number;
		temp->day=node->day;
		temp->time=node->time;
		temp->next=NULL;
		road_cur->next=temp;
		road_cur=road_cur->next;
		printf("ͣ��������\n");
		printf("%d��%dʱ:%d�ų�ͣ�ڱ����%d��λ\n",temp->day,temp->time,temp->number,road_number);
		road_number++; //����ϵȴ��ĳ���Ŀ��һ
	}
	else{       		//ͣ����δ��
		arr[top]=node;
		printf("%d��%dʱ:%d�ų�ͣ��ͣ������%d��λ\n",node->day,node->time,node->number,top+1);
		top++;     								//topָ��������һλ
	}
}
void popRoad(CarMessage node)		//�뿪��� 
{
	CarMessage road_next,road_pre;		//��ʱ���� 
	road_pre=Road;
	road_next=Road->next;
	while(road_next!=NULL){
		if(road_next->number==node->number){
			printf("%d��%dʱ:%d�ų����뿪�����ͣ��%dʱ\n",node->day,node->time,node->number,(node->day-road_next->day)*24+node->time-road_next->time);
			road_pre->next=road_next->next;
			free(road_next);
			road_next=NULL;
			break;
		}
		road_pre=road_pre->next;
		road_next=road_next->next;
	} 
}
void pop(CarMessage arr[],int n,CarMessage node)	//�뿪ͣ���� 
{
	int i,pop,index;             				//popΪ��ʱջ����indexΪ�����ĳ�λ 
	CarMessage pop_parking[PARKSIZE];   		//��ʱջ
	pop=0;
	index=-1;
	for(i=0;i<top;i++){			 
		if(arr[i]->number==node->number)
		index=i;
	}
	if(index==-1){					//ͣ���ڱ��ʱ 
		popRoad(node);
		return;
	}
	for(top=top-1;top>=index;top--,pop++)	//��ջ����ʼ�������γ�ջֱ��Ŀ�공���볡 
	{
		pop_parking[pop]=arr[top];
	}
	printf("%d��%dʱ:%d�ų����뿪ͣ������ͣ��%dʱ\n",node->day,node->time,node->number,(node->day-pop_parking[--pop]->day)*24+node->time-pop_parking[pop]->time);
	pop--;
	top++;
	for(pop;pop>=0;pop--,top++)	     //�����������λ�ջ 
	{	
		arr[top]=pop_parking[pop];
	}
	if(Road->next!=NULL){
		push(arr,n,Road->next);
		popRoad(Road->next);
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
	LR=(CarMessage)malloc(sizeof(CarSite));
	/*�����ʼ��*/ 
	Road=(CarMessage)malloc(sizeof(CarSite));
	road_cur=(CarMessage)malloc(sizeof(CarSite));
	Road->next=NULL;
	road_cur=Road;
	road_number=1;
    /*-----*/ 
	current_Node=LR;
	top=0;		//ջ��ʼ�� 
	printf("��ʼ��������:\n");
	for(i=0;;i++)
	{
		Car=(CarMessage)malloc(sizeof(CarSite));
		if(scanf("%c,%d,%d,%d",&Car->reach,&Car->number,&Car->day,&Car->time)!=4){
			printf("�������\n");
			printf("�밴��'״̬,����,��,ʱ'�ĸ�ʽ���\n");
			printf("��'A,1,1,1'\n"); 
			exit(0);							//�����fflush()���� 
		}     
		if(!(Car->reach=='A'||Car->reach=='a'||Car->reach=='D'||Car->reach=='d'||Car->reach=='E'||Car->reach=='e'))
		{
			printf("����״̬����");
			exit(0);        
		}
		if(Car->reach=='E'||Car->reach=='e')
		{
			break;        
		}
		Car->next=NULL;
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
