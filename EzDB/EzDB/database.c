//
//  database.c
//  EzDB
//
//  Created by Jagateesvaran on 25/10/23.
//

#include "database.h"


// Instruction strut
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
int logic_databse(char *inv[], int inc){
    
    if (inv[0] == NULL) {
        printf("U Enter Nothing So we are kicking u out .\n");
        return 1;
    }
    if (inc >= 2 && strcmp(inv[0], db_instruction.SHOW) == 0 && strcmp(inv[1], db_instruction.ALL) == 0) // SHOW ALL INSTRUCTION
    {
        printf("Welcome to SHOW ALL Instruction\n");
//        show_all_instruction();
        return 0;
    }
    if (strcmp(inv[0], db_instruction.INSERT) == 0)
    {
        printf("Welcome to INSERT Instruction\n");
//        insert_instruction();
        return 0;
    }
    else if (strcmp(inv[0], db_instruction.QUERY) == 0) // QUERY INSTRUCTION
    {
        printf("Welcome to QUERY Instruction\n");
//        query_instruciton();
        return 0;
    }
    else if (strcmp(inv[0], db_instruction.UPDATE) == 0) // UPDATE INSTRUCTION
    {
        printf("Welcome to UPDATE Instruction\n");
//        update_instruciton();
        return 0;
    }
    else if (strcmp(inv[0], db_instruction.DELETE) == 0) // DELETE INSTRUCTION
    {
        printf("Welcome to DELETE Instruction\n");
//        delete_instruciton();
        return 0;
    }
    else {
        printf("I don't understand this command %s\n", inv[0]);  // INVAILD INSTRUCTION
        return 0;
    }

    
    
    
    
    return 0;
    
}

void show_all_instruction(void){
    
}
void insert_instruction(void){
    
}
void query_instruciton(void){
    
}
void update_instruciton(void){
    
}
void delete_instruciton(void){
    
}




