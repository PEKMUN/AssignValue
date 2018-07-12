#include "TextParser.h"
#include <ctype.h>
#include <stdio.h>
#include <malloc.h>

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

int getStringLength(char **linePtr)
{
	int i=0;
	
	if ((*linePtr)== NULL || (**linePtr)=='\0')
	{
		return 0;
	}
	
	else
	{
		while((**linePtr) != ' ' && (**linePtr) != '=')
		{
			if((**linePtr) == '\0'){
				(*linePtr) -= i;
				return i;
			}
			else 
			{	
				i++;
				(*linePtr)++;
			}
		}
		(*linePtr) -= i;
		return i;
		
	}
}

void skipSpaces(char **line)
{
	while(isspace(**line))
	{
		(*line)++;
	}
}

int parseAndConvertToNum(char **linePtr)
{
  int sum=0;

	while((**linePtr) != '\0')
  {
	if(isspace(**linePtr))
	{
		(*linePtr)++;
	}
	
	else
	{
		sum = (**linePtr) - 48 + sum * 10;
		(*linePtr)++;  
	}		
  }
  return sum;
}

int stringContains(char **linePtr, char *cmpStr)
{
  int i;
  int strlgth = getStringLength(linePtr) + 1;
  char *temp, *strptr;
  temp = malloc(strlgth);
  
  strptr = *linePtr;
  
  for(i=0;i<10;i++)
  {
    temp[i] = (*strptr);
    strptr++;
  }
  
  temp[i] = '\0';
  
  if(parseAndCompare(linePtr, temp))
  {
    return 1;
  }
  
  else 
    return 0;
}

int parseTextAndAssignValues(char **line, VariableMapping *varTableMapping) 
{
  if(stringContains(line, "assign"))
  {
	while(varTableMapping->name != NULL)
	{
		if(parseAndCompare(line, varTableMapping->name))
		{
			if(stringContains(line, "="))
			{
				if(isdigit(**line))
				{
					*varTableMapping->storage = parseAndConvertToNum(line);
				}
			}
		}
	}
  }
}
