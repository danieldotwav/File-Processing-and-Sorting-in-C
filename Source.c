#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

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

char* read_line(char* buffer, int max_len) {
    if (fgets(buffer, max_len, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0'; /* Remove newline character */
        return strdup(buffer); /* Duplicate and return the string */
    }
    return NULL;
}

int main(void) {
    struct Record* records[MAX_RECORDS];
    int num_records = 0;
    char buffer[100]; /* Buffer for reading lines */

    /* Loop until there is no more input */
    while (fgets(buffer, MAX_LINE_LENGTH, stdin) != NULL) {
        /* Dynamically allocate memory for a record */
        struct Record* new_record = malloc(sizeof(struct Record));

        /* Print error message upon failure to dynamically allocate memory */
        if (!new_record) {
            fprintf(stderr, "Memory allocation failed.\n");
            return -1;
        }

        new_record->name = read_line(buffer, MAX_NAME_LENGTH);
        new_record->street = read_line(buffer, MAX_ADDRESS_LENGTH);
        new_record->city_and_state = read_line(buffer, MAX_ADDRESS_LENGTH);
        new_record->zipcode = read_line(buffer, MAX_ADDRESS_LENGTH);

        records[num_records] = new_record;
    }

    // Display records
    for (int i = 0; i < num_records; i++) {
        struct Record* rec = records[i];
        printf("Record %d: %s, %s, %s, %s\n", i + 1, rec->name, rec->street, rec->city_and_state, rec->zipcode);
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