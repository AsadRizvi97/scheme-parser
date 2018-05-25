/****************************************************************
 File: conscell.h
 ----------------
 This is a data type that allows for the parsing and evaluation
 of Scheme expressions. Innately supports car, cdr and cons.
 ****************************************************************/

#ifndef CONSCELL
#define CONSCELL

/****************************************************************
 A list is implemented as a node modeling a conscell, each
 containing a string, a pointer to the 'first' conscell, and a
 pointer to the 'rest' conscell, representing the current and
 rest of the elements of the cell, respectively.
 ****************************************************************/
struct cell {
    char symbol[20];
    struct cell *first;
    struct cell *rest;
};

/****************************************************************
 Type: List
 --------------
 Declaration of a List object takes the form,

   List list;
 ****************************************************************/
typedef struct cell conscell;
typedef conscell *List;

List false;
List true;

List newList();

/****************************************************************
 Function: car(List list)
 -----------------------
 Returns the first element of the list.

 Example usage, given a List l1 = (a b c):

   l1 = car(l1);

 l1 is now the symbol a.
 ****************************************************************/
List car(List list);

/****************************************************************
 Function: cdr(List list)
 -----------------------
 Returns the rest of a list, where the first element is removed.

 Example usage, given a List l1 = (a b c):

   l1 = cdr(l1);

 l1 is now the list (b c).
 ****************************************************************/
List cdr(List list);

/****************************************************************
 Function: cons(List list1, List list2)
 -----------------------
 Returns a list where the first element is the list list1 and the
 rest of the list is the elements in list2.

 Example usage, given a List l1 = (a b c) and List l2 = (a):

   List newList = cons(l1, l2);

 newList is now ((a b c) a).
 ****************************************************************/
List cons(List list1, List list2);

int isConsCell(List list);

#endif //CONSCELL
