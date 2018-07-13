#include "TextParser.h"
#include <ctype.h>
#include <stdio.h>
#include <malloc.h>

int parseAndCompare(char **linePtr, char *cmpStr)
{
	int addOne = 0;
	while((**linePtr) != '\0' || (*cmpStr) != '\0')
	{
    if((**linePtr) == ' ' && (*cmpStr) == '\0')
    {
      while(isspace(**linePtr))
      {
        (*linePtr)++;
        addOne++;
      }
      return 1;
    }
		
    else if((**linePtr) == '=' && (*cmpStr) == '=')
    {
      (*linePtr)++;
      return 1;
    }
    
    else if(isdigit(**linePtr) && isdigit(*cmpStr))
    {
      return 1;
    }
    
    else if((**linePtr) == '=' && (*cmpStr) == '\0')
    {
      return 1;
    }
    
		else if(isspace(*cmpStr))
		{
			cmpStr++;
		}
    
		else if(isspace(**linePtr))
		{
			(*linePtr)++;
			addOne++;
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
    if(isdigit(**linePtr))
    {
      sum = (**linePtr) - 48 + sum * 10;
      (*linePtr)++;
      while ((**linePtr) == ' ')
      {
        skipSpaces(linePtr);
        return sum;  
      }
    }
    
    else 
      skipSpaces(linePtr);
  }
  return sum;
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
		while((**linePtr) == '\0')
		{
      i++;
    }
	}
}

int stringContains(char **linePtr, char *cmpStr)
{
  int i;
  char *temp, *strptr;
  temp = malloc(256);
  skipSpaces(linePtr);
  strptr = (*linePtr);
  
  for(i=0;(*strptr) != ' ';i++)
  {
    if(isdigit(*strptr))
    {
      break;
    }
    
    else
    {
      temp[i] = *strptr;
      strptr++;
    }
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
  char *origin;
  origin = varTableMapping;
  
  if(*line == NULL)
  {
    return 0;
  }
  
  else if(varTableMapping == NULL)
  {
    throwSimpleError(5, "ERR_TABLE_IS_MISSING");
  }
    
  else if(parseAndCompare(line, "assign"))
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
            varTableMapping = origin;
          }
          else
          {
            throwSimpleError(1, "ERR_NOT_A_NUMBER");
          }
        }
        else
        {
          throwSimpleError(4, "ERR_MALFORM_ASSIGN");
        }
      }
      else
      {
        varTableMapping++;
      }
    }
    throwSimpleError(2, "ERR_UNKNOWN_VARIABLE");
  }
  else
  {
    throwSimpleError(3, "ERR_UNKNOWN_COMMAND");
  }
}
