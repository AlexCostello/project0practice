#include "tldlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct tldlist{
    Date *begin;
    Date *end;
    TLDNode *root;
    int count;
};

struct tldnode{
    TLDNode *left;
    TLDNode *right;
    char *tldName;
    long count;
};

struct tlditerator{
    TLDList *list;
    TLDNode *prev;
};

TLDList *tldlist_create(Date *begin, Date *end){
    TLDList *tld;
    tld = (TLDList *)malloc(sizeof(TLDList));
    tld->begin = begin;
    tld->end = end;
    tld->root = NULL;
    tld->count = 0;
    return tld;
}

void tldlist_destroy(TLDList *tld){
    date_destroy(tld->begin);
    date_destroy(tld->end);
    free(tld);
}

TLDNode *tldnode_create() {
    TLDNode *node;
    node = (TLDNode *)malloc(sizeof(TLDNode));
    node->left = NULL;
    node->right = NULL;
    node->count = 0;

    return node;
}


char *processname(char *name){
    char *temp;
    char *prev;
    temp = strchr(name, '.');
    prev = temp;
    while(temp != NULL)
    {
        temp = strchr(temp+1, '.');
        if(temp != NULL)
            prev = temp;
    }
    temp = prev+1;
    return temp;
}

int tldlist_add(TLDList *tld, char *hostname, Date *d){
    TLDList **tree = &tld;
    if( tld->root != NULL )
       printf("Start check: tld->root->name = %s\n", tld->root->tldName); 
    char *name = processname(hostname);
    //printf("Hostname: %s\n", name);
    int compare = 0;
    if(date_compare(d, tld->begin) == -1 || date_compare(tld->end, d) == -1){
        return 0;
    } else {
    tld->count++;
    TLDNode *node = NULL;
    TLDNode *next = NULL;
    TLDNode *last = NULL;
    
    if(*(*tree)->root == NULL){
        (*tree)->root = tldnode_create();
        (*tree)->root->tldName = name;
        (*tree)->root->count = 1;
    }
    else {
        next = (*tree)->root;
        //printf("Root name: %s\n", tld->root->tldName);
        while( next != NULL ){
            last = next;
            compare = strcmp(name, next->tldName);
            if(compare < 0){
                next = next->left;
            }
            else if(compare > 0){
                next = next->right;
            }
            else{
                next->count++;
                last = next;
                next = NULL;
                break;
            }   
        }

        node = tldnode_create();
        node->tldName = name;
        compare = strcmp(name, last->tldName);
        printf("At compare: Hostname = %s, Lasthost = %s\n", name, last->tldName);
        if( compare < 0 )
            last->left = node;
        if( compare > 0 )
            last->right = node;


    }      
    printf("TLDRoot Name: %s\n", (*tree)->root->tldName);
    return 1;
    }
}


TLDNode *tldlist_getroot(TLDList *tld){
    return tld->root;
}


void tldlist_print(TLDNode *node){
    if( node == NULL )
        return;
    tldlist_print(node->left);
    printf("TLD: %s, Count: %ld\n", node->tldName, node->count);
    tldlist_print(node->right);
}


TLDIterator *tldlist_iter_create(TLDList *tld){
    TLDIterator *iterator = NULL;
    if ( (iterator = malloc( sizeof( TLDIterator))) == NULL)
        return NULL;
    iterator->list = tld;
    return iterator;
}

void tldlist_iter_destroy(TLDIterator *iter){
    tldlist_destroy(iter->list);
    free(iter);
}

