#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Record.h"

void removeNewline(char* str); /* Helper function to remove newline character from the end of a string */
void merge(struct Record** records, int left, int mid, int right);
void mergeSort(struct Record** records, int left, int right);

int main(void) {
    struct Record* records[MAX_RECORDS];
    int num_records = 0;
    char buffer[100]; /* Buffer for reading lines */

    /* Convert input to Record objects and store them in the records array */
    while (fgets(buffer, MAX_LINE_LENGTH, stdin) != NULL && num_records < MAX_RECORDS) {
        /* Dynamically allocate memory for a record */
        struct Record* new_record = malloc(sizeof(struct Record));

        /* Print error message upon failure to dynamically allocate memory */
        if (!new_record) {
            fprintf(stderr, "Memory allocation failed.\n");
            break;
        }

        /* Name */
        removeNewline(buffer);
        new_record->name = _strdup(buffer);
        if (!new_record->name) {
            fprintf(stderr, "Memory allocation for name failed.\n");
            free(new_record);
            break;
        }

        /* Address */
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

        /* City and State */
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

        /* Zipcode */
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

    /* Sort the records by zipcode */
    mergeSort(records, 0, num_records - 1);

    /* Display sorted records */
    for (int i = 0; i < num_records; i++) {
        struct Record* rec = records[i];
        printf("%s\n", rec->name);
        printf("%s\n", rec->street);
        printf("%s\n", rec->city_and_state);
        printf("%s\n\n", rec->zipcode);
    }

    /* Deallocate dynamically allocated memory */
    for (int i = 0; i < num_records; i++) {
        free(records[i]->name);
        free(records[i]->street);
        free(records[i]->city_and_state);
        free(records[i]->zipcode);
        free(records[i]);
    }

    return 0;
}

void removeNewline(char* str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void merge(struct Record** records, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    /* Create temporary arrays to store the two halves of the records */
    struct Record** L = malloc(n1 * sizeof(struct Record*));
    struct Record** R = malloc(n2 * sizeof(struct Record*));

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) {
        L[i] = records[left + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = records[mid + 1 + j];
    }

    /* Merge the temp arrays back into records[left..right] */
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (strcmp(L[i]->zipcode, R[j]->zipcode) <= 0) {
            records[k] = L[i];
            i++;
        }
        else {
            records[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there are any */
    while (i < n1) {
        records[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there are any */
    while (j < n2) {
        records[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(struct Record** records, int left, int right) {
    if (left < right) {
        /* Same as (l+r)/2, but avoids overflow for large l and h */
        int mid = left + (right - left) / 2;

        /* Sort first and second halves */
        mergeSort(records, left, mid);
        mergeSort(records, mid + 1, right);

        merge(records, left, mid, right);
    }
}