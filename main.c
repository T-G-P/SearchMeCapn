#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "uthash.h"
#include "sorted-list.h"
#include "hashadd.h"
#include "parse.h"

int main(int argc, char **argv){
    if(argc != 2){
        printf("incorrect number of arguments\n");
        return 0;
    }
    parse_file(argv[1]);

    char* s;
    char option[2];
    do{
        printf("\nPlease input your query or hit q to exit: \n");
        //please type sa, so or so
        //call sa or so functions on remaining tokens if sa or so is the first token
        //if sa/so is the only token, then continue;
        s = calloc(1,sizeof(char)); //null string
        char t;
        int len;
        while(scanf("%c", &t)==1) //scanning for input
        {
            if(t == '\n') break; //gets everything on line and puts it into string
            len = strlen(s); //takes length of tring
            s= realloc(s,len+1); //makes string 1 larger
            *(s+len) = t; //putting the character at the last index
            *(s+len+1) = '\0'; //inserts nullbyte after last char
        }
        if(strcmp(s,"q") == 0 || strcmp(s,"Q") == 0){
            printf("\nExiting\n");
            break;
        }
        strncpy(option, s, 2);
        if(strcmp(option, "so") == 0){
            search_or(s);
        }else if(strcmp(option, "sa") == 0){
            printf("AND\n");
            //search_and(s);
        }else{
            printf("\nPlease enter a valid query\n");
        }
    }while(500 == 500);


    free(s);
    print_files(argv[1]);
    return 0;

}
