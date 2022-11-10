#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROOM_NUMBER 100
typedef struct{
	char *ClientName;
	char *ClientSurname;
}ClientInfo;
typedef struct{
	int day;
	int month;
	int year;
}Date;
typedef struct{
	int PersonNumber;
	int RoomState;
	int RoomNumber;
	double price;
	ClientInfo client;
	Date entrance;
	Date departure;
}RoomInfos;
typedef enum{
	client=0,staff=1,
}Badge;
int DayDif(Date entrance,Date departure){
	if(entrance.day>departure.day){
		departure.month-=1;
		departure.day+=30;
	}
	if(entrance.month>departure.month){
		departure.year-=1;
		departure.month+=12;
	}
	Date daydif;
	daydif.day=departure.day-entrance.day;
	daydif.month=departure.month-entrance.month;
	daydif.year=departure.year-entrance.year;
	int dif=daydif.year*365+daydif.month*30+daydif.day;
	return dif;
	
}
double PriceCalc(RoomInfos *rooms,int RoomNumber){
	int diff=DayDif(rooms[RoomNumber-1].entrance,rooms[RoomNumber-1].departure);
	printf("The day number you stay : %d\n",diff);
	return diff*150*rooms[RoomNumber-1].PersonNumber;
}
void ClearRes(RoomInfos *rooms,int RoomNumber){
	rooms[RoomNumber-1].RoomState=0;
	free(rooms[RoomNumber-1].client.ClientName);
	free(rooms[RoomNumber-1].client.ClientSurname);
	printf("%d. room exit process has done successfully!\n",RoomNumber);
}
void Query(RoomInfos *rooms,int RoomNumber){
	RoomNumber=rooms[RoomNumber-1].RoomNumber;
	if(rooms[RoomNumber-1].RoomState!=0){
		printf("The room is full until %d:%d:%d!\n",rooms[RoomNumber-1].departure.day,rooms[RoomNumber-1].departure.month,rooms[RoomNumber-1].departure.year);
	}else{
		printf("%d. room is available right now!\n",rooms[RoomNumber-1].RoomNumber);
	}
}
void TotalPrice(){
	int PerNum;
	double total=0.0;
	Date entrance,departure;
    printf("\n\n------------------------------------\n\n");
	printf("Please enter the person number : ");
	scanf("%d",&PerNum);
	printf("\n\n------------------------------------\n\n");
	printf("Please enter the date of entrance as(day:month:year) : ");
	scanf("%d:%d:%d",&entrance.day,&entrance.month,&entrance.year);
	printf("\n\n------------------------------------\n\n");
	printf("Please enter the date of departure as(day:month:year) : ");
	scanf("%d:%d:%d",&departure.day,&departure.month,&departure.year);
	printf("\n\n------------------------------------\n\n");
	total=DayDif(entrance,departure)*PerNum*150;
	printf("\n\n------------------------------------\n\n");
	printf("Total Price : %.2lfTL",total);
	printf("\n\n------------------------------------\n\n");	
}
void ShowRooms(RoomInfos *rooms){
	int i;
	for(i=0;i<ROOM_NUMBER;i++){
		if(rooms[i].RoomState!=0){
		printf("\n\n------------------------------------\n\n");
	    printf("%d.Room : ",rooms[i].RoomNumber);
	    printf("\n\n------------------------------------\n\n");
	    printf("Client Name/Surname : %s %s",rooms[i].client.ClientName,rooms[i].client.ClientSurname);
	    printf("\n\n------------------------------------\n\n");
	    printf("Person Number : %d",rooms[i].PersonNumber);
	    printf("\n\n------------------------------------\n\n");
	    printf("Price : %.2lf",rooms[i].price);
	    printf("\n\n------------------------------------\n\n");
	    printf("Entrance : %d:%d:%d",rooms[i].entrance.day,rooms[i].entrance.month,rooms[i].entrance.year);
	    printf("\n\n------------------------------------\n\n");
	    printf("Departure : %d:%d:%d",rooms[i].departure.day,rooms[i].departure.month,rooms[i].departure.year);
	    printf("\n\n------------------------------------\n\n");
		}
	}
}
void AddClient(RoomInfos *rooms){
	int QueryRoom;
	char ch1;
	char name[30],surname[30];
	printf("Please enter the desired room : ");
	scanf("%d",&QueryRoom);
	if(rooms[QueryRoom-1].RoomState!=0){
		printf("Unfortunately,This room is full until %d:%d:%d",rooms[QueryRoom-1].departure.day,rooms[QueryRoom-1].departure.month,rooms[QueryRoom-1].departure.year);
		return;
	}
	rooms[QueryRoom-1].RoomNumber=QueryRoom;
	printf("\n\n------------------------------------\n\n");
	printf("Please enter the client's name : ");
	scanf("%s",&name);
	printf("\n\n------------------------------------\n\n");
	printf("Please enter the client's surname : ");
	scanf("%s",&surname);
	printf("\n\n------------------------------------\n\n");
	rooms[QueryRoom-1].client.ClientName=(char*)malloc(sizeof(char*)*strlen(name)+1);
	rooms[QueryRoom-1].client.ClientSurname=(char*)malloc(sizeof(char*)*strlen(surname)+1);
	strcpy(rooms[QueryRoom-1].client.ClientName,name);
	strcpy(rooms[QueryRoom-1].client.ClientSurname,surname);
	printf("\n\n------------------------------------\n\n");
	printf("Please enter the person number : ");
	scanf("%d",&rooms[QueryRoom-1].PersonNumber);
	printf("\n\n------------------------------------\n\n");
	printf("Please enter the date of entrance as(day:month:year) : ");
	scanf("%d:%d:%d",&rooms[QueryRoom-1].entrance.day,&rooms[QueryRoom-1].entrance.month,&rooms[QueryRoom-1].entrance.year);
	printf("\n\n------------------------------------\n\n");
	printf("Please enter the date of departure as(day:month:year) : ");
	scanf("%d:%d:%d",&rooms[QueryRoom-1].departure.day,&rooms[QueryRoom-1].departure.month,&rooms[QueryRoom-1].departure.year);
	printf("\n\n------------------------------------\n\n");
	rooms[QueryRoom-1].price=PriceCalc(rooms,QueryRoom);
	printf("\n\n------------------------------------\n\n");
	printf("Total Price : %.2lfTL",rooms[QueryRoom-1].price);
	printf("\n\n------------------------------------\n\n");
	printf("Do you want to continue (Y:N) : ");
	fflush(stdin);
	ch1=getchar();
	fflush(stdin);
	if(ch1=='N'){
		ClearRes(rooms,QueryRoom);
		return;
	}
	rooms[QueryRoom-1].RoomState=1;
}
void Record(RoomInfos *rooms){
	int i;
	FILE *file=fopen("HotelProject.txt","a");
	if(file==NULL){
		fprintf(stderr,"An Unexpected Error occured!\n");
		exit(1);
	}
	for(i=0;i<ROOM_NUMBER;i++){
		if(rooms[i].RoomState!=0){
			fprintf(file,"\n\n------------------------------------\n\n");
			fprintf(file,"%d.Room :",rooms[i].RoomNumber);
			fprintf(file,"\n\n------------------------------------\n\n");
			fprintf(file,"Client Name/Surname : %s %s",rooms[i].client.ClientName,rooms[i].client.ClientSurname);
			fprintf(file,"\n\n------------------------------------\n\n");
			fprintf(file,"Entrance : %d:%d:%d",rooms[i].entrance.day,rooms[i].entrance.month,rooms[i].entrance.year);
			fprintf(file,"\n\n------------------------------------\n\n");
			fprintf(file,"Depature : %d:%d:%d",rooms[i].departure.day,rooms[i].departure.month,rooms[i].departure.year);
			fprintf(file,"\n\n------------------------------------\n\n");
			fprintf(file,"Person Number : %d\n",rooms[i].PersonNumber);
			fprintf(file,"\n\n------------------------------------\n\n");
			fprintf(file,"Price : %.2lf\n",rooms[i].price);
			fprintf(file,"\n\n------------------------------------\n\n");
		}
	}
	fclose(file);
}
int main(){
	char ch;
	int password=123456,userpassword,roomnum;
	Badge badges;
	RoomInfos *RoomArray;
	RoomArray=(RoomInfos*)calloc(ROOM_NUMBER,sizeof(RoomInfos));
	printf("\t\t\tWelcome To Hotel Reservation System :\n");
	printf("Please enter the password : ");
	scanf("%d",&userpassword);
	if(userpassword==password){
		badges=staff;
	}else{
		badges=client;
	}
	do{
	   printf("\n\n------------------------------------\n\n1-New Client Entrance (PRESS E)\n\n------------------------------------\n\n2-Room Information Query (PRESS S)\n\n------------------------------------\n\n3-Show Full Rooms(PRESS F)\n\n------------------------------------\n\n4-Price Query (PRESS P)\n\n------------------------------------\n\n5-Room Exit (PRESS X)\n\n------------------------------------\n\n6-System Exit (PRESS Q)\n\n------------------------------------\n\n");
	   printf("Please enter a process : ");
	   fflush(stdin);
	   ch=getchar();
	   fflush(stdin);
	   switch(ch){
	   	case 'E':
	   	case 'e':
	   		if(badges==staff){
	   			AddClient(RoomArray);
			}else{
				printf("\n\n------------------------------------\n\n");
				printf("This process is for the staffs.Please choose another process!\n");
				printf("\n\n------------------------------------\n\n");
			}
	   		break;
	   	case 'S':
	   	case 's':
	   		printf("Please enter the room number to be searched : ");
	   		scanf("%d",&roomnum);
	   			Query(RoomArray,roomnum);
	   		break;
	   	case 'F':
	   	case 'f':
	   		if(badges==staff){
	   			ShowRooms(RoomArray);
			}else{
				printf("\n\n------------------------------------\n\n");
				printf("This process is for the staffs.Please choose another process!\n");
				printf("\n\n------------------------------------\n\n");
			}
	   		break;
	   	case 'P':
	   	case 'p':
	   		TotalPrice();
	   		break;
	   	case 'X':
	   	case 'x':
	   		if(badges==staff){
	   		printf("Please enter the room number to be exited : ");
	   		scanf("%d",&roomnum);
	   		ClearRes(RoomArray,roomnum);
	   		}else{
	   			printf("\n\n------------------------------------\n\n");
				printf("This process is for the staffs.Please choose another process!\n");
				printf("\n\n------------------------------------\n\n");
			}
	   		break;
	   	case 'Q':
	   	case 'q':
	   		if(badges==staff){
	   		Record(RoomArray);
	   		}else{
	   			printf("\n\n------------------------------------\n\n");
				printf("This process is for the staffs.Please choose another process!\n");
				printf("\n\n------------------------------------\n\n");
			}
	   		break;
	   	default:
		   break; 			
	   }
	}while(ch!='Q'||ch!='q');
}