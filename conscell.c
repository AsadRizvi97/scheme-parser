/****************************************************************
 File: conscell.c
 ----------------
 This file implements the conscell data type given in conscell.h.
 ****************************************************************/

#include <string.h>
#include <stdlib.h>
#include "conscell.h"

conscell fcell = {.symbol = "()", .first = NULL, .rest = NULL};

List false = &fcell;

conscell tcell = {.symbol = "#t", .first = NULL, .rest = NULL};

List true = &tcell;

List newList() {
    List list = (conscell *) malloc(sizeof(conscell));
    return list;
}

List car(List list) {
    if (list == NULL) {
        return list;
    }
    return list->first;
}

List cdr(List list) {
    if (list == NULL) {
        return list;
    }
    return list->rest;
}

List cons(List list1, List list2) {
    List final = newList();
    strcpy(final->symbol, "");
    if (list1 == NULL || !strcmp(list1->symbol, false->symbol)) {
        final->first = false;
    } else {
        final->first = list1;
    }
    if (list2 == NULL || !strcmp(list2->symbol, false->symbol)) {
        final->rest = NULL;
    } else {
        final->rest = list2;
    }
}

int isConsCell(List list) {
    if (!strcmp(list->symbol, "")) {
        return 1;
    }
    return 0;
}
