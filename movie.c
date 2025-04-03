
/*****************Movie Ticket Booking Application*****************/
/* Creating Movie ticket  booking application using c with functions to perform operations like register ,login, booking ,view ticket ,cancel ticket ,update a movie 
using single linked list ,switch statements, if else conditions,  loops etc..*/
//header files 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Moviedetails {
    int sid;
    char stitle[50];
    char sshowtime[10];
    int sprice;
    float srating;
    int sseats[50];
    struct Moviedetails *next;
};
typedef struct Moviedetails *mv;

mv first = NULL;
mv last = NULL;
int global_movie_id;
int global_total_price;
char global_movie_title[50];
char admin_username[100];
char admin_password[100];

void login();
void moviesavailable();
void displaymovie();
void book_ticket();
void updatemovie();
void seats_available();
void searchmovie();
void cancel_ticket();
void make_apayment();
void addMovie(int id, char *title, char *showtime, int price, float rating);
void clean_movie();
int main() {
    long int number;
    char gmail[100];
    char password[100];

    printf("<<<<<<<<<<<<<<<<<BOOK MY CINEMA>>>>>>>>>>>>>\n");
    printf("*****************SIGN UP DETAILS**************\n");
    printf("Enter your mobile number: ");
    scanf("%ld", &number);
    printf("Enter the correct mail ID to get updates:");
    scanf("%s", gmail);
    printf("Enter the password:");
    getchar();
    scanf("%[^\n]s", password);
    printf("<---------------You Have Signed Up Successfully--------------->\n");
    printf("=========================User Login============================\n");
    login();
    addMovie(12, "DEWARA", "3:30 PM", 300, 9.5);
    addMovie(13, "KA", "11:30 AM", 250, 8.5);
    addMovie(14, "AAMRAN", "6:30 PM", 200, 8.0);
    printf("*BOOK MY CINEMA*\n");
    while (1) {
        printf("============================================================\n");
        printf("\t1. Movies Available\n\t2. Search Movie\n\t3. Display Movie\n\t4. Seats Available\n\t5. Book a Ticket\n\t6. Cancel a Ticket\n\t7. Update Movie Details\n\t8. Make Payment\n\t9. Exit\n");
        printf("=============================================================\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: 
                moviesavailable();
                break;
            case 2:
                searchmovie();
                break;
            case 3:
                displaymovie();
            case 4:
                seats_available();
                break;
            case 5:
                book_ticket();
                break;
            case 6:
                cancel_ticket();
                break;
            case 7:
                updatemovie();
                break;
            case 8:
                make_apayment();
                break;
            case 9:
                printf("Cleaning up memory and exiting...\n");
                clean_movie();
                printf("Thank you for using Book My Cinema! Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
void login() {
    char username[100];
    char password[100];
    int attempts = 3; 
    while (attempts > 0) {
        printf("Enter username: ");
        scanf(" %[^\n]", username); 
        printf("Enter password: ");
        scanf(" %[^\n]", password);
        if (strcmp(username, password) == 0)
        {
            printf("User login successful.\n");
            return; 
        } else 
        {
            attempts--; 
            if (attempts > 0) {
                printf("Login failed. You have %d attempt(s) remaining. Try again.\n", attempts);
            } else {
                printf("Login failed. No attempts remaining. Exiting...\n");
                exit(0); 
            }
        }
    }
}

void addMovie(int id, char *title, char *showtime, int price, float rating) {
    mv new = (mv)malloc(sizeof(struct Moviedetails));
    if (new == NULL) {
        perror("Allocation failed\n");
        exit(0);
    }

    new->sid = id;
    strcpy(new->stitle, title);
    strcpy(new->sshowtime, showtime);
    new->sprice = price;
    new->srating = rating;
    memset(new->sseats, 0, sizeof(new->sseats));
    new->next = NULL;

    if (first == NULL) {
        first = last = new;
    } else {
        last->next = new;
        last = new;
    }
}

void moviesavailable() {
    printf(".......Movies available for booking........\n");
    displaymovie();
}

void displaymovie() {
    mv temp = first;
    if (temp == NULL) {
        printf("No movies available\n");
        return;
    }

    int count = 1;
    printf("\n================== Movies Available ==================\n");

    while (temp != NULL) {
        printf("----------------------------------------------------\n");
        printf("| Movie #%d                                         |\n", count++);
        printf("----------------------------------------------------\n");
        printf("| ID        : %-4d                                  |\n", temp->sid);
        printf("| Title     : %-20s                   |\n", temp->stitle);
        printf("| Showtime  : %-10s                        |\n", temp->sshowtime);
        printf("| Price     : %-6d                                |\n", temp->sprice);
        printf("| Rating    : %-6.1f                             |\n", temp->srating);
        printf("----------------------------------------------------\n\n");
        temp = temp->next;
    }

    printf("====================================================\n");
}

void searchmovie() {
    int id;
    printf("Enter the movie ID to search: ");
    scanf("%d", &id);
    mv temp = first;
    int found = 0;

    while (temp != NULL) {
        if (id == temp->sid) {
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (found) {
        printf("Movie details:\n");
        printf("ID: %d\n", temp->sid);
        printf("Title: %s\n", temp->stitle);
        printf("Showtime: %s\n", temp->sshowtime);
        printf("Price: %d\n", temp->sprice);
    } else {
        printf("Movie ID does not exist.\n");
    }
}

void updatemovie() {
    char admin_username[50], admin_password[50];
    printf("**** Admin Details ****\n");
    printf("Enter the admin username: ");
    getchar();
    scanf("%[^\n]s", admin_username);
    getchar();
    printf("Enter the admin password: ");
    scanf("%[^\n]s", admin_password);

    if (strcmp(admin_username, admin_password) == 0) {
        printf("** Admin login successful **\n");
    } else {
        printf("Only admins can update movie details.\n");
        return;
    }
    
    int movieprice, id;
    char movietime[100];
    char moviename[50];
    printf("Enter the movie ID to update: ");
    scanf("%d", &id);

    mv temp = first;
    int found = 0;

    while (temp != NULL) {
        if (id == temp->sid) {
            found = 1;            
            printf("Enter the new movie price: ");
            scanf("%d", &movieprice);

            printf("Enter the new showtime: ");
            getchar();
            scanf("%[^\n]s", movietime);

            temp->sprice = movieprice;
            strncpy(temp->sshowtime, movietime, sizeof(temp->sshowtime) - 1);
            temp->sshowtime[sizeof(temp->sshowtime) - 1] = '\0';

            printf("Movie data updated successfully.\n");
            return;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Movie ID does not exist.\n");
    }
}
void seats_available() {
	int id;
	printf("Enter the movie ID to check seats:\n");
	scanf("%d", &id);
	mv temp = first;
	int flag = 0;
	while (temp != NULL) {
		if (id == temp->sid) {
			flag = 1;
			printf("Available seats are:\n");
			printf("\n");

			for (int row = 0; row < 5; row++) {
				for (int col = 0; col < 10; col++) {
					int seat_index = row * 10 + col;
					if (temp->sseats[seat_index] == 0) {
						printf("  A ");  
					} else {
						printf("  X ");  
					}
				}
				printf("\n"); 
			}
			printf("\n");
			break;
		}
		temp = temp->next;
	}

	if (flag == 0) {
		printf("Movie ID does not exist.\n");
	}
}

void book_ticket() {
	int id, num_seats;
	printf("Enter the movie ID to book tickets:\n");
	scanf("%d", &id);
	mv temp = first;
	int flag = 0;
	while (temp != NULL) {
		if (id == temp->sid) {
			flag = 1;
			printf("Enter the number of seats to book: ");
			scanf("%d", &num_seats);

			if (num_seats < 1 || num_seats > 50) {
				printf("Invalid number of seats. Please choose between 1 and 50.\n");
				return;
			}
			int seats[num_seats];
			printf("Enter the seat numbers to book (1-50):\n");
			for (int i = 0; i < num_seats; i++) {
				scanf("%d", &seats[i]);
				if (seats[i] < 1 || seats[i] > 50) {
					printf("Invalid seat number. Please choose between 1 and 50.\n");
					return;
				}
				if (temp->sseats[seats[i] - 1] == 1) {
					printf("Seat number %d is already booked.\n", seats[i]);
					return;
				}
				temp->sseats[seats[i] - 1] = 1;
			}
			global_movie_id = temp->sid;
			strcpy(global_movie_title, temp->stitle);
			global_total_price = num_seats * temp->sprice;
			make_apayment();
			printf("Tickets booked successfully!\n");
			break;
		}
		temp = temp->next;
	}

	if (flag == 0) {
		printf("Movie ID does not exist.\n");
	}
}
void cancel_ticket() {
	int id;
	printf("Enter the movie ID to cancel tickets:\n");
	scanf("%d", &id);
	mv temp = first;
	int flag = 0;
	while (temp != NULL) {
		if (id == temp->sid) {
			flag = 1;
			int num_seats;
			printf("Enter the number of seats to cancel:\n");
			scanf("%d", &num_seats);

			if (num_seats < 1 || num_seats > 50) {
				printf("Invalid number of seats. Please choose between 1 and 50.\n");
				return;
			}
			int seats[num_seats];
			printf("Enter the seat numbers to cancel (1-50):\n");
			for (int i = 0; i < num_seats; i++) {
				scanf("%d", &seats[i]);
				if (seats[i] < 1 || seats[i] > 50) {
					printf("Invalid seat number. Please choose between 1 and 50.\n");
					return;
				}
				if (temp->sseats[seats[i] - 1] == 0) {
					printf("Seat number %d is not booked.\n", seats[i]);
					return;
				}
				temp->sseats[seats[i] - 1] = 0;
			}
			printf("Tickets canceled successfully!\n");
			perror("Your money will be refundded within 24 hrs on your bank account\n");
			break;
		}
		temp = temp->next;
	}
	if (flag == 0) {
		printf("Movie ID does not exist.\n");
	}
}
void make_apayment() {
	int payment_method;
	char card_number[16];
	int cvv;
	char wallet[20];
	printf("\nTotal amount to pay: %d\n", global_total_price);
	printf("Choose Payment Method:\n");
	printf("1. Credit Card\n");
	printf("2. Debit Card\n");
	printf("3. Wallet\n");
	printf("Enter your choice: ");
	scanf("%d", &payment_method);
	switch (payment_method) {
	case 1:
	case 2:
		printf("Enter Card Number: ");
		scanf("%s", card_number);
		printf("Enter CVV: ");
		scanf("%d", &cvv);
		printf("Payment of %d successful for movie '%s'.\n", global_total_price, global_movie_title);
		break;
	case 3:
		printf("Enter Wallet Name (e.g., Paytm,phonepay): ");
		scanf("%s", wallet);
		printf("Payment of %d successful through %s for movie '%s'.\n", global_total_price, wallet, global_movie_title);
		break;
	default:
		printf("Invalid Payment Method.\n");
		return;
	}
	printf("Thank you for your payment! Enjoy the movie.\n");
}
void clean_movie() {
    mv temp;
    while (first != NULL) {
        temp = first;
        first = first->next;
        free(temp);
    }
    last = NULL;
    printf("All movie data has been cleaned up.\n");
}