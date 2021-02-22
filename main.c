#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#define ENTER 13
#define TAB 9
#define BKSP 8
#define SPACE 32
#define A 1  //Arrival Constant
#define D 2  // Departure Constant

struct info
{
    char schedule[10];
    char city[15];
    char airline[30];
    char flight[10];
    char terminal[5];
    char status[15];
    struct info *next;
};
typedef struct info adst;//arrival departure schedule type

struct login
{
    char username[20];
    char password[20];
};

adst *a_list = NULL;
adst *d_list = NULL;
short int l=0,h=1;

void welcome();
void decoration();
void line();
void arrival_data();
void departure_data();
void storeData();
void findFlight();
void main_menu();
void ad_submenu();
void admin_menu();
void operations();
void go_back();
void login();
void startDelete();
void second_line();
short int do_more();
void add();
void getInfo();
void edit();
void editMenu();
void singleEdit();
void del();
void searchNdel();
void selectNdel();
void searchAgain();
void displayData();
short int numDisplay();

int main()
{
    arrival_data();
    departure_data();
    main_menu();
    return 0;
}

void arrival_data()
{
    FILE *afp;
    adst data;
    afp = fopen("Arrivals.txt","r");
    fseek(afp,202,SEEK_SET);
    if(afp!=NULL)
    {
        while(fscanf(afp,"%s %s %s %s %s %s",data.schedule,data.city,data.airline,data.flight,data.terminal,data.status)!=EOF)
        {
            storeData(data,A);
        }
    }
    else
    {
        printf("\nDatabase Error!\n");
    }
    fclose(afp);
    return;
}

void departure_data()
{
    FILE *dfp;
    adst data;
    dfp = fopen("Departures.txt","r");
    fseek(dfp,202,SEEK_SET);
    if(dfp!=NULL)
    {
        while(fscanf(dfp,"%s %s %s %s %s %s",data.schedule,data.city,data.airline,data.flight,data.terminal,data.status)!=EOF)
        {
            storeData(data,D);
        }
    }
    else
    {
        printf("Database Error!\n");
    }
    fclose(dfp);
    return;
}

void storeData(adst data,int p) // collects data from arrival_data or departure_data
{
    adst *temp,*temp2;
    temp = (adst *)malloc(sizeof(adst)); // allocating memory to store data of the file
    strcpy(temp->schedule,data.schedule);
    strcpy(temp->city,data.city);
    strcpy(temp->airline,data.airline);
    strcpy(temp->flight,data.flight);
    strcpy(temp->terminal,data.terminal);
    strcpy(temp->status,data.status);
    temp->next = NULL;
    if(p==A) // p==A or D where A and D are constants value respectively 0 and 1 decides the list to be arrival or departure
    {
        if(a_list==NULL)
        {
            a_list = temp; //a_list means arrivals list
            return;
        }
        temp2 = a_list; // temp2 is used so that, program doesn't loose the address of first node
    }
    else if(p==D)
    {
        if(d_list==NULL)
        {
            d_list = temp; //d_list means departure list
            return;
        }
        temp2 = d_list; // temp2 is used so that,, program doesn't loose the address of first node
    }
    while(temp2->next!=NULL)
    {
        temp2 = temp2->next; // Finds the last node of the list
    }
    temp2->next = temp; // After finding the last node then insert new data bearing temp node
    return;
}

