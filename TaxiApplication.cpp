#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct booking
{
	int taxi_id;
	int booking_id;
	char from;
	char to;
	int pickup;
	int drop;
	int amount;
	int isavailable;
};
typedef struct booking booking;
void showAvailability(booking *b,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("Availability of Taxi %d is :%d\n",i+1,b[i].isavailable);
	}
	/*for(i=0;i<n;i++)
	{
		printf("Drop of Taxi %d is :%d\n",i+1,b[i].drop);
	}*/
}
int getTaxi(booking *b,int n,int pickup)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(	(b[i].isavailable == 0) && (b[i].drop != 0)	)
		{
			if(	(b[i].drop) <= pickup)
			{
				return i;
			}
		}
	}
	for(i=0;i<n;i++)
	{
		if(b[i].isavailable == 1)
		{
			b[i].isavailable = 0;
			return i;
		}
	}
}
int getDrop(char a,char b)
{
	int var1 = int(a);
	int var2 = int(b);
	int res = abs(var1-var2);
	return res;
}
int getAmount(char a,char b)
{
	int var1 = int(a);
	int var2 = int(b);
	int res = abs(var1-var2);
	int amount;
	if(res <= 1)
	{
		amount = 100;
	}
	else
	{
		amount = ((res-1)*50)+100;
	}
	return amount;
}
void displayLog()
{
	FILE *fp; 
	fp = fopen("log.txt","r");
	printf("TAXI_ID\tBOOKING_ID\tFROM\tPICKUP_TIME\tTO_TIME\t\tDROP_TIME\tAMOUNT\n");
	char tid[5],bid[5],pickup[5],drop[5],amount[5];
	char from[5],to[5];
	do
	{
		fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\n",tid,bid,from,pickup,to,drop,amount);
		printf("%s\t\t",tid);
		printf("%s\t",bid);
		printf("%s\t",from);
		printf("%s\t\t",pickup);
		printf("%s\t\t",to);
		printf("%s\t\t",drop);
		printf("%s\n",amount);
	}while(!feof(fp));
	fclose(fp);
}
void setTaxi(booking *b,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		b[i].isavailable = 1;
		b[i].drop = 0;
	}
}
int myid=1;
void assignTaxi(booking *b,int a,int b_,char c,char d,int e,int f,int g)
{
	FILE *fp;  
   	fp = fopen("log.txt", "a");
	b[a].taxi_id = a+1;
	b[a].booking_id = myid++;
	b[a].from = c;
	b[a].to = d;
	b[a].pickup = e;
	b[a].drop = f;
	b[a].amount = g;
	printf("\n");
	printf("Your Booking ID is B%d.You will be travelling in the Taxi_%d , from the point %c picked up at %d and dropped at point %c at %d.You have to pay %d as the Booking Pay\n",b[a].booking_id,b[a].taxi_id,b[a].from,b[a].pickup,b[a].to,b[a].drop,b[a].amount);
	printf("\n");
	fprintf(fp,"%d\t",b[a].taxi_id);
	fprintf(fp,"%d\t",b[a].booking_id );
	fprintf(fp,"%c\t",b[a].from);
	fprintf(fp,"%c\t",b[a].to);
	fprintf(fp,"%d\t",b[a].pickup);
	fprintf(fp,"%d\t",b[a].drop);
	fprintf(fp,"%d\n",b[a].amount);
	fclose(fp); 
}
void clearLog(booking *b,int n)
{
	setTaxi(b,n);
	FILE *fp;  
   	fp = fopen("log.txt", "w");
	fclose(fp);
	printf("Log is Cleared\n");	
}
int main()
{
	int n;
	printf("Enter the number of Taxi : \n");
	scanf("%d",&n);
	booking b[n];
	setTaxi(b,n);
	int choice;
	do
	{
		printf("********************\nEnter Your Choice :\n********************\n1.Book Taxi\n2.Display Log\n3.Clear Log\n4.Exit\n********************\n");
		scanf("%d",&choice);
		int id,pickup,drop;
		char from[10];
		char to[10];
		int id_;
		int amount;
		int book_id = 0;
		switch(choice)
		{
			case 1:
			{
				showAvailability(b,n);
				printf("*****Enter the Current Location*****\n");
				scanf("%s",from);
				printf("*****Enter the Drop Location*****\n");
				scanf("%s",to);
				printf("*****Enter the Pick Up Time*****\n");
				scanf("%d",&pickup);
				id = getTaxi(b,n,pickup);
				if(id < n )
				{	
					drop = (getDrop(from[0],to[0])+pickup);
					amount = getAmount(from[0],to[0]);
					printf("\n");	
					printf("You are at : %c",from[0]);
					printf("\n");		
					printf("Your Drop Location : %c",to[0]);
					printf("\n");		
					printf("Your Pick Up Time : %d",pickup);
					printf("\n");
					printf("Your Drop Time : %d",drop);
					printf("\n");
					printf("Amount to be Paid : %d",amount);
					printf("\n");
					assignTaxi(b,id,book_id+1,from[0],to[0],pickup,drop,amount);
					printf("\nThe Alloted Taxi is TAXI_%d \n\n",id+1);
				}
				else
				{
					printf("Sorry..!!\nNo Taxi is Available..!!\n");
				}
				break;
			}
			case 2:
			{
				displayLog();
				break;
			}
			case 3:	
			{
				clearLog(b,n);
				break;
			}
			default:
			{
				printf("Application Exited..!!\n");
				break;
			}
		}
	}while(choice<4);
	return 0;
}
