#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "uthash.h"
#include "parse.h"
#include "search.h"
#include "hashadd.h"
#include "sorted-list.h"


int search_or(char *input){
    struct hash *h;
    token = strtok(input," \n");
    SortedListPtr sorted_result = SLCreate(compareStrings,destroyBasicTypeNoAlloc);
    while((token = strtok(NULL, " \n")) != NULL && strlen(token > 0)){
        //get SL of key from hash
        HASH_FIND_STR(tokenHash, token, h);
        Node *ptr = h->list->head;
        while(ptr){
            SLInsert(sorted_result,token,ptr->fileName);
            ptr = ptr->next;
        }

    }
    //print new SL
    ptr = sorted_result->head;
    while(ptr->next){
        printf("%s, ", ptr->fileName);
        ptr = ptr->next;
    }
    if(ptr){
        printf("%s\n", ptr->fileName);
    }

    //free new SL
    SLDestroy(sorted_result);
}


int search_and(char *input){
}