void findFlight(int p)
{
    char str[30];
    short int i = 0,k=0;
    adst *temp;
    adst data;
    if(p==A) // p==A or D where A and D are constants value respectively 0 and 1 decides the list to be arrival or departure
        temp = a_list;
    else if(p==D)
        temp = d_list;
    printf("\tEnter Flight Number or City or Airline: ");
    scanf("%s",str); // Collects Flight number or City or Airline from the user to search
    system("cls");
    if(p==A) // p==A or D where A and D are constants value respectively 0 and 1 decides the list to be arrival or departure
        printf("\n\tResults: In Arrival List                                                       Date: 08-04-2017,Saturday\n");
    else if(p==D)
        printf("\n\tResults: In Departure List                                                     Date: 08-04-2017,Saturday\n");
    decoration(p);

    while(temp!=NULL) // Searching till the last node to find multiple data with same information
    {
        if((strcmp(temp->flight,str)==0) || (strcmp(temp->airline,str)==0) || (strcmp(temp->city,str)==0)) // Comparing user input with the list data.
        {
            ++k;
            printf("\t| %-10s | %-15s | %-25s | %-10s | %-10s | %-15s |\n",temp->schedule,temp->city,temp->airline,temp->flight,temp->terminal,temp->status); //If found then shows data
        }
        else
        {
            for(i=0; str[i]!='\0'; i++) // Convert uppercase to lowercase to make search better
            {
                str[i] = tolower(str[i]);
                data.airline[i] = tolower(temp->airline[i]);
                data.city[i] = tolower(temp->city[i]);
                data.flight[i] = tolower(temp->flight[i]);
            }
            str[i]=data.airline[i]=data.city[i]=data.flight[i]='\0';
            if((strcmp(data.flight,str)==0) || (strcmp(data.airline,str)==0) || (strcmp(data.city,str)==0))// Comparing user input with the list data.
            {
                ++k;
                printf("\t| %-10s | %-15s | %-25s | %-10s | %-10s | %-15s |\n",temp->schedule,temp->city,temp->airline,temp->flight,temp->terminal,temp->status);
            }
        }
        temp = temp->next;
    }
    if(k==0)printf("\t| Not Found.                                                                                           |\n"); // If not found it will show not found
    line();
    return;
}
void getInfo(adst *temp)
{
    adst data;
    printf("\t  Enter Time: ");
    scanf("%s",data.schedule);
    printf("\t  Enter City: ");
    scanf("%s",data.city);
    printf("\t  Enter Airline: ");
    scanf("%s",data.airline);
    printf("\t  Enter Flight Number: ");
    scanf("%s",data.flight);
    printf("\t  Enter Terminal: ");
    scanf("%s",data.terminal);
    printf("\t  Enter status: ");
    scanf("%s",data.status);
    strcpy(temp->schedule,data.schedule);
    strcpy(temp->city,data.city);
    strcpy(temp->airline,data.airline);
    strcpy(temp->flight,data.flight);
    strcpy(temp->terminal,data.terminal);
    strcpy(temp->status,data.status);
    return;
}

void add(int p)  //Add schedule in the list
{
    adst *temp;
    short int s;
    temp = (adst *)malloc(sizeof(adst)); //allocating memory
    system("cls");
    printf("\n\tEnter The Following Information to Add:\n\n");
    getInfo(temp); // will go to this function to collect information to add
    system("cls");
    if(p==A)
    {
        temp->next = a_list;
        a_list = temp;
        displayData(p);
        printf("\tSuccessfully Added in Arrival List.\n\n");
    }
    else if(p==D)
    {
        temp->next = d_list;
        d_list = temp;
        displayData(p);
        printf("\tSuccessfully Added in Departure List.\n\n");
    }
    s = do_more(1);
    if(s==1)add(p);
    return;
}

void edit(int p)
{
    short int n;
    char str[30];
    adst *temp;
    if(p==A)  // p==A or D where A and D are constants value respectively 0 and 1 decides the list to be arrival or departure
        temp = a_list;
    else if(p==D)
        temp = d_list;
    if(temp==NULL){ // If temp is NULL then this function will show no data so go back or exit
        system("cls");
        displayData(p);
        go_back();
        return;
    }
    system("cls");
    displayData(p);
    printf("\n\n\tEnter Flight Number: ");
    scanf("%s",str);
    while(strcmp(temp->flight,str)!=0) // File searching condition
    {
        temp = temp->next;
        if(temp->next==NULL)break; // If data not found it will break from the loop
    }
    if(strcmp(temp->flight,str)==0) // If data found then
    {
        system("cls");
        printf("\n\tFound:\n");
        decoration(p);
        printf("\t| %-10s | %-15s | %-25s | %-10s | %-10s | %-15s |\n",temp->schedule,temp->city,temp->airline,temp->flight,temp->terminal,temp->status);
        line();
        editMenu(p,temp); // Will go edit menu and ask user to edit
        if(h==2){
            h = 1;
            return;
        }
        system("cls");
        displayData(p);
        printf("\tSuccessfully Edited\n\n");
        n = do_more(2);
        if(n==2)edit(p);
        }
    else
    {
        searchAgain(&n);
        if(n==1)edit(p);
    }
    return;
}

