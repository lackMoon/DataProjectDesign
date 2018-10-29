/*
	LR:输入结点(队列)，调用bubblesort进行排序
	Road:便道（队列），push进便道，popRoad出便道，road_number为便道计数变量 
	parking:停车场（栈），push进栈，pop出栈,top为栈顶变量，index为目标车辆索引 
	pop_parking：临时存放(栈)，在pop函数中存放停车场临时让路的车辆 
	其余全为临时变量(循环遍历插入用) 
*/
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
CarMessage Road,road_cur;		//便道变量 
int road_number; 				//便道号 
void push(CarMessage arr[],int n,CarMessage node)	//进入停车场 
{
	if(top==n){					//停车场已满
		CarMessage temp;
		temp=(CarMessage)malloc(sizeof(CarSite));	//形参赋值，不能直接传递地址 
		temp->reach=node->reach;
		temp->number=node->number;
		temp->day=node->day;
		temp->time=node->time;
		temp->next=NULL;
		road_cur->next=temp;
		road_cur=road_cur->next;
		printf("停车场已满\n");
		printf("%d天%d时:%d号车停在便道第%d号位\n",temp->day,temp->time,temp->number,road_number);
		road_number++; //便道上等待的车数目加一
	}
	else{       		//停车场未满
		arr[top]=node;
		printf("%d天%d时:%d号车停在停车场第%d号位\n",node->day,node->time,node->number,top+1);
		top++;     								//top指针移向下一位
	}
}
void popRoad(CarMessage node)		//离开便道 
{
	CarMessage road_next,road_pre;		//临时变量 
	road_pre=Road;
	road_next=Road->next;
	while(road_next!=NULL){
		if(road_next->number==node->number){
			printf("%d天%d时:%d号车已离开便道，停留%d时\n",node->day,node->time,node->number,(node->day-road_next->day)*24+node->time-road_next->time);
			road_pre->next=road_next->next;
			free(road_next);
			road_next=NULL;
			break;
		}
		road_pre=road_pre->next;
		road_next=road_next->next;
	} 
}
void pop(CarMessage arr[],int n,CarMessage node)	//离开停车场 
{
	int i,pop,index;             				//pop为临时栈顶，index为出场的车位 
	CarMessage pop_parking[PARKSIZE];   		//临时栈
	pop=0;
	index=-1;
	for(i=0;i<top;i++){			 
		if(arr[i]->number==node->number)
		index=i;
	}
	if(index==-1){					//停放在便道时 
		popRoad(node);
		return;
	}
	for(top=top-1;top>=index;top--,pop++)	//从栈顶开始汽车依次出栈直至目标车辆离场 
	{
		pop_parking[pop]=arr[top];
	}
	printf("%d天%d时:%d号车已离开停车场，停留%d时\n",node->day,node->time,node->number,(node->day-pop_parking[--pop]->day)*24+node->time-pop_parking[pop]->time);
	pop--;
	top++;
	for(pop;pop>=0;pop--,top++)	     //其他车辆依次回栈 
	{	
		arr[top]=pop_parking[pop];
	}
	if(Road->next!=NULL){
		push(arr,n,Road->next);
		popRoad(Road->next);
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
	LR=(CarMessage)malloc(sizeof(CarSite));
	/*便道初始化*/ 
	Road=(CarMessage)malloc(sizeof(CarSite));
	road_cur=(CarMessage)malloc(sizeof(CarSite));
	Road->next=NULL;
	road_cur=Road;
	road_number=1;
    /*-----*/ 
	current_Node=LR;
	top=0;		//栈初始化 
	printf("开始输入数据:\n");
	for(i=0;;i++)
	{
		Car=(CarMessage)malloc(sizeof(CarSite));
		if(scanf("%c,%d,%d,%d",&Car->reach,&Car->number,&Car->day,&Car->time)!=4){
			printf("输入错误\n");
			printf("请按照'状态,车号,天,时'的格式输出\n");
			printf("如'A,1,1,1'\n"); 
			exit(0);							//最后用fflush()代替 
		}     
		if(!(Car->reach=='A'||Car->reach=='a'||Car->reach=='D'||Car->reach=='d'||Car->reach=='E'||Car->reach=='e'))
		{
			printf("输入状态出错");
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
