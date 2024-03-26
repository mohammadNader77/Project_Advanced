#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>


typedef struct Passenger
{

    int StudentId;
    char Date[30];
    char Time[30];
    char from[30];
    char to[30];


    struct Passenger *next;
} Passenger;
 typedef struct Passenger* p,*pass;
Passenger *head_passenger=NULL, *current_passenger= NULL;

p* passlist=NULL;
typedef struct Busses
{

    int id;
    char date[30];
    char departure_time[50];
    char from[30];
    char to[30];
    int price_ticket;
    int capacity;

//    passList passenger;
    struct busses *next;
} Busses;

Busses *current_busses=NULL,*head_busses=NULL;


//PList *unmatches=NULL;

int main()
{




    char option [2];
    do
    {
        PrintMenue();


        printf("\n Enter the number of option \n");

        scanf("%s",option);


        if(strlen(option) > 1) // because the options have one character
            strcpy(option,"0") ;

        switch(atoi(option))  // switch to know what is the option
        {


        case 1:
            readInformationOFBusses();


            break;

        case 2:

            ReadPassengerInformation();


            display();
            break;
        case 3:

            break;

        case 4:

            //    deletepass();
            break;

        case 5:


            break;
        case 6:

            AddPassenger();
            display();
            break;
        case 7:

            deletepass();
            display();
            break;


        case 8:
            //deletepass1();


            break;
        case 9:
            return 0;
            break;
        }
    }
    while(atoi(option) != 8);

}
void PrintMenue()
{
    printf("\n--------------Menu---------------\n");
    printf("Select the number of the option that you want \n");
    printf("1. Load the bus information file \n");
    printf("2. Load the passenger information file \n");
    printf("3. Assign passengers and print assignment information of all busses \n");
    printf("4. Print a specific bus information along with its passengers information (names and IDs)  \n");
    printf("5. Print unmatched passengers \n");
    printf("6. Add new passenger \n");
    printf("7. Delete passenger \n");
    printf("8. Delete bus number \n");
    printf("9. Exit");

}

void readInformationOFBusses()
{

    FILE *file;
    file=fopen("busses.txt","r");
    if(file==NULL)
    {
        printf("Error opening file \n");

    }

    Busses pass[100];
    int read=0;
    int rec=0;

    do
    {
        read=fscanf(file,"%d#%d#%49[^#]#%29[^#]#%29[^#]#%d#%d\n",&pass[rec].id,&pass[rec].date,pass[rec].departure_time,pass[rec].from,pass[rec].to,&pass[rec].price_ticket,&pass[rec].capacity);
        if(read==7)
            rec++;
        if(read!=7&&!feof(file))
        {

            printf("file incorrect\n");
            return 1;
        }

    }
    while(!feof(file));
    fclose(file);
    printf("%15s%15s%15s%15s%15s%15s%15s\n","id","date","time","from","to","price","capacity");
    for(int i=0; i<rec; i++)
    {

        printf("%15d%15d%15s%15s%15s%15d%15d\n",pass[i].id,pass[i].date,pass[i].departure_time,pass[i].from,pass[i].to,pass[i].price_ticket,pass[i].capacity);
        printf("\n");
    }

}



void AddPassenger()
{

    Passenger p1,*node;
    printf("Enter the raveler ID(student ID)-->");
    scanf("%d",&p1.StudentId);
    printf("Enter the travelling date-->");
    scanf("%d",&p1.Date);
    printf("Enter the travelling time-->");
    scanf("%s",&p1.Time);
    printf("Enter from -->");
    scanf("%s",&p1.from);
    printf("Enter to-->");
    scanf("%s",&p1.to);

    node=(Passenger*)malloc(sizeof(Passenger));
    node->StudentId=p1.StudentId;
       strcpy(node->Date,p1.Date);

    strcpy(node->Time,p1.Time);
    strcpy(node->from,p1.from);
    strcpy(node->to,p1.to);
    node->next=NULL;

    if(head_passenger==NULL)
    {
        head_passenger=node;

    }
    else
    {
        current_passenger=head_passenger;
        while(current_passenger->next!=NULL)
            current_passenger=current_passenger->next;
        current_passenger->next=node;
    }
}