void editMenu(int p,adst *temp)
{
    short int n;
    printf("\n\t  [1] Edit Time\n\t  [2] Edit City\n\t  [3] Edit Airline\n\t  [4] Edit Flight Number\n\t  [5] Edit Terminal\n\t  [6] Edit Status\n\t  [7] Edit All Data Together\n\t  [8] Go Back\n\t  [0] Exit\n\n\tEnter Your Choice: ");
    scanf("%hi",&n);
    switch(n)
    {
    case 1:
        singleEdit(temp,n);
        break;
    case 2:
        singleEdit(temp,n);
        break;
    case 3:
        singleEdit(temp,n);
        break;
    case 4:
        singleEdit(temp,n);
        break;
    case 5:
        singleEdit(temp,n);
        break;
    case 6:
        singleEdit(temp,n);
        break;
    case 7:
        printf("\n\tEnter Following Information to edit: \n");
        getInfo(temp);
        return;
    case 8:
        h = 2;
        break;
    case 0:
        exit(0);
        break;
    default:
        printf("\n\tWrong Keyword!\n");
        exit(0);
        break;
    }
    return;
}
void singleEdit(adst *temp,int n)
{
    char str[30];
    if(n==1)
    {
        printf("\t  Enter Schedule: ");
        scanf("%s",str);
        strcpy(temp->schedule,str);
    }
    else if(n==2)
    {
        printf("\t  Enter City: ");
        scanf("%s",str);
        strcpy(temp->city,str);
    }
    else if(n==3)
    {
        printf("\t  Enter Airline: ");
        scanf("%s",str);
        strcpy(temp->airline,str);
    }
    else if(n==4)
    {
        printf("\t  Enter Flight Number: ");
        scanf("%s",str);
        strcpy(temp->flight,str);
    }
    else if(n==5)
    {
        printf("\t  Enter Terminal: ");
        scanf("%s",str);
        strcpy(temp->terminal,str);
    }
    else if(n==6)
    {
        printf("\t  Enter Status: ");
        scanf("%s",str);
        strcpy(temp->status,str);
    }
    return;
}

void del(int p)
{
    adst *temp;
    short int n;
    while(1){
            if(p==1)
        temp = a_list;
    else if(p==2)
        temp = d_list;
            system("cls");
            printf("\n\t\t\tDelete Menu:\n\t\t\t\t  [1] Search and Delete\n\t\t\t\t  [2] Select and Delete\n\t\t\t\t  [3] Go Back\n\t\t\t\t  [4] Home\n\t\t\t\t  [0] Exit\n\n\t\t\tEnter Your Choice: ");
            scanf("%hi",&n);
            system("cls");
            switch(n)
            {
            case 1:
                searchNdel(temp,p);
                break;
            case 2:
                selectNdel(temp,p);
                break;
            case 3:
                h = 1;
                return;
                break;
            case 4:
                h = 0;
                break;
            case 0:
                exit(0);
                break;
            default:
                printf("\n\tWrong Keyword!\n");
                exit(0);
                break;
            }
        if(h==0)break;
    }
    return;
}

