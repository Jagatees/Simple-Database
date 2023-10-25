//
//  database.c
//  EzDB
//
//  Created by Jagateesvaran on 25/10/23.
//

#include "database.h"

struct DB {
    const char* SHOW;
    const char* INSERT;
    const char* QUERY;
    const char* UPDATE;
    const char* DELETE;
    const char* ALL;
};

struct DB db_instruction = {
    .SHOW = "SHOW",
    .ALL = "ALL",
    .INSERT = "INSERT",
    .QUERY = "QUERY",
    .UPDATE = "UPDATE",
    .DELETE = "DELETE"
};


// inv is the list of user input string and inc is the counter length
int init_databse(char *inv[], int inc){

    // Check if the user enter nothing
    if (inv[0] == NULL){
        printf("U Enter Nothing So we are kicking u out .\n");
        return 1;
    }
    
    // SHOW ALL INSTRUCTION
    if (inc >= 2 &&
        strcmp(inv[0], db_instruction.SHOW) == 0 &&
        strcmp(inv[1], db_instruction.ALL)  == 0)
    {
        printf("Welcome to SHOW ALL Instruction\n");
        return 0;
    }
    
    // INSERT INSTRUCTION
    else if (strcmp(inv[0], db_instruction.INSERT) == 0)
    {
        printf("Welcome to INSERT Instruction\n");
        return 0;
    }
    
    // QUERY INSTRUCTION
    else if (strcmp(inv[0], db_instruction.QUERY) == 0)
    {
        printf("Welcome to QUERY Instruction\n");
        return 0;
    }
    
    // UPDATE INSTRUCTION
    else if (strcmp(inv[0], db_instruction.UPDATE) == 0)
    {
        printf("Welcome to UPDATE Instruction\n");
        return 0;
    }
    
    // DELETE INSTRUCTION
    else if (strcmp(inv[0], db_instruction.DELETE) == 0)
    {
        printf("Welcome to DELETE Instruction\n");
        return 0;
    }
    
    // INVAILD INSTRUCTION
    else {
        printf("I don't understand this command %s\n", inv[0]);
        return 0;
    }
    
    return 0;
}



