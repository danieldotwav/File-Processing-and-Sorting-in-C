#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_ADDRESS_LENGTH 50
#define MAX_NAME_LENGTH 30
#define MAX_RECORDS 50
#define LINE_SIZE 100

/* Record information */
struct Record {
    char* name;
    char* street;
    char* city_and_state;
    char* zipcode;
};

/* Helper function to read a single line of input and return a char pointer */
char* readLine() {
    char* line = malloc(LINE_SIZE + 1);

    if (!fgets(line, LINE_SIZE, stdin)) {
        free(line);
        return NULL;
    }

    /* Remove newline character */
    line[strcspn(line, "\n")] = '\0';
    return line;
}

int main(void) {
    /* Initialize an array of Record objects using pointer notation */
    struct Record* records[MAX_RECORDS];
    int num_records = 0;
    char current = '\0';

    while (num_records < MAX_RECORDS) {
        struct Record* new_record = malloc(sizeof(struct Record));

        new_record->name = readLine();
        new_record->street = readLine();
        new_record->city_and_state = readLine();
        new_record->zipcode = readLine();

        records[num_records] = new_record;

        /* Consume newline */
        getchar();
    }

    /* Display records */
    for (int i = 0; i < num_records; i++) {
        struct Record* rec = records[i];
        printf("Record %d: %s, %s, %s, %s\n", i + 1, rec->name, rec->street, rec->city_and_state, rec->zipcode);
    }

    /* Cleanup */
    for (int i = 0; i < num_records; i++) {
        free(records[i]->name);
        free(records[i]->street);
        free(records[i]->city_and_state);
        free(records[i]->zipcode);
        free(records[i]);
    }

    return 0;
}
