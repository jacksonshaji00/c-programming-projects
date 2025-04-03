#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct moviedetails{
    int id;
    char title[50];
    char showtime[50];
    int price;
    float rating;
    int seats[50];
    struct moviesdetails *next;
};

struct moviedetails *first=NULL;
struct moviedetails *last=NULL;
struct moviedetails *newnode;

char admin_username[100];
char admin_password[100];

char sign_password[100];
char sign_username[100];
void login();

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}


int main()
{
    long int number;
    char gmail[50];

    printf("<<<<<<<<<<<<<<<<<BOOK MY CINEMA>>>>>>>>>>>>>\n");
    printf("*****************SIGN UP DETAILS**************\n");
    printf("Enter your mobile number: ");
    scanf("%ld", &number);
    clearInputBuffer();

    printf("Enter the correct mail ID to get updates:");
    scanf("%s", gmail);
    clearInputBuffer();

    printf("enter the user name: ");
    scanf("%[^\n]s",sign_username);
    clearInputBuffer();

    printf("Enter the password:");
    scanf("%[^\n]s",sign_password);
    clearInputBuffer();

    printf("<---------------You Have Signed Up Successfully--------------->\n");
    printf("=========================User Login============================\n");
    login();
    addMovie(12,"KGF","3:30 pm",200,9.5);
    addMovie(13,"EMPURAN","3:30 pm",200,9.5);
    addMovie(13,"KGF2","3:30 pm",200,9.5);

}


void login()
{
    char username[100];
    char password[100];
    int attempts=3;

    while(attempts>0)
    {
        printf("enter username: ");
        scanf("%[^\n]s",username);
        clearInputBuffer();

        printf("enter password: ");
        scanf("%[^\n]s",password);
        clearInputBuffer();

        if(strcmp(username,sign_username)==0 && strcmp(password,sign_password)==0)
        {
            printf("..............user login sucessful..............\n");
            return;
        }
        else
        {
            attempts--;
            if(attempts>0)
            {
                printf("Login failed. You have %d attempt(s) remaining. Try again.\n", attempts);
            } else {
                printf("Login failed. No attempts remaining. Exiting...\n");
               exit(0); 
            }
        }
    }
}

void addMovie(int id, char title, char showtime, int price, float rating)
{
    
    newnode=(struct moviedetails *)malloc(sizeof(struct moviedetails));

    if(newnode==NULL)
    {
        perror("This not coorect way...");
    }
    newnode->id=id;
    strcpy(newnode->title,title);
    strcpy(newnode->showtime,showtime);
    newnode->price=price;
    newnode->rating=rating;
    memset(newnode->seats,0,sizeof(newnode->seats));
    newnode->next=NULL;

    if(first=NULL)
    {
        first=last=newnode;
    }
    else{
        last->next=newnode;
        last=newnode;
    }

}