#ifndef database_h
#define database_h

// Include C Header Files
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

// Include Custom Header Files
#include "j_node.h"

// Switch State db_open to db_close
void switchState(const char* user_input);

// Instruction Function
void openInstruction(char *user_input[], node_t **head);
void showAllInstruction(char *user_input[], int counter, node_t **head);
void exitInstruction(char *user_input[]);
void insertInstruction(char *user_input[], node_t **head);
void queryInstruction(char *user_input[], node_t **head);
void updateInstruction(char *user_input[], node_t **head);
void deleteInstruction(char *user_input[], node_t **head);
void saveInstruction(char *user_input[], node_t **head);


// Database Loop
int databaseLogic(char *user_input[], int counter, node_t **head);


// Trim White space
char *rtrim(char *user_input);


// Read / Write .txt File
int readFromFile(const char *filename, node_t **mainHead);
void saveFromFile(const char *filename, node_t **head);



#endif /* database_h */
