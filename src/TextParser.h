#ifndef _TEXTPARSER_H
#define _TEXTPARSER_H

typedef struct VariableMapping VariableMapping;
struct VariableMapping {
  char *name;
  int *storage;
};

int parseTextAndAssignValues(char *line, VariableMapping *varTableMapping);

#endif // _TEXTPARSER_H