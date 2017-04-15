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
};

Date *date_create(char *datestr){
    Date *d;
    char *day = (char *)malloc(sizeof(char)*3);
    char *month = (char *)malloc(sizeof(char)*3);
    char *year = (char *)malloc(sizeof(char)*5);
    d = (Date *)malloc(sizeof(Date));
    d->datestring = datestr;

    strncpy(day, datestr, 2);
    day[2] = '\0';
    d->day = atoi(day);
    strncpy(month, datestr+3, 2);
    month[2] = '\0';
    d->month = atoi(month);
    strncpy(year, datestr+6, 4);
    year[4] = '\0';
    d->year = atoi(year);
    free(day);
    free(month);
    free(year);

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
