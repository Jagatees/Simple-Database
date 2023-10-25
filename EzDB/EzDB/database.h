//
//  database.h
//  EzDB
//
//  Created by Jagateesvaran on 25/10/23.
//

#ifndef database_h
#define database_h

#include <stdio.h>
#include <string.h>

#endif /* database_h */


// Instruction strut
struct Instruction {
    const char* SHOW;
    const char* INSERT;
    const char* QUERY;
    const char* UPDATE;
    const char* DELETE;
    const char* ALL;
};

struct Instruction db_instruction = {
    .SHOW = "SHOW",
    .ALL = "ALL",
    .INSERT = "INSERT",
    .QUERY = "QUERY",
    .UPDATE = "UPDATE",
    .DELETE = "DELETE"
};


// Logic of Database
int logic_databse(char *inv[], int inc);

// Instruction Function
void show_all_instruction(void);
void insert_instruction(void);
void query_instruciton(void);
void update_instruciton(void);
void delete_instruciton(void);