void deletepass()
{
    int id,found=0;
    printf("Enter the id ");
    scanf("%d",&id);
    current_passenger=head_passenger;
    if(current_passenger->StudentId==id)
    {
        head_passenger=current_passenger->next;
        free(current_passenger);
        found =1;

    }
    while(current_passenger->next!=NULL){
        Passenger *pass=current_passenger->next;
        if(pass->StudentId==id){
            current_passenger->next=pass->next;
            free(pass);
            found =1;
            break;
        }
        current_passenger=current_passenger->next;
    }

    if(found)
    {
        printf("sucss");
    }
    else
    {
        printf("error");
    }

}

void ReadPassengerInformation()
{
    head_passenger=NULL,current_passenger=NULL;

    FILE* in = fopen("passengers.txt","r");
    if(in==NULL)
        printf("error");
    Passenger p1,*node;
    while(fscanf(in,"%d#%d#%29[^#]#%29[^#]#%[^]\n",&p1.StudentId,&p1.Date,p1.Time,p1.from,p1.to!=EOF))  // if there is a line to scan..
    {
        node=(Passenger*)malloc(sizeof(Passenger));

        node->StudentId=p1.StudentId;
        strcpy(node->Date,p1.Date);

        strcpy(node->Time,p1.Time);
        strcpy(node->from,p1.from);
        strcpy(node->to,p1.to);

        node->next=NULL;

        if(head_passenger==NULL)
        {
            current_passenger=head_passenger=node;
        }
        else
        {
            current_passenger=current_passenger->next=node;


        }

    }

    fclose(in);
}

void display()
{
    printf("\n %15s%15s%15s%15s%15s%15s\n","id","date","time","from","to");
    for(current_passenger=head_passenger; current_passenger; current_passenger=current_passenger->next)
        printf("\n%15d%15d%15s%15s%15s%15d",current_passenger->StudentId,current_passenger->Date,current_passenger->Time,current_passenger->from,current_passenger->to);


}
/*
void display1(){
printf("\n%15s%15s%15s%15s%15s%15s%15s\n","id","date","time","from","to","price","capacity");
for(current_busses=head_busses;current_busses;current_busses=current_busses->next)
    printf("%15d%15d%15d%15d%15d%15d%15d\n",current_busses->id,current_busses->date,current_busses->departure_time,current_busses->from,current_busses->to,current_busses->price_ticket,current_busses->capacity);
}
*/
bool isEmpty(Passenger *p){

return p==NULL;
}

p newNode(int StudentId,char date[30],char Time[20] ,char from[30] ,char to[30]){

    p list=(p)malloc(sizeof(Passenger));
    list->StudentId=StudentId;
    strcpy(list->Date,date);
    strcpy(list->Time,Time);
    strcpy(list->from,from);
    strcpy(list->to,to);
    list->next=NULL;

    return list;
}
void insertPassengeratlist(int StudentId,char date[30],char Time[20] ,char from[30] ,char to[30],p*l){

if(isEmpty(*l)){
    (*l)=newNode( StudentId,date,Time ,from ,to);
}
else{
    p node=newNode( StudentId,date,Time ,from ,to);
    node->next=(*l);
    (*l)=node;
}




}
p* make(int size,p* l){
l=(p*)malloc(sizeof(p)*size);
for(int i=0;i<size;i++)
    l[i]=NULL;
    return l;

}

void ReadFilePassenger(){
   int size=0;
        char l[100];
    FILE *pass=fopen("passenger.txt","r");
    if(pass==NULL){
        printf("file does not exist");
    }

    else{

        while(fgets(l,100,pass)){
            size=size+1;
        }

    }
    fclose(pass);

    int *spilt="#";
    char edg=strtok(l,spilt);
    int f=0;

    int id=0;
    char date[20]="";
       char time="";
          char from="";
             char to="";
    while(edg!=NULL){

        if(f==0){
            id=(int)strtol(edg,NULL,20);
            f++;
        }
       else if(f==1){
        strcat(date,edg);
        f++;
       }
              else if(f==2){
        strcat(time,edg);
        f++;
       }
              else if(f==3){
        strcat(from,edg);
        f++;
       }
              else if(f==4){
        strcat(to,edg);
        f++;
       }
       edg=strtok(NULL,spilt);
    }

    insert(id,date,time,from,to,passlist);
}
