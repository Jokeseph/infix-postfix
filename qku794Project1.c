#include "Stack.h"
#include <ctype.h>
#include <string.h>

#define MAX_LINE_LENGTH 50

int operatorCheck(char check);
int priority(char check);
int convertToPostfix(char *infixString, char *postfixString);
int evaluatePostfix(char *postfixString);


int main()
{
	FILE *inputFile;
	inputFile = fopen("p1Input.txt", "r");
	if(inputFile == NULL){

		perror("Error opening file");
		return -1;
	}


	//This string will hold the infix equations that are read from inputFile, one at a time.
	char infixString[MAX_LINE_LENGTH];


	//Use fgets to read the next line from the inputFile.
	//Store the line into infixString.
	//The while loop repeats until there are no more lines in the file.
	while(fgets(infixString, MAX_LINE_LENGTH, inputFile)!=NULL){

		//If the line is blank, skip it.
		if(infixString[0] == '\n')
			continue;

		printf("Current infix string: %s",infixString);

		//postfixString is a string to store the equation from szInfixString converted into postfix.
		char postfixString[MAX_LINE_LENGTH];

		//Call the convertToPostfix function (that you are to implement below main).
		int returnMessage = convertToPostfix(infixString,postfixString);


		//convertToPostfix should return an integer letting us know if the infix string was in a valid format.
		//If the format is valid (we returned 0), then we call the evalutaePostfix function (that you are to implement below), and print the result of the evalution.
		//If the format is not valid (we returned something other than 0), then we print the corresponding error message.
		switch(returnMessage)
		{

			case 0: //0 means the infix string had no errors.  Go ahead and evaluate the postfix string.
				printf("Postfix string: %s\n",postfixString);
				int result = evaluatePostfix(postfixString);
				printf("It evaluates to %d.\n",result);
				break;
			case 1:  //1 means the infix string is missing a left parenthesis.
				printf("WARNING: Missing left parenthesis.\n");
				break;
			case 2: //2 means the infix string is missing a right parenthesis.
				printf("WARNING: Missing right parenthesis.\n");
				break;
			case 3: // 3 means missing operator.
				printf("WARNING: Missing operator.\n");
				break;
			case 4: //4 means missing operand.
				printf("WARNING: Missing operand.\n");
				break;
			default:
				printf("WARNING: %d.\n", returnMessage);


		}


		printf("\n\n");
	}

	fclose(inputFile);

	return 0;
}


/*******
int convertToPostfix(char *infixString, char *postfixString)

Input: 
infixString is a character array of length <= MAX_LINE_LENGTH that contains an equation in infix format.
postfixString is a currently empty character array of length <= MAX_LINE_LENGTH that we should fill with a postfix representation of infixString.

Output:
We return an integer based on any errors found in infixString.
If there are no errors, return 0.
If there is a missing (, return 1.
If there is a missing ), return 2.
If there is a missing operator, return 3 (for extra credit).
If there is a missing operand, return 4 (for extra credit).
*********/
int convertToPostfix(char *infixString, char *postfixString){
    
    Stack s = newStack(MAX_LINE_LENGTH);
    int left = 0;
    int right = 0;
    int i = 0;
    int j = 0;
    int operator = 0;
    int operand = 0;

    printf("\nChecking for errors...\n");
    while(infixString[i] != '\0')
    {
        if(infixString[i] == '(')
        {
            left++;
        }
        else if(infixString[i] == ')')
        {
            right++;
        }
        else if(isdigit(infixString[i]))
        {
            operand++;
        }
        else if(infixString[i] == '+' || infixString[i] == '-' || infixString[i] == '*' || infixString[i] == '/')
        {
            operator++;
        }
        i++;
    }


if(left < right)
    {
        return 1;
    }
    if(right < left)
    {
        return 2;
    }
    if(operator + 1 < operand)
    {
        return 3;
    }
    if(operator + 1 > operand)
    {
        return 4;
    }
     else
    {
        printf("\nCONVERTING STRING TO POSTFIX...\n");
        char next;
        Element temp;
        temp.operation = '(';
        push(s, temp);
        strcat(infixString, ")");

        i = 0;
        j = 0;
        next = infixString[i];

        while(next != '\0')
        {
            if(next == '(')
            {
                temp.operation = next;
                push(s, temp);
            }
            else if(isdigit(next))
            {
                postfixString[j] = next;
                j++;
            }
            else if(operatorCheck(next) == 1)
            {
                temp.operation = pop(s).operation;
                while(operatorCheck(temp.operation) == 1 && priority(temp.operation) >= priority(next))
                {
                    postfixString[j] = temp.operation;
                    j++;
                    temp.operation = pop(s).operation;
                }
                push(s, temp);

                temp.operation = next;
                push(s, temp);
            }
            else if(next == ')')
            {
                temp.operation = pop(s).operation;
                while(temp.operation != '(')
                {
                    postfixString[j] = temp.operation;
                    j++;
                    temp.operation = pop(s).operation;
                }
            }

            i++;
            next = infixString[i];

        }

        postfixString[j] = '\0';
        printf("\nCONVERSION SUCCESSFUL\n");

        return 0;
    }


	
	
}



/************
evaluatePostfix(char *postfixString)

Input:
postfixString is a string of length <= MAX_LINE_LENGTH that contains an equation in postfix representation.
If your convertToPostfix() function is correct, this string should be in a valid postfix format.

Output:
Return an integer representing what the postfix equation evaluated to.
************/
int evaluatePostfix(char *postfixString){

Stack s = newStack(MAX_LINE_LENGTH);
    Element result;
    Element temp1;
    Element temp2;
    int i = 0;


    while(postfixString[i] != '\0')
    {
    printf("Hello\n");
        if(postfixString[i] == '+')
        {
            temp1.operand = pop(s).operand;
            temp2.operand = pop(s).operand;
            result.operand = temp1.operand + temp2.operand;
            push(s, result);
        }
        else if(postfixString[i] == '-')
        {
            temp1.operand = pop(s).operand;
            temp2.operand = pop(s).operand;
            result.operand = temp1.operand - temp2.operand;
            push(s, result);
        }
        else if(postfixString[i] == '*')
        {
            temp1.operand = pop(s).operand;
            temp2.operand = pop(s).operand;
            result.operand = temp1.operand * temp2.operand;
            push(s, result);
        }
        else if(postfixString[i] == '/')
        {
            temp1.operand = pop(s).operand;
            temp2.operand = pop(s).operand;
            result.operand = temp1.operand / temp2.operand;
            push(s, result);
        }
        else
        {
            temp1.operand = postfixString[i];
            push(s, temp1);
        }

        i++;
    }

    return result.operand;
	

}

int operatorCheck(char check)
{
    if(check == '+' || check == '-' || check == '*' || check == '/')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int priority(char check)
{
    if(check == '*' || check == '/')
    {
        return 2;
    }
    else if(check == '+' || check == '-')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
