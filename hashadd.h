#ifndef HASHADD_H
#define HASHADD_H
/*
 * hashadd.h
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "uthash.h"
#include "sorted-list.h"

struct hash{
    char *token;          /* key */
    struct SortedList *list;  //The value is a sorted list pointer to file linked list
    UT_hash_handle hh;         /* makes this structure hashable */
};

Node *createNode(void*,void *);

void add_node(void*, void*);

int token_compare(struct hash *, struct hash *);

void sort_by_token(void);

//void sortList(struct Node*);

void print_files();

#endif

