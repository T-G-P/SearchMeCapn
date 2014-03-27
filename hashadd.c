#include <string.h>  /* strcpy */
#include <stdlib.h>  /* malloc */
#include <stdio.h>   /* printf */
#include "uthash.h"
#include "hashadd.h"
#include "sorted-list.h"

int compareStrings(void *p1, void *p2)
{
    char *s1 = p1;
    char *s2 = p2;

    return strcmp(s1, s2);
}

//Destructor functions
void destroyBasicTypeAlloc(void *p){
    //For pointers to basic data types (int*,char*,double*,...)
    //Use for allocated memory (malloc,calloc,etc.)
    free(p);
}

void destroyBasicTypeNoAlloc(void *p) {
    //For pointers to basic data types (int*,char*,double*,...)
    //Use for memory that has not been allocated (e.g., "int x = 5;SLInsert(mylist,&x);SLRemove(mylist,&x);")
    return;
}


struct hash *tokenHash = NULL;

void add_node(void *token, void *fileName){
    //printf("This is the token/key: %s\n",token);
    struct hash *h;
    HASH_FIND_STR(tokenHash, token, h);
    if(h == NULL){
        SortedListPtr sorted_list = SLCreate(compareStrings,destroyBasicTypeNoAlloc);
        h = (struct hash*)malloc(sizeof(struct hash));
        h->token  = token;
        //printf("Inserting %s file into key %s\n",fileName,token);
        h->list = sorted_list;
        SLInsert(h->list, token, fileName);
        HASH_ADD_STR(tokenHash, token, h); //add this hash node to the hash table
    }
    else{
        //printf("Inserting %s into key %s\n",fileName,token);
        SLInsert(h->list,token,fileName);
    }
}

int token_compare (struct hash *a, struct hash *b) {
    return strcmp(a->token,b->token);
}

void sort_by_token() {
    HASH_SORT(tokenHash, token_compare);
}

void print_files() {
    struct hash *h;
    Node *ptr;
    for(h=tokenHash; h != NULL; h=(struct hash*)(h->hh.next)) {
        printf("%s\n", h->token);  //print the token
        ptr = h->list->head;  //points to hash node
        //sortList(ptr);
        while(ptr){     //while the pointer is not null
            printf("%s\n", ptr->fileName); //then for each token print file names and count
            ptr = ptr->next;
        }
    }
}

