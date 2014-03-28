#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "uthash.h"
#include "sorted-list.h"
#include "hashadd.h"

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
