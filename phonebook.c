// @autor = Mehdi Talalha
// This is a phonebook with CLI that let the user add and remove adn edit and delet contacts
// my goal is get confortable with persestent Data

#include <stdio.h>

typedef struct
{
    char name[20];
    char number[20];
} phonebook;

void delete_contact();
void edit_contact();
void show_contact();
void add_contact(contacte *phonebook, int index);
int get_int(char *label);

int main(void)
{
    phonebook contacte[100];
    int index = 0;

    while (1)
    {
        FILE *data = fopen("phonebook.csv", "a+");

        if (data == NULL)
        {
            printf("invalide file\n");
        }

        printf("1. Add Contact\n");
        printf("2. Show Contacts\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("\n");
        
        int choice = get_int("Choice: \n");

        switch (choice)
        {
            case 1:
                add_contact(contacte, index);
                break;
            case 2:
                show_contact(contacte, index);
                break;
            case 3:
                edit_contact(contacte, index);
                break;
            case 4:
                delete_contact(contacte, index);
                break;
            case 5:
                printf("Exiting...");
                return 0;
        }
    }
}

void add_contact(contacte *phonebook, int index){
    
}

void show_contact(){
    
}

void edit_contact(){
    
}

void delete_contact(){
    
}

// to make the code readble
int get_int(char *label){
    int input;
    printf("%s", label);
    scanf("%d", &input);

    return input;
}