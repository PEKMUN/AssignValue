#include "TextParser.h"
#include <ctype.h>

int parseAndCompare(char **linePtr, char *cmpStr)
{
	char addOne = 0;
	while(**linePtr != '\0' || *cmpStr != '\0')
	{
		if(isspace(**linePtr))
		{
			(*linePtr)++;
			addOne++;
		}
		
		else if(isspace(*cmpStr))
		{
			cmpStr++;
		}
		
		else if(tolower(**linePtr) != tolower(*cmpStr))
		{
			(*linePtr) -= addOne;
			return 0;
		}
	  
		else
		{
			cmpStr++;
			addOne++;
			(*linePtr)++;
		}
    }  
	return 1;
}

/*int parseAndConvertToNum(char **linePtr)
{
  
}

int parseTextAndAssignValues(char *line, VariableMapping *varTableMapping) {
  return 0;
}*/