void searchNdel(adst *temp,int p)
{
    short int n;
    char ch;
    adst *temp2;
    char str[30];
    if(temp==NULL){
        system("cls");
        displayData(p);
        go_back();
        return;
    }
    displayData(p);
    printf("\n\tEnter Flight Number: ");
    scanf("%s",str);
    system("cls");
    if(strcmp(temp->flight,str)==0) // To delete first schedule from the list
    {
        printf("\n\tFound:\n");
        decoration(p);
        printf("\t| %-10s | %-15s | %-25s | %-10s | %-10s | %-15s |\n",temp->schedule,temp->city,temp->airline,temp->flight,temp->terminal,temp->status);
        line();
        printf("\n\tAre you sure you want to delete? Y/N\n\n");
        ch = getch();
            if(ch=='y' || ch=='Y')
            {
                temp2 = temp;
                if(p==A)
                    a_list = temp->next;
                else if(p==D)
                    d_list = temp->next;
                free(temp2);
                system("cls");
                displayData(p);
                printf("\n\tSuccessfully Deleted.\n");
                n = do_more(3);
                if(n==3 && p==A)searchNdel(a_list,p);
                else if(n==3 && p==D)searchNdel(d_list,p);
                return;
            }else
                return;
        }else{        // If data is absent in firs node then
            while(strcmp(temp->next->flight,str)!=0)
            {
                if(temp->next->next==NULL)break;
                temp = temp->next;
            }

            if(strcmp(temp->next->flight,str)==0)
            {
                printf("\n\tFound:\n");
                decoration(p);
                printf("\t| %-10s | %-15s | %-25s | %-10s | %-10s | %-15s |\n",temp->next->schedule,temp->next->city,temp->next->airline,temp->next->flight,temp->next->terminal,temp->next->status);
                line();
                printf("\n\tAre you sure you want to delete? Y/N\n\n");
                ch = getch();
                if(ch=='y' || ch=='Y')
                {
                    temp2 = temp->next;
                    temp->next = temp2->next;
                    free(temp2);
                    system("cls");
                    displayData(p);
                    printf("\n\tSuccessfully Deleted.\n");
                    n = do_more(3);
                    if(n==3 && p==A)searchNdel(a_list,p);
                    else if(n==3 && p==D)searchNdel(d_list,p);
                    return;
                }else{
                    return;
                }
            }else{
                searchAgain(&n);
                if(n==1 && p==A)
                    searchNdel(a_list,p);
                else if(n==1 && p==D)
                    searchNdel(d_list,p);
            }
        }
}

void second_line(){
    printf("\t-----------------------------------------------------------------------------------------------------------\n");
}

