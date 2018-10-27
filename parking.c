#include <stdio.h>
#include <stdlib.h>
#define PARKSIZE 5
typedef struct CarSite{
	char reach;           //到达的车辆
	int number;           //车牌号
	int day;			//天数 
	int time;             //停车时间
	struct CarSite *next; 
}CarSite,*CarMessage;

int top;     					//停车场栈变量,top为栈顶
CarMessage road,road_cur;		//便道变量 
int road_number; 				//便道号 
void push(CarMessage arr[],int n,CarMessage node)	//进入停车场 
{
	if(top-1==n){					//停车场已满
		road_cur->next=node;
		road_cur=road_cur->next;
		printf("停车场已满\n");
		printf("%d天%d时:%d号车停在便道第%d号位\n",node->day,node->time,node->number,road_number);
		road_number++; //便道上等待的车数目加一
	}
	else{       		//停车场未满
		arr[top]=node;
		printf("%d天%d时:%d号车停在停车场第%d号位\n",node->day,node->time,node->number,top+1);
		top++;     								//top指针移向下一位
	}
}
void pop(CarMessage arr[],int n,CarMessage node)	//离开停车场 
{
	int i,pop,index;             				//pop为临时栈顶，index为出场的车位 
	CarMessage pop_parking[PARKSIZE];   		//临时栈
	pop=0;
	for(i=0;i<top;i++){			 
		if(arr[i]->number==node->number)
		index=i;
	}
	for(top=top-1;top>=index;top--,pop++)	//从栈顶开始汽车依次出栈直至目标车辆离场 
	{
		pop_parking[pop]=arr[top];
	}
	printf("%d天%d时:%d号汽车已离开，停留%d时\n",node->day,node->time,node->number,(node->day-pop_parking[--pop]->day)*24+node->time-pop_parking[--pop]->time);
	pop--;
	top++;
	for(pop;pop>=0;pop--,top++)	     //其他车辆依次回栈 
	{	
		arr[top]=pop_parking[pop];
	}
	if(road->next!=NULL){
		push(arr,n,road->next);
		road->next=road->next->next;
		road_number--;
	}
}
CarMessage bubblesort(CarMessage L)//根据时间冒泡排序 
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
	printf("开始输入数据:\n");
	for(i=0;;i++)
	{
		Car=(CarMessage)malloc(sizeof(CarSite));
		if(scanf("%c,%d,%d,%d",&Car->reach,&Car->number,&Car->day,&Car->time)!=4){
			printf("输入错误\n");
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
