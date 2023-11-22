#ifndef database_h
#define database_h

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#include "databaseNode.h"

void switchState(const char* user_input);

void showAllInstruction(char *user_input[], int counter, KeyValueNode **head);
void insertInstruction(char *user_input[], int counter, KeyValueNode **head);
void queryInstruction(char *user_input[], int counter, KeyValueNode **head);
void updateInstruction(char *user_input[], int counter, KeyValueNode **head);
void saveInstruction(char *user_input[], int counter, KeyValueNode **head);
void openInstruction(char *user_input[], int counter, KeyValueNode **head);
void deleteInstruction(char *user_input[], int counter, KeyValueNode **head);
int exitInstruction(char *user_input[], int counter);


int databaseLogic(char *user_input[], int counter, KeyValueNode **head);

char *removeSpace(char *user_input);

int readFromFile(const char *filename, KeyValueNode **mainHead, char *user_input);
void saveFromFile(const char *filename, KeyValueNode **head);

char* getWorkingDirectory(char* user_input);
char* printWorkingDirectory(void);

void PRINT_INVAILD_INSTRUCTION(void);



#endif /* database_h */
