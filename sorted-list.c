#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "sorted-list.h"

/*Creates a Linked List Node
 *
 */

Node *createNode(void * token, void *fileName)
{
    Node *llNode = malloc(sizeof(Node));
    llNode->token= token;
    llNode->fileName = fileName;
    llNode->refCount = 0;
    llNode->next = NULL;
    return llNode;
}

/*
 * SLCreate creates a new, empty sorted list.  The caller must provide
 * a comparator function that can be used to order objects that will be
 * kept in the list, and a destruct function that gets rid of the objects
 * once they are no longer in the list or referred to in an iterator.
 *
 * If the function succeeds, it returns a (non-NULL) SortedListT object,
 * otherwise, it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df)
{
    SortedListPtr sl = malloc(sizeof(struct SortedList));
    sl->head = NULL;
    sl->cf = cf;
    sl->df = df;
    return sl;
}

/*
 * SLDestroy destroys a list, freeing all dynamically allocated memory.
 *
 * You need to fill in this function as part of your implementation.
 */

void SLDestroy(SortedListPtr list)
{
    if(!list){
        return;
    }
    /*Destroy all Nodes, fileName. Free on the nodes, and df(fileName)*/
    Node *ptr = NULL;
    while(list->head != NULL){
        list->df(list->head->fileName);
        list->df(list->head->token);
        ptr = list->head;
        list->head = list->head->next;
        free(ptr);
    }
    free(list);
}

int SLInsert(SortedListPtr list, void *token, void*fileName)
{
    if(!list || !token|| !fileName){       //if there is no list, or new fileName, return successfully
        return 0;               //there's just nothing to insert
    }

    //we definitely are inserting something now, so we create a new node
    Node *newNode = createNode(token,fileName);

    if(list->head == NULL || list->cf(list->head->fileName, fileName) < 0){
        newNode->next = list->head;     //Make the new node point to the current head
        list->head = newNode;           //Make the head the new node
        return 1;
    }

    Node *ptr = list->head;
    Node *prev= NULL;

    while(ptr != NULL){
        if(list->cf(ptr->fileName, fileName) == 0){   //no duplicate insertion
            return 0;
        }
        else if(list->cf(ptr->fileName, fileName) < 0){ //if fileName is bigger, insert
            Node *newNode = createNode(token, fileName);
            if(prev == NULL){       //the new object is bigger than the head
                Node *temp = ptr;       //store head
                list->head = newNode;   //change head
                newNode->next = temp;   //set previous head to head->next
            }
            prev->next = newNode;
            newNode->next = ptr;
            newNode->refCount++;
            return 1;
        }
        else if(list->cf(ptr->fileName, fileName) > 0){ //if fileName is smaller, keeping going
            prev = ptr;
            ptr = ptr->next;
        }
    }
    prev->next = newNode;
    return 1;
}

/*int SLRemove(SortedListPtr list, void *fileName)
{
    if(!list || list->head == NULL || !fileName){
        return 0;
    }

       if(list->cf(list->head->fileName, fileName) == 0){
       Node *tmp = list->head;
       list->head = list->head->next;
       list->head->refCount++;     //Sortedlistptr is pointing to this node now
       tmp->refCount--;            //Sortedlistptr no longer pointing to this node
       if(tmp->refCount <= 0){    //if the node has nothing pointing to it (no iterator)
       list->df(tmp->fileName);    //Destroys the fileName of the node
       if(tmp->next != NULL){      //if temp has a next, decrement its refCount
       tmp->next->refCount--;
       }
       free(tmp);
       return 1;
       }
       }
    Node *ptr = list->head;
    Node *prev = NULL;
    while(ptr != NULL){
        if(list->cf(ptr->fileName, fileName) == 0){
            if(prev == NULL){       //deleting the head
                list->head = list->head->next;
                if(list->head){
                    list->head->refCount++;     //SortedListPtr is pointing to this node now
                }
                ptr->refCount--;    //ptr no longer has the sorted list pointing to it
                ptr->reMoved = 1;
                if(ptr->refCount <= 0){     //if there is nothing pointing to this node
                    list->df(ptr->fileName);
                    if(ptr->next !=NULL){   //if the ptr has a next
                        ptr->next->refCount--;  //decrement the reference count
                    }
                    free(ptr);
                    return 1;
                }
            }
            else{
                prev->next = ptr->next;     //not deleting the head
                if(ptr->next != NULL){      //the node has a next and we increment the ref count for its next
                    ptr->next->refCount++;
                    ptr->refCount--;
                    ptr->reMoved = 1;
                }
                if(ptr->refCount <=0){
                    list->df(ptr->fileName);
                    if(ptr->next != NULL){
                        ptr->next->refCount--;
                    }
                    free(ptr);
                    return 1;
                }
            }
        }
        prev = ptr;
        ptr = ptr->next;
    }
    return 0;
}
*/

SortedListIteratorPtr SLCreateIterator(SortedListPtr list)
{
    SortedListIteratorPtr slIterator = malloc(sizeof(struct SortedListIterator));
    slIterator->currNode = list->head;
    if(list->head != NULL){
        list->head->refCount++;
    }
    return slIterator;

}

void SLDestroyIterator(SortedListIteratorPtr iter)
{
    //decrement currNode count, then free iterator.
    if(iter->currNode != NULL){
        iter->currNode->refCount--;
    }
    free(iter);

}


