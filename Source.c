#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ADDRESS_LENGTH 50
#define MAX_NAME_LENGTH 30
#define MAX_RECORDS 50
#define MAX_LINE_LENGTH 100

/* Record information */
struct Record {
    char* name;
    char* street;
    char* city_and_state;
    char* zipcode;
};

void removeNewline(char* str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int main(void) {
    struct Record* records[MAX_RECORDS];
    int num_records = 0;
    char buffer[100]; /* Buffer for reading lines */

    /* Loop until there is no more input */
    while (fgets(buffer, MAX_LINE_LENGTH, stdin) != NULL && num_records < MAX_RECORDS) {
        /* Dynamically allocate memory for a record */
        struct Record* new_record = malloc(sizeof(struct Record));

        /* Print error message upon failure to dynamically allocate memory */
        if (!new_record) {
            fprintf(stderr, "Memory allocation failed.\n");
            break;
        }

        // Name
        removeNewline(buffer);
        new_record->name = _strdup(buffer);
        if (!new_record->name) {
            fprintf(stderr, "Memory allocation for name failed.\n");
            free(new_record);
            break;
        }

        // Address
        if (fgets(buffer, MAX_LINE_LENGTH, stdin) == NULL) {
            free(new_record->name);
            free(new_record);
            break;
        }

        removeNewline(buffer);
        new_record->street = _strdup(buffer);
        if (!new_record->street) {
            fprintf(stderr, "Memory allocation for street failed.\n");
            free(new_record->name);
            free(new_record);
            break;
        }

        // City and State
        if (fgets(buffer, MAX_LINE_LENGTH, stdin) == NULL) {
            free(new_record->name);
            free(new_record->street);
            free(new_record);
            break;
        }

        removeNewline(buffer);
        new_record->city_and_state = _strdup(buffer);
        if (!new_record->city_and_state) {
            fprintf(stderr, "Memory allocation for city and state failed.\n");
            free(new_record->name);
            free(new_record->street);
            free(new_record);
            break;
        }

        // Zipcode
        if (fgets(buffer, MAX_LINE_LENGTH, stdin) == NULL) {
            free(new_record->name);
            free(new_record->street);
            free(new_record->city_and_state);
            free(new_record);
            break;
        }

        removeNewline(buffer);
        new_record->zipcode = _strdup(buffer);
        if (!new_record->zipcode) {
            fprintf(stderr, "Memory allocation for zipcode failed.\n");
            free(new_record->name);
            free(new_record->street);
            free(new_record->city_and_state);
            free(new_record);
            break;
        }

        /* Store newly created record object pointer */
        records[num_records] = new_record;
        num_records++;
    }

    // Display records
    for (int i = 0; i < num_records; i++) {
        struct Record* rec = records[i];
        printf("Record #%d\n", i + 1);
        printf("Name: %s\n", rec->name);
        printf("Street: %s\n", rec->street);
        printf("City and State: %s\n", rec->city_and_state);
        printf("Zipcode: %s\n", rec->zipcode);
    }

    // Cleanup
    for (int i = 0; i < num_records; i++) {
        free(records[i]->name);
        free(records[i]->street);
        free(records[i]->city_and_state);
        free(records[i]->zipcode);
        free(records[i]);
    }

    return 0;
}