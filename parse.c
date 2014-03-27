#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "uthash.h"
#include "sorted-list.h"
#include "hashadd.h"

int parse_file(char *);

int parse_file(char *file_name){
    FILE *fp = fopen(file_name, "r");
    size_t sizeof_line = 0;
    char* buffer = NULL;
    char *token = NULL;
    char *delim = " \n";
    char *key;
    ssize_t line_length = 0;
    /*Taking the next line from fp, allocating space for it in buffer and returns
     * the length of the line
     */
    while ((line_length = getline(&buffer, &sizeof_line, fp)) > 0) {
        token = strtok(buffer,delim);
        if(token == NULL){  //case where there is no token
            continue;       //go to next line
        }else if(strcmp(token, "<list>") == 0){ //case where it's the first line with key
            token = strtok(NULL,delim);         //token should now be the key
            //printf("This is the token: %s\n",token);
            key = malloc(strlen(token)*sizeof(char));   //store this token as key
            sprintf(key,"%s",token);

            //printf("This is the key: %s\n", key); //this is where we create node
        }else if(strcmp(token, "</list>") == 0){ //case where it's the end of that key
            token = NULL;
            continue;                   //this hash thing is done, add node to hash here
        }else{                          //case for file names/counts
            while(token != NULL && strlen(token) > 0){
                if(!isdigit(token[0])){
                    //printf("This is the key: %s\n");
                    //printf("add_node is passing %s and %s as the filename\n",key,token);
                    char *file = malloc(strlen(token)*sizeof(char));   //store this token as key
                    sprintf(file,"%s",token);
                    add_node(key,file);
                    //printf("%s\n", token); //add to linked list
                }
                token = strtok(NULL, delim);
            }
        }
    }
    if(buffer) free(buffer);
    fclose(fp);
    return 1;
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("incorrect number of arguments\n");
        return 0;
    }
    parse_file(argv[1]);
    /*char *query;
      printf("Please input your query or multiple queries: \n");
      scanf("%s", query);
      printf("You entered: %s\n", query);
      */
    /*
       char *str;

    // Initial memory allocation
    str = (char *) malloc(15);
    printf("Please input your query or multiple queries: \n");
    scanf("%s", str);

    // Reallocating memory
    str = (char *) realloc(str, strlen(str));
    printf("You entered: %s\n", s);

    free(str);
    */
    int quit = 0;
    char* s;
    do{
        printf("Please input your query or multiple queries: \n");
        s = calloc(1,sizeof(char));
        char t;
        int len;
        while(scanf("%c", &t)==1)
        {
            if(t == '\n')
                break;
            len = strlen(s);
            s= realloc(s,len+1);
            *(s+len) = t;
            *(s+len+1) = '\0';
        }
        if(strcmp(s,"q") == 0 || strcmp(s,"Q") == 0){
            quit = 1;
        }
        printf("You entered: %s\n", s);
    }while(!quit);


    free(s);
    //print_files(argv[1]);
    return 0;

}