short int numDisplay(int p)
{
    adst *temp;
    short int i=1;
    if(p==A)
        temp = a_list;
    else if(p==D)
        temp = d_list;
    printf("\n");
    second_line();
    printf("\t|  | %-10s | %-15s | %-25s | %-10s | %-10s | %-15s |\n","SCHEDULED","FROM","AIRLINE","FLIGHT","TERMINAL","STATUS");
    second_line();
    if(temp == NULL)
        printf("\t|                                       ...List is EMPTY...                                              |\n");
    while(temp!=NULL)
    {
        printf("\t|%2d| %-10s | %-15s | %-25s | %-10s | %-10s | %-15s |\n",i++,temp->schedule,temp->city,temp->airline,temp->flight,temp->terminal,temp->status);
        temp = temp->next;
    }
    second_line();
    return i;
}
void startDelete(){
    short int n;
    printf("\n\t  [1] Start Deleting\n\t  [2] Go Back\n\n\tEnter Your Choice: ");
    scanf("%hi",&n);
    switch(n){
    case 1:
        h = 2;
        break;
    case 2:
        h = 1;
        return;
        break;
    case 0:
        exit(0);
        break;
    default:
        printf("\n\tWrong Keyword!\n");
        exit(0);
        break;
    }
    system("cls");
}
void selectNdel(adst *temp,int p)
{
    short int pos,i,s;
    adst *temp2;
    numDisplay(p);
    if(temp==NULL){
             system("cls");
        displayData(p);
        go_back();
        return;
    }
    if(h!=2)
    startDelete();
    if(h!=2)return;
    system("cls");
    s = numDisplay(p);
    printf("\n\tEnter Position to Delete: ");
    scanf("%hi",&pos);
    if(pos>=s || pos<1)
    {
        printf("\n\tWrong Keyword!\n");
        exit(0);
    }
    if(pos==1)
    {
        temp2 = temp;
        if(p==A)
            a_list = temp->next;
        else if(p==D)
            d_list = temp->next;
        free(temp2);
        system("cls");
        displayData(p);
        printf("\n\tSuccessfully Deleted.\n");
    }else{
    for(i=1; i<pos-1; i++)
        temp = temp->next;
    temp2 = temp->next;
    temp->next = temp2->next;
    free(temp2);
    system("cls");
        displayData(p);
        printf("\n\tSuccessfully Deleted.\n");
    }
    i = do_more(3);
    if(i==3 && p==A)selectNdel(a_list,p);
    else if(i==3 && p==D)selectNdel(d_list,p);
    return;
}
short int do_more(int n)
{
    short int t;
    if(n==1)
        printf("\t  [1] Add More\n\t  [2] Go Back\n\t  [3] Home\n\t  [0] Exit\n\n\t Enter Your Choice: ");
    else if(n==2)
        printf("\t  [1] Edit More\n\t  [2] Go Back\n\t  [3] Home\n\t  [0] Exit\n\n\t Enter Your Choice: ");
    else if(n==3)
        printf("\t  [1] Delete More\n\t  [2] Go Back\n\t  [3] Home\n\t  [0] Exit\n\n\t Enter Your Choice: ");

    scanf("%hi",&t);
    system("cls");
    switch(t)
    {
    case 1:
        return n;
        break;
    case 2:
        h = 1;
        return 0;
        break;
    case 3:
        h = 0;
        break;
    case 0:
        exit(0);
        break;
    default:
        printf("\n\tWrong Keyword!\n");
        exit(0);
        break;
    }
    return 0;
}

void searchAgain(short int *g){
    short int n;
    printf("\n\tNot Found!\n"); // If not found then
        printf("\t  [1] Search Again\n\t  [2] Go Back\n\t  [0] Exit\n\n\tEnter Your Choice: ");
        scanf("%hi",&n);
        switch(n)
        {
        case 1:
            *g = n;
            break;
        case 2:
            h = 1;
            return;
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("\n\tWrong Keyword!\n");
            exit(0);
            break;
        }
        system("cls");
}

void operations(int p)
{
    short int n;
    system("cls");
    while(1){
        system("cls");
        printf("\n\n\t\t\tAdmin Operations:\n\t\t\t\t  [1] Add Schedule\n\t\t\t\t  [2] Edit Schedule\n\t\t\t\t  [3] Delete Schedule\n\t\t\t\t  [4] Go Back\n\t\t\t\t  [5] Home\n\t\t\t\t  [0] Exit\n\n\t\t\tEnter Your Choice:  ");
        scanf("%hi",&n);
        switch(n)
        {
        case 1:
            add(p);
            break;
        case 2:
            edit(p);
            break;
        case 3:
            del(p);
            break;
        case 4:
            h=1;
            return;
            break;
        case 5:
            h = 0;
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("\n\t\t\tWrong Keyword!\n");
            exit(0);
            break;
        }
        if(h==0)break;
    }
    return;
}

void admin_menu()
{
    short int p;
    l++;
    while(1){
        system("cls");
        printf("\n\n\t\t\tAdmin Menu:\n\t\t\t\t[1] Arrival Operations\n\t\t\t\t[2] Departure Operations\n\t\t\t\t[3] Go Back\n\t\t\t\t[0] Exit\n\n\t\t\tEnter Your Choice: ");
        scanf("%hi",&p);
        switch(p)
        {
        case 1:
            operations(A);
            break;
        case 2:
            operations(D);
            break;
        case 3:
            h=1;
            return;
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("\n\t\t\tWrong Keyword!\n");
            exit(0);
            break;
        }
        if(h==0)break;
    }
    return;
}

