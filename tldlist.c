#include "tldlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*TODO ADD ROTATES. ALL ELSE SHOULD BE THERE!*/

struct tldlist{
    Date *begin;
    Date *end;
    TLDNode *root;
    long count;
    int size;
};

struct tldnode{
    TLDNode *left;
    TLDNode *right;
    char *tldName;
    long count;
};

struct tlditerator{
    long next;
    long size;
    void **elements;
};

TLDList *tldlist_create(Date *begin, Date *end){
    TLDList *tld;
    tld = (TLDList *)malloc(sizeof(TLDList));
    tld->begin = begin;
    tld->end = end;
    tld->root = NULL;
    tld->count = 0;
    tld->size = 0;
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
    temp = (char *)malloc(sizeof(char*) *10);
    strcpy(temp, prev+1);
    return temp;
}

int tldnode_height( TLDNode *node) {
        int height_left = 0;
        int height_right = 0;

        if ( node->left ) height_left = tldnode_height( node->left );
        if ( node->right ) height_right = tldnode_height( node->right );

        return height_right > height_left ? ++height_right : ++height_left;
}


int balance_factor( TLDNode *node) {
    int bf = 0;

    if( node->left ) bf += tldnode_height( node->left );
    if( node->right ) bf -= tldnode_height( node->right );

    return bf;
}

TLDNode *rotate_leftleft ( TLDNode *node ) {
    TLDNode *a = node;
    TLDNode *b = a->left;

    a->left = b->right;
    b->right = a;
    return b;

}

TLDNode *rotate_leftright( TLDNode *node ) {
    TLDNode *a = node;
    TLDNode *b = a->left;
    TLDNode *c = b->right;

    a->left = c->right;
    b->right = c->left;
    c->left = b;
    c->right = a;

    return c;
}

TLDNode *rotate_rightleft( TLDNode *node ) {
    TLDNode *a = node;
    TLDNode *b = a->right;
    TLDNode *c = b->left;

    a->right = c->left;
    b->left = c->right;
    c->right = b;
    c->left = a;

    return c;

}

TLDNode *rotate_rightright( TLDNode *node ){
    TLDNode *a = node;
    TLDNode *b = a->right;
    
    a->right = b->left;
    b->left = a;

    return b;
}


TLDNode *tldnode_balance( TLDNode *node) {
    TLDNode *newroot = NULL;

    if( node->left )
        node->left = tldnode_balance( node->left );
    if( node->right )
        node->right = tldnode_balance( node->right );

    int bf = balance_factor( node );

    if( bf >= 2 ){

        if( balance_factor( node->left ) <= -1 )
            newroot = rotate_leftright( node );
        else
            newroot = rotate_leftleft( node );
    } else if( bf <= -2 ){

        if( balance_factor( node->right ) >= 1 )
            newroot = rotate_rightleft( node );
        else
            newroot = rotate_rightright( node );
    } else {
        newroot = node;
    }

    return ( newroot );
}

void tldlist_balance(TLDList *tld) {

    TLDNode *newroot = NULL;
    
    newroot = tldnode_balance( tld->root );

    if( newroot != tld->root )
        tld->root = newroot;

}


int tldlist_add(TLDList *tld, char *hostname, Date *d){
    char *name = processname(hostname);
    int compare = 0;
    if(date_compare(d, tld->begin) == -1 || date_compare(d, tld->end) == 1)
        return 0;

    tld->count++;
    TLDNode *node = NULL;
    TLDNode *next = NULL;
    TLDNode *last = NULL;
    
    if( tld->root == NULL){
        tld->root = tldnode_create();
        tld->root->tldName = name;
        tld->root->count = 1;
        tld->size++;
    }
    else {
        next = tld->root;
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
                return 1;
            }   
        }
        
        node = tldnode_create();
        node->tldName = name;
        node->count = 1;
        tld->size++;
        compare = strcmp(name, last->tldName);
        if( compare < 0 )
            last->left = node;
        if( compare > 0 )
            last->right = node;


    } 
    
    tldlist_balance(tld);   
    return 1;
    
}


TLDNode *tldlist_getroot(TLDList *tld){
    if(tld->root != NULL)
        printf("TLDROOT: %s\n", tld->root->tldName);
    return tld->root;
}


void tldlist_print(TLDNode *node){
    if( node == NULL )
        return; 

    printf("TLD: %s, Count: %ld\n", node->tldName, node->count);
    tldlist_print(node->left);
    tldlist_print(node->right); 
}

void **traverse(TLDNode *node, void** e, int *index){
    if ( node == NULL )
        return NULL;
    e[*index] = node;
    *index = *index + 1;
    traverse(node->left, e, index);
    traverse(node->right, e, index);
    //printf("Added node: %s, Index: %d\n", node->tldName, *index);
    return e;
}



TLDIterator *tldlist_iter_create(TLDList *tld){
    TLDIterator *iterator = NULL;
    int index = 0;
    if ( (iterator = malloc( sizeof( TLDIterator))) == NULL)
        return NULL;
    void **elements;
    elements = (void**)malloc(sizeof(void*)*tld->size);
    iterator->next = 0L;
    iterator->size = tld->size;
    iterator->elements = traverse(tld->root, elements, &index);
    //printf("Iterator size: %ld\n", iterator->size);
    return iterator;
}

TLDNode *tldlist_iter_next(TLDIterator *iter){
    void *element;
    if(iter->next < iter->size) {
        element = iter->elements[iter->next++];
        //printf("IN NEXT. ELEMENT: %s, NEXT: %ld\n", element->tldName, iter->next);
    }
    return element;
}
    
void tldlist_iter_destroy(TLDIterator *iter){
    free(iter);
}

long tldlist_count(TLDList *tld){
    return tld->count;
}

char *tldnode_tldname(TLDNode *node){
    return node->tldName;
}

long tldnode_count(TLDNode *node){
    return node->count;
}
