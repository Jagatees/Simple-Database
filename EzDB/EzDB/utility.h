
#ifndef utility_h
#define utility_h

#include <stdio.h>
#include <unistd.h>

// Store Genral Variable or Variable Used in Mutiple Files

#define MAX_USER_INPUT 256
#define MAX_PATH_LEN 2048

const char *characters = " ?\t\n";

void PRINT_SIT_DECLARATION(void){
    printf("Declaration\n");
    printf("SIT\x27s policy on copying does not allow the students to copy source code as well as assessment solutions\n");
    printf("from another person or other places. It is the students\x27 responsibility to guarantee that their assessment\n");
    printf("solutions are their own work. Meanwhile, the students must also ensure that their work is not accessible\n");
    printf("by others. Where such plagiarism is detected, both of the assessments involved will receive ZERO mark.\n");
    printf("\n");
    printf("We hereby declare that:\n");
    printf("- We fully understand and agree to the abovementioned plagiarism policy.\n");
    printf("- We did not copy any code from others or from other places.\n");
    printf("- We did not share our codes with others or upload to any other places for public access.\n");
    printf("- We agree that our project will receive Zero mark if there is any plagiarism detected.\n");
    printf("\n");
    printf("Declared by: Group Name: P6_1\n");
    printf("\n");
    printf("Team members:\n");
    printf("1. 2301770 K JAGATEESVARAN RAJOO\n");
    printf("2. 2301772 KERWIN LOH\n");
    printf("3. 2301792 JONATHAN GOH ZHE HONG\n");
    printf("4. 2301817 IAN KOH QI EN\n");
    printf("5. 2301821 KHOO YE CHEN\n");

    printf("\n");
    printf("Date: 22 Nov 2023.\n");
    printf("\n");
}



#endif /* utility_h */
