/***************************************************************
 File: eval.h
 ----------------
 This is a list evaluator which can evaluate Scheme expressions.
 This evaluator supports the functions quote, symbol?, null?,
 equal?, assoc, cond, define, list? and function? as well as
 the evaluation of user defined functions.
 ***************************************************************/

#ifndef EVAL
#define EVAL
#include "conscell.h"

List globalList;

/****************************************************************
 Function: quote(List list)
 -----------------------
 Prevents evaluation of the contents of the list.

 Example usage, given a List l1 = (car(a b c)):

   l1 = quote(l1);

 l1 is still (car(a b c)).
 ****************************************************************/
List quote(List list);

/****************************************************************
 Function: symbol(List list)
 -----------------------
 Returns #t if the list is a symbol, returns () otherwise.

 Example usage, given a List l1 = a:

   symbol(l1);

 This would return the symbol #t.
 ****************************************************************/
List symbol(List list);

/****************************************************************
 Function: append(List list1, List list2)
 -----------------------
 Returns a list where the elements of list2 are inserted at the
 end of list1.

 Example usage, given a List l1 = (a b c) and List l2 = (d):

   List newList = cons(l1, l2);

 newList is now (a b c d).
 ****************************************************************/
List append(List list1, List list2);

/****************************************************************
 Function: null(List list)
 -----------------------
 Returns #t if the list is null, returns () otherwise.

 Example usage, given a List l1 = ():

   null(l1);

 This would return the symbol #t.
 ****************************************************************/
List null(List list);

/****************************************************************
 Function: equal(List list1, List list2)
 -----------------------
 Returns #t if the two lists are equal, returns () otherwise.

 Example usage, given a List l1 = (quote (a b)) and a
 List l2 = (quote (a b)):

   equal(l1, l2);

 This would return the symbol #t.
 ****************************************************************/
List equal(List list1, List list2);

/****************************************************************
 Function: assoc(List list1, List list2)
 -----------------------
 For this function, list1 must be a symbol and list2 must be an
 association list. Returns the pair associated with the symbol
 in list1, returns () otherwise.

 Example usage, given a List l1 = (quote joan) and a
 List l2 = (quote ((john smith) (joan doe) (marcia law))):

   assoc(l1, l2);

 This would return the list (joan doe).
 ****************************************************************/
List assoc(List list1, List list2);

/****************************************************************
 Function: cond(List list)
 -----------------------
 Operates as an if statement equivalent in Scheme.

 Example usage, given a List l1 = ((null? (quote ()))
                                   (car (quote (a b))))
                                   (#t (cdr (quote (a b))))):

   cond(l1);

 This would return a.
 ****************************************************************/
List cond(List list);

/****************************************************************
 Function: define(List list1, List list2)
 -----------------------
 For this function, list1 must be a symbol. Associates the symbol
 in list1 with the expression in list2. Returns list1.

 Example usage, given a List l1 = fname and a
 List l2 = (quote (john));

   define(l1, l2);

 The symbol fname would subsequently be evaluated as (john).
 ****************************************************************/
List define(List list1, List list2);

/****************************************************************
 Function: isList(List list)
 -----------------------
 Returns #t if the expression is a list, returns () otherwise.

 Example usage, given a List l1 = (a b c):

   symbol(l1);

 This would return the symbol #t.
 ****************************************************************/
List isList(List list);

/****************************************************************
 Function: isFunction(List list)
 -----------------------
 Returns #t if the expression is a defined function, returns ()
 otherwise.

 Example usage, given a define function f1:

   function(f1);

 This would return the symbol #t.
 ****************************************************************/
List isFunction(List list);

/****************************************************************
 Function: eval(List list)
 -----------------------
 Evaluates the given list based on the above defined functions
 and returns it.

 Example usage, given a List l1:

   l1 = eval(l1);
 ****************************************************************/
List eval(List list);

#endif //EVAL
