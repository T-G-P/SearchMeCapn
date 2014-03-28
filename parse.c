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
    while ((line_length = getline(&buffer, &sizeof_line, fp)) > 0) {    //allocates space for a buffer for each line
        token = strtok(buffer,delim);   //finds the first token
        if(token == NULL){  //case where there is no token
            continue;       //go to next line
        }else if(strcmp(token, "<list>") == 0){ //case where it's the first line with key
            token = strtok(NULL,delim);         //get the next token and token should now be the key
            //printf("This is the token: %s\n",token);
            key = malloc(strlen(token)*sizeof(char));   //allocate space for the key and store this token as key
            sprintf(key,"%s",token);

            //printf("This is the key: %s\n", key);
        }else if(strcmp(token, "</list>") == 0){ //case where it's the end of that key
            token = NULL;   //reset the token
            continue;
        }else{                          //case for file names/counts
            while(token != NULL && strlen(token) > 0){
                if(!isdigit(token[0])){
                    //printf("This is the key: %s\n");
                    //printf("add_node is passing %s and %s as the filename\n",key,token);
                    char *file = malloc(strlen(token)*sizeof(char));   //store this token as value
                    sprintf(file,"%s",token);   //print the token to the file
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
