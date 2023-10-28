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
#include <ctype.h>
#include <stdlib.h>

#include "j_node.h"


// Logic of Database
int logic_databse(char *inv[], int inc, node_t **head);
char *rtrim(char *s);
node_t* printFileContents(const char *filename, node_t **head);




#endif /* database_h */


