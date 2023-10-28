//
//  utility.h
//  EzDB
//
//  Created by Jagateesvaran on 25/10/23.
//

#ifndef utility_h
#define utility_h

#include <stdio.h>

#include "j_node.h"

#define MAX_USER_INPUT 256
const char *characters = " ?\t\n";


char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}


node_t* printFileContents(const char *filename) {
    node_t *head = NULL;
    node_t *tmp;
    FILE *file = fopen(filename, "r");
    
    if (!file) {
        perror("Error opening file");
        return NULL;
    }
 
    char line[1024];
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        
        char *key = strtok(line, "\t");
        char *value = strtok(NULL, "\t");
        
        if (key && value) {
            tmp = create_new_node(rtrim(key), rtrim(value));
            head = insert_at_head(&head, tmp);
        }
    }

    fclose(file);
    return head;
}


#endif /* utility_h */
