#ifndef _TLDLIST_H_INCLUDED_
#define _TLDLIST_H_INCLUDED_

#include "date.h"

typedef struct tldlist TLDList;

typedef struct tldnode TLDNode;

typedef struct tlditerator TLDIterator;

TLDList *tldlist_create(Date *begin, Date *end);

void tldlist_destroy(TLDList *tld);

int tldlist_add(TLDList *tld, char *hostname, Date *d);

TLDIterator *tldlist_iter_create(TLDList *tld);

void tldlist_iter_destroy(TLDIterator *iter);

void tldlist_print(TLDNode *node);

TLDNode *tldlist_getroot(TLDList *tld);

TLDNode *tldlist_iter_next(TLDIterator *iter);

long tldlist_count(TLDList *tld);

char *tldnode_tldname(TLDNode *node);

long tldnode_count(TLDNode *node);
#endif
