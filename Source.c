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

int main(void) {
    /* Initialize an array of Record objects using pointer notation */
    struct Record* records[MAX_RECORDS];
    int count = 0;



    return 0;
}
