// @autor = Mehdi Talalha
// This is a phonebook with CLI that let the user add and remove adn edit and delet contacts
// my goal is get confortable with persestent Data

#include <stdio.h>
#include <string.h>
#define SIZE 100
#define MAX_LEN 100

typedef struct
{
    char name[20];
    char number[20];
} contacte;

void show_contact(FILE *data);
void add_contact(contacte *phonebook, FILE *data);
void delete_contact(FILE *data);

int main(void)
{
    contacte phonebook[100];
    int counter = sizeof(phonebook) / sizeof(phonebook[0]);

    while (1)
    {
        FILE *data = fopen("phonebook.csv", "a+");

        if (data == NULL)
        {
            printf("invalide file\n");
        }

        printf("1. Add Contact\n");
        printf("2. Show Contacts\n");
        printf("3. Delete Contact\n");
        printf("4. Exit\n");
        printf("\n");
        
        int choice;
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                add_contact(phonebook, data);
                break;
            case 2:
                show_contact(data);
                break;
            case 3:
                delete_contact(data);
                break;
            case 4:
                printf("Exiting...");
                return 0;
        }
    }
}

void add_contact(contacte *phonebook, FILE *data){

    int index = 0;

    printf("Name: ");
    scanf("%19s",phonebook[index].name);

    printf("Number: ");
    scanf("%19s", phonebook[index].number);   

    fprintf(data, "%s, %s\n", phonebook[index].name, phonebook[index].number);
    
    fclose(data);

    printf("\n");
    
}

void show_contact(FILE *data){
    printf("\n");

    char line[20];
    int index = 0;

    while (fgets(line, sizeof(line), data))
    {
        printf("%d. %s",index + 1, line);
        index++;
    }
    
    printf("\n");    
}

void delete_contact(FILE *data) {
    char line[SIZE][MAX_LEN];
    int index = 0;

    rewind(data);

    // Read all contacts
    while (fgets(line[index], MAX_LEN, data)) {
        printf("%d. %s", index + 1, line[index]);
        index++;
    }

    if (index == 0) {
        printf("No contacts to delete.\n");
        return;
    }

    int chose;
    printf("Choose contact to delete (1-%d): ", index);
    scanf("%d", &chose);

    if (chose < 1 || chose > index) {
        printf("Invalid choice!\n");
        return;
    }

    chose--; // 0-based;

    // Shift remaining contacts
    for (int i = chose; i < index - 1; i++) {
        strcpy(line[i], line[i + 1]);
    }
    index--;

    // Rewrite the file
    fclose(data);
    data = fopen("phonebook.csv", "w");
    if (!data) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < index; i++) {
        fputs(line[i], data);
    }

    fclose(data);
    printf("Contact deleted successfully!\n");
}

// offff tish project takes 3hours cuz of deleting contact and in the end i asked chatgpt.