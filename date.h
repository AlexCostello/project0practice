#ifndef _DATE_H_INCLUDED_
#define _DATE_H_INCLUDED_

typedef struct date Date;

Date *date_create(char *datestr);

void date_destroy(Date *d);

int date_compare(Date *date1, Date *date2);

void print_date(Date *d);

#endif 
