#ifndef RECORD_H
#define RECORD_H

#define MAX_ADDRESS_LENGTH 50
#define MAX_NAME_LENGTH 30
#define MAX_RECORDS 50
#define MAX_LINE_LENGTH 100

/* Record information */
struct Record {
    char name[MAX_NAME_LENGTH];
    char street[MAX_ADDRESS_LENGTH];
    char city_and_state[MAX_ADDRESS_LENGTH];
    char zipcode[MAX_ADDRESS_LENGTH];
};

#endif