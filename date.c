/*TO DO: fix date create logic. Copy from slides. 
 *
 */

#include "date.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct date{
    char* datestring;
    int day;
    int month;
    int year;
    int dateint;
};

Date *date_create(char *datestr){
    Date *d;
    char *temp = (char *)malloc(sizeof(char)*10);
    //char *p = &temp[0];

    d = (Date *)malloc(sizeof(Date));
    d->datestring = datestr;
    /* potentially smarter way to do this... try later
    while(*datestr != '\0'){
        printf("%c\n", *datestr);
        if(*datestr != '/'){
            *p = *datestr;
            *p++;
        }
        datestr++;
    }
    d->dateint = atoi(temp);
    printf("%d\n", d->dateint);
    //printf("Date in date create: %s\n", p);
    */

    strncpy(temp, datestr, 2);
    d->day = atoi(temp);
    strncpy(temp, datestr+3, 2);
    d->month = atoi(temp);
    strncpy(temp, datestr+6, 4);
    d->year = atoi(temp);
    free(temp);

    return d;
}

void date_destroy(Date *d){
    free(d);
}


int date_compare(Date *date1, Date *date2){
    
    if (date1->year < date2->year)
        return -1;
    else if (date1->year > date2->year)
        return 1;
    else if(date1->month < date2->month)
        return -1;
    else if(date1->month > date2->month)
        return 1;
    else if(date1->day < date2->day)
        return -1;
    else 
        return 0;

    
    
    /*
    if (date1->year < date2->year)
        return -1;
    else if (date1-> year > date2->year)
        return 1;
    else {
        if (date1->month < date2->month)
            return -1;
        else if (date1->month > date2->month)
            return 1;
        else if (date1->day < date2->day)
            return -1;
        else if (date1->day > date2->day)
            return 1;
        else
            return 0;
    }
    */
    /*potentially better way to do this. fix later
    printf("Date1: %d, Date2: %d\n", date1->dateint, date2->dateint);
    if(date1->dateint < date2->dateint)
        return -1;
    else if(date1->dateint > date2->dateint)
        return 1;
    else
        return 0;    
        */
}

void print_date(Date *d){
    printf("Date: %s\n", d->datestring);
    printf("Month: %d\n", d->month);
    printf("Day: %d\n", d->day);
    printf("Year: %d\n", d->year);
}
