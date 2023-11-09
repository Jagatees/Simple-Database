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

// Handle the Switchin of OPEN & Close State
void switch_state(const char* user_input);

// Handle the logic of the database and where which instruction go to
int databaseLogic(char *inv[], int inc, node_t **head);

// Different type of instruction
void handleOpenCommand(char *inv[], node_t **head);
void handleShowAllCommand(char *inv[], int inc, node_t **head);
void handleExitCommand(char *inv[]);
void handleInsertCommand(char *inv[], node_t **head);
void handleQueryCommand(char *inv[], node_t **head);
void handleUpdateCommand(char *inv[], node_t **head);
void handleDeleteCommand(char *inv[], node_t **head);
void handleSaveCommand(char *inv[], node_t **head);

// Remove char from word
char *rtrim(char *data);

// Read and Write into Txt File
int readFromFile(const char *filename, node_t **mainHead);
void saveFromFile(const char *filename, node_t **head);


#endif /* database_h */