void login()
{
    struct login data;
    char ch;
    short int j=0;
    char up[2][20];
    FILE *fp;
    if(l==0)
    {
        fp = fopen("login.txt","r");
        system("cls");
        while(fscanf(fp,"%*s %s",data.username)!=EOF) //Here "use" is using to collect data from file
        {
            strcpy(up[j],data.username);
            j++;
        }
        j = 0;
        fclose(fp);
        printf("\n\n\n\t\t\t\tAdmin Login\n\n");
        printf("\t\t\t\tEnter Username: ");
        scanf("%s",data.username);
        printf("\t\t\t\tEnter Password: ");
        while(1)
        {
            ch = getch();
            if(ch==ENTER)
            {
                data.password[j]='\0';
                break;
            }
            else if(ch==BKSP)
            {
                if(j>0)
                {
                    j--;
                    printf("\b \b");
                }
            }
            else if(ch==SPACE || ch == TAB)
            {
                continue;
            }
            else
            {
                data.password[j++] = ch;
                printf("*");
            }

        }
        if(strcmp(up[0],data.username)==0 && strcmp(up[1],data.password)==0)
        {
            admin_menu();
        }
        else
        {
            printf("\n\n\t\t\t\tAuthentication Failed!\n\n");
            printf("\t\t\t\t  [1] Go Back\n\t\t\t\t\  [2] Try Again\n\t\t\t\t  [0] Exit\n\n\t\t\t\tEnter Your Choice: ");
            scanf("%hi",&j);
            switch(j)
            {
            case 1:
                h = 1;
                return;
                break;
            case 2:
                system("cls");
                login();
                break;
            case 0:
                exit(0);
                break;
            default:
                printf("\n        Wrong Keyword!\n");
                exit(0);
                break;
            }
        }
    }
    else
    {
        admin_menu();
    }
    return;
}

void main_menu()
{
    short int n=0;
    while(1){
        system("cls");
        if(n==0)
             welcome();
        printf("\n\n\t\t\tMAIN MENU:\n\t\t\t\t[1] Arrivals\n\t\t\t\t[2] Departures\n\t\t\t\t[3] Admin Panel\n\t\t\t\t[0] Exit\n\n\t\t\tEnter Your Choice: ");
        scanf("%hi",&n);
        switch(n)
        {
        case 1:
            ad_submenu(A);
            break;
        case 2:
             ad_submenu(D);
            break;
        case 3:
            login();
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("\n\t\t\tWrong Keyword!\n");
            exit(0);
            break;
        }
        h = 1;
    }
    return;
}

void welcome(){
    printf("\n");
    printf("                                                               _  _\n");Sleep(300);
    printf("                                                              \\ `/ |\n");Sleep(300);
    printf("                        \\------------------------------\\       \\__`!\n");Sleep(300);
    printf("                         \\                              \\      / ,' `-.__________________\n");Sleep(300);
    printf("                          \\                              \\    '-'\\_____                LI`-.\n");Sleep(300);
    printf("                           >     FLIGHT SCHEDULE APP      >------<____()-=O=O=O=O=O=[]====--)\n");Sleep(300);
    printf("                          /                              /        `.___ ,-----,_______...-'\n");Sleep(300);
    printf("                         /                              /              /    .'\n");Sleep(300);
    printf("                        /------------------------------/              /   .'\n");Sleep(300);
    printf("                                                                     /  .'\n");Sleep(300);
    printf("                                                                     `-'\n\n");Sleep(300);
}

