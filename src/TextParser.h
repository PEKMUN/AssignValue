#ifndef _TEXTPARSER_H
#define _TEXTPARSER_H

typedef struct VariableMapping VariableMapping;
struct VariableMapping {
  char *name;
  int *storage;
};

int parseAndCompare(char **linePtr, char *cmpStr);
int getStringLength(char **linePtr);
int parseAndConvertToNum(char **linePtr);
int stringContains(char **linePtr, char *cmpStr);
void skipSpaces(char **line);
int parseTextAndAssignValues(char **line, VariableMapping *varTableMapping);

#endif // _TEXTPARSER_H