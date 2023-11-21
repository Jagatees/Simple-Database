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

void openInstruction(char *user_input[], KeyValueNode **head);
void showAllInstruction(char *user_input[], int counter, KeyValueNode **head);
void exitInstruction(char *user_input[]);
void insertInstruction(char *user_input[], KeyValueNode **head);
void queryInstruction(char *user_input[], KeyValueNode **head);
void updateInstruction(char *user_input[], KeyValueNode **head);
void deleteInstruction(char *user_input[], KeyValueNode **head);
void saveInstruction(char *user_input[], KeyValueNode **head);

int databaseLogic(char *user_input[], int counter, KeyValueNode **head);

char *removeSpace(char *user_input);

int readFromFile(const char *filename, KeyValueNode **mainHead);
void saveFromFile(const char *filename, KeyValueNode **head);

char* getWorkingDirectory(char* user_input);
char* printWorkingDirectory(void);


#endif /* database_h */
