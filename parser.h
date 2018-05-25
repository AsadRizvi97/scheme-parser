/****************************************************************
 File: parser.h
 ----------------
 This is a Scheme parser that parses Scheme expressions into the
 List data type to be ready for evaluation.
 ****************************************************************/

#ifndef PARSER
#define PARSER
#include <stdlib.h>
#include "conscell.h"

/****************************************************************
 Function: printList(List list)
 -----------------------
 Prints out the given list on a new line.
 ****************************************************************/
void printList(List list);

/****************************************************************
 Function: s_expr()
 -----------------------
 Parses input from the command line into C and returns it in the
 List data type.
 ****************************************************************/
List s_expr(char token[]);

#endif //PARSER
