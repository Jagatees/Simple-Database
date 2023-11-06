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

#define MAX_PATH_LEN 1024

// Handle Database Login based on user_input
int databaseLogic(char *inv[], int inc, node_t **head);

// Remove Trailling Whitespace from string
char *rtrim(char *s);

// Read From a TXT File and Load it into Cache (Linked List Node)
void readFromFile(const char *filename, node_t **head);

// Save Data from Cache to TXT File
void saveFromFile(const char *filenam, node_t **head);

#endif /* database_h */
