/***************************************************************
 File: eval.c
 ----------------
 This file implements the evaluator interface given in eval.h.
 ***************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "eval.h"
#include "conscell.h"
#include "parser.h"

List globalList;

List quote(List list) {
    return car(cdr(list));
}

List symbol(List list) {
    if (car(list) == NULL && cdr(list) == NULL) {
        return true;
    } else {
        return false;
    }
}

List append(List list1, List list2) {
    if (null(list1) == true) {
        return list2;
    } else {
        return cons(car(list1), append(cdr(list1), list2));
    }
}

List null(List list) {
    if (list == NULL) {
        return true;
    } else if (!strcmp(list->symbol, false->symbol)) {
        return true;
    } else {
        return false;
    }
}

/****************************************************************
 Implementation note: This is a Scheme function that determines
 if two lists are equal to each other. Only case when this is
 true is when both are NULL, or if their symbols, car and cdr are
 equal to each other.
 ****************************************************************/
List equal(List list1, List list2) {
    if (list1 == NULL) {
        if (list2 == NULL) {
            return true;
        }
        return false;
    }
    if (!strcmp(list1->symbol, list2->symbol)) {
        if (equal(car(list1), car(list2)) == true && equal(cdr(list1), cdr(list2)) == true) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

/****************************************************************
 Implementation note: This is a Scheme function that determines
 if an association list contains a symbol and then returns the
 pair in the association list if it is contained. Compares the
 car of the car of the association list, which is the first
 symbol in the first list of the association list, with the
 given symbol. If found, it returns the first list directly.
 Otherwise, the first list is discarded and the scan continues
 until it is either found or the association list becomes NULL.
 ****************************************************************/
List assoc(List list1, List list2) {
    if (list2 == NULL || !strcmp(list2->symbol, false->symbol)) {
        return false;
    }
    if (!strcmp(car(car(list2))->symbol, list1->symbol)) {
        return car(list2);
    } else {
        list2 = cdr(list2);
        assoc(list1, list2);
    }
}

/****************************************************************
 Implementation note: This is a Scheme function that
 ****************************************************************/
List cond(List list) {
    if (eval(car(car(list))) == true || !strcmp(car(car(list))->symbol, "else")) {
        return eval(car(cdr(car(list))));
    } else {
        list = cdr(list);
        cond(list);
    }
}

/****************************************************************
 Implementation note: This is a Scheme function that allows
 symbols to be evaluated as an expression. The first few lines
 manually create the structure necessary for an association list
 which is then added to the front of the global association list.
 ****************************************************************/
List define(List list1, List list2) {
        List pair = newList();
        strcpy(pair->symbol, "");
        pair->first = list1;
        pair->rest = newList();
        strcpy(pair->rest->symbol, "");
        pair->rest->first = list2;
        pair->rest->rest = NULL;
        globalList = cons(pair, globalList);
        return list1;
}

List isList(List list) {
    if (list == NULL) {
        return false;
    } else if (!strcmp(list->symbol, "") || !strcmp(list->symbol, "()")) {
        return true;
    }
    return false;
}

List isFunction(List list) {
    List inEnv = assoc(list, globalList);
    if (strcmp(inEnv->symbol, false->symbol) == 0) {
        return false;
    } else if (isList(car(cdr(inEnv))) == true && !strcmp(car(car(cdr(inEnv)))->symbol, "define")) {
        return true;
    }
    return false;
}

List defineFn(List list1, List list2) {
    List pair = newList();
    strcpy(pair->symbol, "");
    pair->first = car(list1);
    pair->rest = newList();
    strcpy(pair->rest->symbol, "");
    pair->rest->first = list2;
    pair->rest->rest = NULL;
    globalList = cons(pair, globalList);
    return car(list1);
}

List addHelper (List list, int sum) {
    if (list == NULL || !strcmp(list->symbol, "()")) {
        List result = newList();
        char buffer[20];
        sprintf(buffer, "%d", sum);
        strcpy(result->symbol, buffer);
        return result;
    }
    sum = sum + atoi(eval(car(list))->symbol);
    return addHelper(cdr(list), sum);
}

List add(List list) {
    return addHelper(list, 0);
}

List subtractHelper (List list, int diff) {
    if (list == NULL || !strcmp(list->symbol, "()")) {
        List result = newList();
        char buffer[20];
        sprintf(buffer, "%d", diff);
        strcpy(result->symbol, buffer);
        return result;
    }
    diff = diff - atoi(eval(car(list))->symbol);
    return subtractHelper(cdr(list), diff);
}

List subtract(List list) {
    if (list == NULL) {
        return false;
    }
    return subtractHelper(cdr(list), atoi(eval(car(list))->symbol));
}

List multiplyHelper (List list, int product) {
    if (list == NULL || !strcmp(list->symbol, "()")) {
        List result = newList();
        char buffer[20];
        sprintf(buffer, "%d", product);
        strcpy(result->symbol, buffer);
        return result;
    }
    product = product * atoi(eval(car(list))->symbol);
    return multiplyHelper(cdr(list), product);
}

List multiply(List list) {
    if (list == NULL) {
        return false;
    }
    return multiplyHelper(cdr(list), atoi(eval(car(list))->symbol));
}

List createList(List list) {
    List final = newList();
    List temp = final;
    while (car(list) != NULL) {
        List elmnt = eval(car(list));
        list = cdr(list);
        temp->first = elmnt;
        if (car(list) != NULL) {
            temp->rest = newList();
        }
        temp = cdr(temp);
    }
    return final;
}

/****************************************************************
 Implementation note: This is a private function that allows
 defined functions to be evaluated. The first few lines retrieve
 the necessary elements for evaluation from the global
 environment. The function then evaluates each parameter provided
 and adds them to the global environment, keeping track of how
 many have been added. The function definition is then evaluated
 and local parameters are removed from the global environment.
 ****************************************************************/
List evalFn(List list) {
    List definition = car(cdr(assoc(car(list), globalList)));
    List function = car(cdr(cdr(definition)));
    List params = cdr(car(cdr(definition)));
    int paramno = 0;
    List localList = false;
    while (params != NULL) {
        List pair = newList();
        strcpy(pair->symbol, "");
        pair->first = car(params);
        pair->rest = newList();
        strcpy(pair->rest->symbol, "");
        pair->rest->first = eval(car(cdr(list)));
        pair->rest->rest = NULL;
        localList = cons(pair, localList);
        list = cdr(list);
        params = cdr(params);
        paramno++;
    }
    while (localList != NULL) {
        globalList = cons(car(localList), globalList);
        localList = cdr(localList);
    }
    List result = eval(function);
    for (int i = 0; i < paramno; i++) {
        globalList = cdr(globalList);
    }
    return result;
}

/****************************************************************
 Implementation note: This is a function that determines
 which function must be performed on the inputted list to
 correctly evaluate it. If the list is not just a symbol, the
 function searches for the supported commands in the conscell
 structure and recursively evaluates the contents before
 applying the outermost function to the resulting list. Once
 internally defined functions are checked for, user defined
 functions and variables are checked and returned as necessary.
 ****************************************************************/
List eval(List list) {
    if (list != NULL && isConsCell(list)) {
        if (!strcmp(car(list)->symbol, "quote")) {
            return quote(list);
        } else if (!strcmp(car(list)->symbol, "car")) {
            list = car(cdr(list));
            return car(eval(list));
        } else if (!strcmp(car(list)->symbol, "cdr")) {
            list = car(cdr(list));
            return cdr(eval(list));
        } else if (!strcmp(car(list)->symbol, "cons")) {
            List list1 = eval(car(cdr(list)));
            List list2 = eval(car(cdr(cdr(list))));
            return cons(list1, list2);
        } else if (!strcmp(car(list)->symbol, "symbol?")) {
            list = eval(car(cdr(list)));
            return symbol(list);
        } else if (!strcmp(car(list)->symbol, "append")) {
            List list1 = eval(car(cdr(list)));
            List list2 = eval(car(cdr(cdr(list))));
            return append(list1, list2);
        } else if (!strcmp(car(list)->symbol, "null?")) {
            list = car(cdr(list));
            return null(eval(list));
        } else if (!strcmp(car(list)->symbol, "equal?")) {
            List list1 = eval(car(cdr(list)));
            List list2 = eval(car(cdr(cdr(list))));
            return equal(list1, list2);
        } else if (!strcmp(car(list)->symbol, "assoc")) {
            List list1 = eval(car(cdr(list)));
            List list2 = eval(car(cdr(cdr(list))));
            return assoc(list1, list2);
        } else if (!strcmp(car(list)->symbol, "cond")) {
            list = cdr(list);
            return cond(list);
        } else if (!strcmp(car(list)->symbol, "define")) {
            if (isList(car(cdr(list))) == true) {
                List list1 = car(cdr(list));
                List list2 = list;
                return defineFn(list1, list2);
            } else {
                List list1 = car(cdr(list));
                List list2 = eval(car(cdr(cdr(list))));
                return define(list1, list2);
            }
        } else if (!strcmp(car(list)->symbol, "list?")) {
            list = eval(car(cdr(list)));
            return isList(list);
        } else if (!strcmp(car(list)->symbol, "function?")) {
            list = car(cdr(list));
            return isFunction(list);
        } else if (!strcmp(car(list)->symbol, "+")) {
            list = eval(cdr(list));
            return add(list);
        } else if (!strcmp(car(list)->symbol, "-")) {
            list = eval(cdr(list));
            return subtract(list);
        } else if (!strcmp(car(list)->symbol, "*")) {
            list = eval(cdr(list));
            return multiply(list);
        } else if (!strcmp(car(list)->symbol, "list")) {
            list = eval(cdr(list));
            return createList(list);
        } else if (!strcmp(car(list)->symbol, "exit")) {
            printf("Have a nice day!");
            exit(0);
        } else if (isFunction(car(list)) == true) {
            return evalFn(list);
        } else {
            return list;
        }
    } else {
        if (assoc(list, globalList) == false) {
            return list;
        } else {
            list = assoc(list, globalList);
            return car(cdr(list));
        }
    }
}