void decoration(int p)
{
    printf("\t--------------------------------------------------------------------------------------------------------\n");
    if(p==A)
    printf("\t| %-10s | %-15s | %-25s | %-10s | %-10s | %-15s |\n","SCHEDULED","FROM","AIRLINE","FLIGHT","TERMINAL","STATUS");
    else if(p==D)
    printf("\t| %-10s | %-15s | %-25s | %-10s | %-10s | %-15s |\n","SCHEDULED","TO","AIRLINE","FLIGHT","TERMINAL","STATUS");
    printf("\t--------------------------------------------------------------------------------------------------------\n");
    return;
}
void line()
{
    printf("\t--------------------------------------------------------------------------------------------------------\n");
    return;
}

void go_back(){
    short int n;
    printf("\t  [1] Go Back\n\t  [2] Home\n\t  [0] Exit\n\n\tEnter Your Choice: ");
    scanf("%hi",&n);
    switch(n)
    {
    case 1:
        h = 1;
        return;
        break;
    case 2:
        h = 0;
        break;
    case 0:
        exit(0);
        break;
    default:
        printf("\n\tWrong Keyword!\n");
        exit(0);
        break;
    }
    return;
}

void ad_submenu(int p)
{
    short int n;
    while(1){
        system("cls");
        displayData(p);
        if(p==A)
        printf("\n\t  [1] Find Arrival Flight\n\t  [2] Go Back\n\t  [0] Exit\n\n\tEnter Your Choice: ");
        else if(p==D)
        printf("\n\t  [1] Find Departure Flight\n\t  [2] Go Back\n\t  [0] Exit\n\n\tEnter Your Choice: ");
        scanf("%hi",&n);
        switch(n)
        {
        case 1:
            findFlight(p);
            go_back();
            break;
        case 2:
            h = 1;
            return;
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("\n\tWrong Keyword!\n");
            exit(0);
            break;
        }
        if(h==0)break;
    }
    return;
}
void displayData(int p)
{
    adst *temp;
    char str[100];
    FILE *fp,*fp2;   //FILE pointer
    fp = fopen("temp/process.txt","w");
    if(p==A)
    {
        temp = a_list;
        printf("\n\tCurrently Showing Todays Arrival List:                                         Date: 08-04-2017,Saturday\n");
    }
    else if(p==D)
    {
        temp = d_list;
        printf("\n\tCurrently Showing Todays Departure List:                                       Date: 08-04-2017,Saturday\n");
    }
    decoration(p);
    if(temp==NULL)
        printf("\t|                                       ...List is EMPTY...                                            |\n");
    while(temp!=NULL)
    {
        printf("\t| %-10s | %-15s | %-25s | %-10s | %-10s | %-15s |\n",temp->schedule,temp->city,temp->airline,temp->flight,temp->terminal,temp->status);
        fprintf(fp,"%-10s   %-15s   %-25s   %-10s   %-10s   %-15s\n",temp->schedule,temp->city,temp->airline,temp->flight,temp->terminal,temp->status);
        temp = temp->next;
    }
    line();
    fclose(fp);
    fp = fopen("temp/process2.txt","w");
    if(p==A)
    fprintf(fp,"%-10s   %-15s   %-25s   %-10s   %-10s   %-15s\n","SCHEDULED","FROM","AIRLINE","FLIGHT","TERMINAL","STATUS");
    else if(p==D)
    fprintf(fp,"%-10s   %-15s   %-25s   %-10s   %-10s   %-15s\n","SCHEDULED","TO","AIRLINE","FLIGHT","TERMINAL","STATUS");
    fprintf(fp,"----------   ---------------   -------------------------   ----------   ----------   ---------------\n");
    fclose(fp);

    fp = fopen("temp/process.txt","r");
    fp2 = fopen("temp/process2.txt","a");
    while(fgets(str,100,fp)){
         fprintf(fp2,"%s",str);
    }
    fclose(fp);
    fclose(fp2);
    fp = fopen("temp/process2.txt","r");
    if(p==1)
        fp2 = fopen("Arrivals.txt","w");
    else if(p==2)
        fp2 = fopen("Departures.txt","w");
    while(fgets(str,100,fp)){
        fprintf(fp2,"%s",str);
    }
    fclose(fp);
    fclose(fp2);
    return;
}

