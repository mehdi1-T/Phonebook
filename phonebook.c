#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


#define MAX_CONTACTS 100
#define MAX_LEN 50

// Function declarations
void Add_Contact(void);
void Show_Contact(void);
void Remove_Contact(void);
void Sort_Contacts(char names[][MAX_LEN], char numbers[][MAX_LEN], int count);
void lowercase(char *str);
char *get_string(const char *label);
int get_int(const char *label);

// Global arrays to hold contacts temporarily
char names[MAX_CONTACTS][MAX_LEN];
char numbers[MAX_CONTACTS][MAX_LEN];
int count = 0; // current number of contacts

int main(void) {
    while (1) {
        printf("\n");
        printf("___________________________\n");
        printf("|       PHONE BOOK         |\n");
        printf("|1. Add contact            |\n");
        printf("|2. Show contacts          |\n");
        printf("|3. Remove contact         |\n");
        printf("|4. Exit                   |\n");
        printf("___________________________|\n\n");

        int choice = get_int("Choice: ");

        switch (choice) {
            case 1:
                Add_Contact();
                break;
            case 2:
                Show_Contact();
                break;
            case 3:
                Remove_Contact();
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

// ---------------------- ADD CONTACT ----------------------
void Add_Contact(void) {
    if (count >= MAX_CONTACTS) {
        printf("Phonebook is full!\n");
        return;
    }

    char *name = get_string("Name: ");
    lowercase(name);
    char *number = get_string("Number: ");

    // Save to arrays
    strcpy(names[count], name);
    strcpy(numbers[count], number);
    count++;

    // Append to CSV
    FILE *file = fopen("phonebook.csv", "a");
    if (!file) {
        printf("File error!\n");
        free(name);
        free(number);
        return;
    }
    fprintf(file, "%s,%s\n", name, number);
    fclose(file);

    free(name);
    free(number);

    printf("Contact added!\n");
}

// ---------------------- SHOW CONTACTS ----------------------
void Show_Contact(void) {
    // Read all contacts from CSV first
    FILE *file = fopen("phonebook.csv", "r");
    if (!file) {
        printf("No contacts found!\n");
        return;
    }

    count = 0;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // remove newline
        char *name = strtok(line, ",");
        char *num = strtok(NULL, ",");
        if (name && num) {
            strcpy(names[count], name);
            strcpy(numbers[count], num);
            count++;
        }
    }
    fclose(file);

    if (count == 0) {
        printf("No contacts to show!\n");
        return;
    }

    // Sort contacts alphabetically
    Sort_Contacts(names, numbers, count);

    // Print names
    printf("====== CONTACT NAMES ======\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, names[i]);
    }

    // Let user pick a contact to see the number
    int choice = get_int("Open contact (number): ");
    if (choice < 1 || choice > count) {
        printf("Invalid contact number!\n");
        return;
    }

    printf("%s's number: %s\n", names[choice - 1], numbers[choice - 1]);
    printf("===========================\n");
}

// ---------------------- REMOVE CONTACT ----------------------
void Remove_Contact(void) {
    // Load contacts from CSV first
    FILE *file = fopen("phonebook.csv", "r");
    if (!file) {
        printf("No contacts found!\n");
        return;
    }

    count = 0;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // remove newline
        char *name = strtok(line, ",");
        char *num = strtok(NULL, ",");
        if (name && num) {
            strcpy(names[count], name);
            strcpy(numbers[count], num);
            count++;
        }
    }
    fclose(file);

    if (count == 0) {
        printf("No contacts to remove!\n");
        return;
    }

    char target[MAX_LEN];
    printf("Remove Contact (name): ");
    fgets(target, sizeof(target), stdin);
    target[strcspn(target, "\n")] = 0; // remove newline

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(target, names[i]) == 0) {
            found = 1;
            for (int j = i; j < count - 1; j++) {
                strcpy(names[j], names[j + 1]);
                strcpy(numbers[j], numbers[j + 1]);
            }
            count--;
            break;
        }
    }

    if (!found) {
        printf("Contact not found!\n");
        return;
    }

    // Rewrite CSV after removal
    file = fopen("phonebook.csv", "w");
    if (!file) {
        printf("File error!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s\n", names[i], numbers[i]);
    }
    fclose(file);

    printf("Contact removed successfully!\n");
}

// ---------------------- SORT CONTACTS ----------------------
void Sort_Contacts(char names[][MAX_LEN], char numbers[][MAX_LEN], int count) {
    char tempName[MAX_LEN], tempNum[MAX_LEN];
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (strcmp(names[j], names[j + 1]) > 0) {
                strcpy(tempName, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], tempName);

                strcpy(tempNum, numbers[j]);
                strcpy(numbers[j], numbers[j + 1]);
                strcpy(numbers[j + 1], tempNum);
            }
        }
    }
}

// ---------------------- HELPER FUNCTIONS ----------------------
void lowercase(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

char *get_string(const char *label) {
    char *input = malloc(MAX_LEN);
    if (!input) return NULL;
    printf("%s", label);
    fgets(input, MAX_LEN, stdin);
    input[strcspn(input, "\n")] = 0; // remove newline
    return input;
}

int get_int(const char *label) {
    int input;
    printf("%s", label);
    scanf("%d", &input);
    while (getchar() != '\n'); // clear buffer
    return input;
}
