/*
                                COMP1028 PROGRAMMING AND ALGORITHMS COURSEWORK (CW.c)
                                   CW: Prefix, Postfix, Infix Expression Evaluator

        Compiler used: GCC
        IDE: CodeBlocks
        Operating system: Windows 10

---------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>

#define MAX 50 //maximum expression length

//structure for nodes in the stack that will be used for conversions
typedef struct node {
    char* expression;
    struct node* next;
}node;

//head of the stack
node* head;

//inclusions for type definitions
typedef enum { false, true } bool;

 //function prototypes
int stack(void);
char* reversing(char*);
char* spacesNo(char* );
char* brackets(char*);
int balance(char*);
int position(char* );
int priority(char );

void push(char*);
char* pop(void);

char* ConvertPrefix(char*, int);
char* ConvertPostfix(char* , int );
char* infixPostfix(char*);
char* infixPrefix(char*);


bool menu(char*, char*);

void evaluatePrefix();
void postfixEV();


int main() //main function
{
    //declaring variables
    char* input=(char*)malloc(sizeof(char)*MAX); //creating space for the input
    int i=1; //counter variable
    FILE *PTR1; //file pointer

    while(1) //loop to iterate the program
    {

        printf("\nEnter an expression:"); //prompting the user for input
        fgets(input, MAX, stdin); //gets the user input

        //saving the input in the output.txt so the user can understand the file better
        PTR1 = fopen("output.txt", "a"); // opening output.txt file
        fprintf(PTR1, "The expression you entered is: %s\n", input); // saving the input to output.txt
        printf("Your input was saved to the file.\n"); //telling the user the input was saved
        fclose(PTR1); //closing the file using is pointer

    //removing spaces
        input=spacesNo(input);
    //calling the menu function
    //output to be saved in output.txt
        menu(input, "output.txt");

    i++;
    } //ending the while loop

    return 0; //indicates  successful end of a run of the program
}

//menu function
//this is what will be displayed to the user after they've entered their expression
//depending on the expression they'll be entering
bool menu(char* input, char* output)
{ //its parameters are the input expression and the output expression after conversion

    FILE* PTR; //file pointer
    char option; //option character that will enable the user to choose what they want to do
    char choice; //choice character that will enable the users to choose what they want to do
                //for the second run of the program



    PTR=fopen(output,"a"); //creating and opening the output.txt file to save the results

    //first we have to check if the expression has imbalanced parentheses or not
    if(balance(input))
    {
         printf(" ");
         return 0;
    } //if the parentheses are balanced it will continue on with the program

// a switch case depending on the type of expression
//calling the position function to check on where the operator is
//so we can know the type of expression
   switch(position(input))
   {
case 1: //if the expression is a prefix expression
    printf("This is a prefix expression. Would you like to:\n"); //tells the user its a prefix expression
    printf("A- Convert it to infix\n"); //and asks them what they want to do
    printf("B- Convert it to postfix\n");
    printf("C- Evaluate the expression\n");
    printf("D- Exit the program.\n");
    printf("Your choice: ");
    scanf("%c", &option); //getting the user's input that is their choice

    if(option=='A' || option=='a') //if the user chooses to convert the expression to an infix expression
    {
        printf("The infix expression is: %s\n", ConvertPrefix(input, 2)); //calling the function that converts prefix to infix
                                                                         //and displaying the results to the user
        //saving the output in the output.txt file
        output=ConvertPrefix(input,2); //assigning the converted expression to output
        fprintf(PTR, "Prefix expression converted to an infix expression:%s\n", output); //putting the converted expression into output.txt
        printf("Output was saved to output file.\n"); //telling the user that the output was saved
        fclose(PTR); //closing the file using its pointer

    }
    else if(option=='B' || option=='b') //if the user chooses to convert the expression to a postfix expression
    {
        printf("The postfix expression is: %s\n", ConvertPrefix(input, 3)); //calling the function that converts prefix to postfix
                                                                            //and displaying the results to the user
        //saving the output in the output.txt file
        output=ConvertPrefix(input, 3); //assigning the converted expression to output
        fprintf(PTR, "Prefix expression converted to a postfix expression: %s\n", output); //putting the converted expression into output.txt
        printf("Output was saved to output file.\n"); //telling the user that the output was saved in the file
        fclose(PTR); //closing the file using its pointer
    }
    else if(option=='C'|| option=='c') //if the user chooses to evaluate the expression
    {
        evaluatePrefix(); //calling the function that will evaluate the expression
    }
    else if(option=='D' || option=='d') //f the user chooses to terminate the program
    {
        printf("Program Ended."); //tells the user that the program ended
        exit(0); //exits the program
    }
    else //else if the user entered anything else other than A, B, C or D
    {
        printf("Invalid choice.\n"); //tells the user its an invalid choice
    }
    break;

   case 2: //if the expression is an infix expression
    printf("This is an infix expression. Would you like to:\n"); //telling the user it is an infix expression
    printf("A- Convert it to prefix\n");                        //and asking what the want to do
    printf("B- Convert it to postfix\n");
    printf("C- Evaluate the expression\n");
    printf("D- Exit the program.\n");

    printf("Your choice: "); //asking the user for their choice
    scanf("%c", &option); //getting user's choice

    if(option=='A' || option=='a') //if the user chooses to convert the expression to prefix
    {
        printf("The prefix expression is: %s\n", infixPrefix(input)); //calling the function that converts infix to prefix
                                                                     //and displaying the converted expression to the user
        //saving the output in the output.txt file
        output=infixPrefix(input); //assigning the converted expression to output
        fprintf(PTR, "Infix expression converted to an prefix expression: %s\n", output); //putting the converted expression into output.txt
        printf("Output was saved to output file.\n"); //telling the user the output was saved to the output.txt file
        fclose(PTR); //closing the file using its pointer
    }
    else if(option=='B' || option=='b') // if the user chooses to convert the expression into a postfix expression
    {
        printf("The postfix expression is: %s\n", infixPostfix(input)); //calling the function that converts infix to postfix
                                                                        //and displaying the converted expression to the user
        //saving the output in output.txt
        output=infixPostfix(input); //assigning the converted expression to output
        fprintf(PTR, "Infix expression converted to an postfix expression: %s\n", output); //putting the converted expression into output.txt
        printf("Output was saved to output file.\n"); //telling the user that the output was saved
        fclose(PTR); //closing the file using its pointer
    }
    else if(option=='C' || option=='c') //if the user chooses to evaluate the expression
    {
         printf("The postfix expression is: %s\n", infixPostfix(input));//converting the expression to postfix first
                                                                        //since the evaluator is only for postfix expressions
         postfixEV();//calling the function that evaluates expressions

    }
    else if(option=='D' || option=='d') //if the user chooses to end the program
    {
        printf("Program Ended."); //telling the user that the program has ended
        exit(0); //exiting the program
    }
    else //if the user enters anything that's not one of the options A, B, C or D
    {
        printf("Invalid choice.\n"); //telling the user its an invalid choice
    }
   break;

   case 3: //if the expression is a postfix expression


    printf("This is a postfix expression. Would you like to:\n"); //telling the user its a postfix expression
    printf("A- Convert it to infix\n");                           //and asking them what they want to do
    printf("B- Convert it to prefix\n");
    printf("C- Evaluate the expression\n");
    printf("D- Exit the program.\n");
    printf("Your choice: "); //asking the user for their choice
    scanf("%c", &option); //getting the user's choice



    if(option=='A' || option =='a') //if the user chooses to convert the expression to infix
    {
        printf("The infix expression is: %s\n", ConvertPostfix(input, 2)); //calling the function that changes postfix to infix
                                                                           //and displaying the converted expression to the user
        //saving the output in the output.txt file
        output=ConvertPostfix(input, 2); //assigning the converted expression to output
        fprintf(PTR, "Postfix expression converted to an infix expression: %s\n", output); //putting the converted expression in the file
        printf("Output was saved to output file.\n"); //telling the user the output was saved in output.txt
        fclose(PTR); //closing the file using its pointer
    }
    else if(option=='B' || option=='b') //if the user chooses to convert the expression to prefix
    {
        printf("The prefix expression is: %s\n", ConvertPostfix(input, 1)); //calling the function that changes postfix to prefix
                                                                            //and displaying the converted expression to the user
        //saving the output in the output.txt file
        output=ConvertPostfix(input,1); //assigning the converted expression to output
        fprintf(PTR, "Postfix expression converted to an prefix expression: %s\n", output); //putting the converted expression in the file
        printf("Output was saved to output file.\n"); //telling the user the output was saved in output.txt
        fclose(PTR); //closing the file using its pointer
    }
    else if(option=='C' || option =='c') //if the user chooses to evaluate the expression
    {
        postfixEV(); //calling the function that evaluates postfix expressions
    }
    else if(option=='D' || option=='d') //if the user chooses to end the program
    {
        printf("Program Ended."); //telling the user the program is ending
        exit(0); //ending the program
    }
    else //if the user enters anything else other than the options A, B ,C or D
    {
        printf("Invalid choice.\n"); //telling the user its an invalid choice
    }
   break;

   default: //if the user enters an invalid expression or anything else
    printf("Invalid input.\n"); //telling the user its an invalid expression
    printf("Restart the program.\n"); //asking the user to restart the program

}
    //this section is used to iterate the program
    //the program wouldn't iterate without the presence of a scanf here
    //but it also wouldn't wait for the user's input before iterating if the user is asked for their input
    //so it is just placed in the program with this form to aid in iteration

    scanf("%c", &choice);

    if (choice == 'A' || choice == 'a')
    {
        return 1;
    }  // this will inform the main function to do the program again
    else
    {
        printf("");
        return 0;
    }

}

//function that converts prefix expressions
//into postfix or infix
char* ConvertPrefix(char* exp, int prefix)
{ //its parameters are the input expression and what the expression is to be converted to

    int i; //counter variable
    char* output= (char*)malloc(sizeof(char)*MAX); //output string
    char* temp=(char*)malloc(sizeof(char)*MAX); //temporary string
    //strings to be used for popping
    char* operand1=(char*)malloc(sizeof(char)*MAX);
    char* operand2=(char*)malloc(sizeof(char)*MAX);
    //assigning the length of the expression to length1 for easier user
    int length1=strlen(exp);

    for (i=length1-1; i>=0; i--) //a for loop to go through each character
    {
        if(exp[i]=='^' || exp[i]=='/' || exp[i]=='*' || exp[i]=='+' || exp[i]=='-' ) //if the character is an operator
        {
            strcpy(output,""); //emptying the output string
            sprintf(temp, "%c", exp[i]); //places the current character into the temporary string

            //if there are less than two characters in the expression
            if(stack() < 2)
            {
                return "This expression is not valid."; //then the expression is valid and the program will let the user know
            }
            else
            {
                if (prefix == 3) {
                //if the user wants to convert the prefix expression to a postfix expression

                    //pop these two strings out of the stack
                    strcpy(operand1, pop());
                    strcpy(operand2, pop());
                    //join the characters and arrange them so they'd appear as a postfix expression
                    //in the form operand1, operand2, operator
                    strcat(output, operand1);
                    strcat(output, operand2);
                    strcat(output, temp);
                    //pushes the output expression back into the stack
                    push(output); }

               else if (prefix == 2) {
                //if the user wants to convert the prefix expression to an infix expression
                //pop these two strings out
                    strcpy(operand1, pop());
                    strcpy(operand2, pop());
                    //joins the opening parentheses to the output expression
                    strcat(output, "(");
                    //joins the characters and arranges them so they'd appear as an infix expression
                    //in the form operand1, operator, operand2
                    strcat(output, operand1);
                    strcat(output, temp);
                    strcat(output, operand2);
                    //joins the closing parentheses to the expression
                    strcat(output, ")");
                    //pushes the expression back into the stack
                    push(output);
            }
            }
        } else { //else for the operands
                sprintf(temp,"%c", exp[i]); //place the operands in the temporary string
                push(temp); //push the string into the stack
            }
    }

    //if the stack still has anything left in it after the above is done
    if(stack() > 1)
    {
        return "This expression is not valid."; //then the expression is not valid and the program lets the user know
    } else { //else it will remove the brackets and will output the infix expression
        if (prefix == 2) { //if the expression is to be converted to infix
        return brackets(pop()); //remove the brackets and pop
    } else {
        return pop(); //else just pop for any other expression type
    }
    }
}

//function to convert postfix expressions
//to infix or prefix expressions
char* ConvertPostfix(char* exp, int expression)
{ //its parameters are the input expression and what the expression is to be converted to
    int i; //counter variable
    //strings to be used for popping
    char* operand1=(char*)malloc(sizeof(char)*MAX);
    char* operand2=(char*)malloc(sizeof(char)*MAX);
    char* temp=(char*)malloc(sizeof(char)*MAX); //temporary string
    char* output=(char*)malloc(sizeof(char)*MAX); //output string

    for(i=0; i<strlen(exp); i++) //loop to go through all characters
    {
        if (exp[i]=='*' || exp[i]=='/' || exp[i]=='^' || exp[i]=='+' || exp[i]=='-') //if the character is an operator
        {
            strcpy(output,""); //make the output string empty
            sprintf(temp,"%c", exp[i]); //place the current character into temp

            if (stack()<2) //if there are less than two characters in the stack then the expression is not valid
            {
                return "Invalid expression."; //informing the user that the expression is not valid
            }
            else
            {
                if (expression == 1) //if the user chooses to convert the expression to prefix
                {
                    //pop these two strings out of the stack
                    strcpy(operand1, pop());
                    strcpy(operand2, pop());
                    //join the characters so they'd appear in the form of a prefix expression
                    //in the form operator, operand2, operand1
                    strcat(output, temp);
                    strcat(output, operand2);
                    strcat(output, operand1);
                    //push the output expression into the stack
                    push(output);
                }
                else if (expression == 2) //if the user chooses to convert the expression to infix
                {
                    //pop these two strings out of the stack
                    strcpy(operand1, pop());
                    strcpy(operand2, pop());
                    //join the opening bracket to the expression
                    strcat(output, "(");
                    //join the characters together so they'd be in the form of an infix expression
                    //in the form operand2, operator, operand1
                    strcat(output, operand2);
                    strcat(output, temp);
                    strcat(output, operand1);
                    //join the closing bracket to the expression
                    strcat(output, ")");
                    //push the output expression into the stack
                    push(output);
                }
            }
        }

        else //for the operands
        {
            sprintf(temp, "%c", exp[i]); //place the operands into the temporary string
            push(temp); //push the string into the stack
        }
    }

    if (stack() > 1) //if anything is left after the above is done
    {
        return "Invalid expression."; //then the expression is invalid and we let the user know
    }
    else
    { //else remove the brackets and output the infix expression
        if (expression == 2) // if the expression is to be converted to infix
        {
            return brackets(pop()); //remove the brackets and pop
        }
        else
        {
            return pop(); //else just pop for any other expression type
        }
    }

}

//function to convert infix expressions to postfix expressions
char* infixPostfix(char* exp)
{ //its parameter is the expression input by the user

    int i, j; //counter variables
    char* output = malloc(sizeof(char)*MAX); //creating an output string and allocating space in memory for it
    char* ops= malloc(sizeof(char)*MAX); //this will be used for the stack of operators

    for(i=0; i<strlen(exp); i++) //for all characters in the expression
    {
        if(exp[i]=='+' || exp[i]=='-' || exp[i]=='/' || exp[i]=='*' || exp[i]=='^') //if the character is an operator
        {
            if(ops[strlen(ops)-1]=='(') //if the opening bracket is at the head of the stack
            {
                ops[strlen(ops)]=exp[i]; //push the current operator to be the head of the stack
            }
            else
            { //else if the character is an operand
                for(j=strlen(ops)-1; j>=0; j--) //loop for all the operators in the stack
                {
                    if(ops[j]=='(') //if there is an opening bracket
                    {
                        break; //continue pushing into the stack
                    }
                    else if ( (exp[i]=='^') && (priority(exp[i]) < priority(ops[j])) )
                        //else if there is a ^ in the expression and the precedence of the
                        //the current operator at the head of the stack is less than that of ^
                    {
                        //then we pop out the operator currently at the head
                        //and add it to the end of the postfix expression
                        output[strlen(output)] =ops[j];
                        ops[j]= '\0';
                    }
                    else if ( priority(exp[i])<=priority(ops[j]) )
                        //else if any other operator's precedence is less than or equal to
                        //that of the operator at the head of the stack
                    {
                        //then we pop out the operator currently at the head
                        //and add it to the end of the postfix expression
                        output[strlen(output)]=ops[j];
                        ops[j]='\0';
                    }
                }

                ops[strlen(ops)]=exp[i]; //push the operator into the stack
            }
        }
        else if (exp[i]=='(') //if there is an opening bracket
        {
            ops[strlen(ops)]=exp[i]; //push it into the operators stack
        }
        else if (exp[i]==')') //if there is a closing bracket
        {
            for (j=strlen(ops); j>=0; j--) //for all that is in the stack
            {
                if (ops[j]=='(') //if there is an opening bracket
                {
                    ops[j]='\0'; //pop it from the stack
                    break; //and exit
                }
                else //else
                {
                    output[strlen(output)]=ops[j]; //pop the operator out of the stack and add it to the end of the expression
                    ops[j]='\0';
                }
            }
        }
        else //for anything else
        {
            output[strlen(output)]=exp[i]; //add it to the end of the postfix string
        }
    }
    for (i=strlen(ops)-1; i>=0; i--) //for all things in the stack starting from the second item
    {
        output[strlen(output)]=ops[i]; //pop it out of the stack and add it to output string
    }

    return output; //return the output string

}

//function that converts infix expressions to prefix expressions
char* infixPrefix(char* exp)
{ //its parameter is the expression input by the user
    char* output=(char*)malloc(sizeof(char)*MAX); //output string

    output = reversing(exp); //reverse the expression
    output = infixPostfix(output); //convert the expression to postfix using the function
                                    //that converts infix expressions to postfix expressions
    output = reversing(output); //then reverse the expression again

    return output; //output the prefix expression

}

//pop function
//this will pop items out of the stack
char* pop(){
    char* exp; //output string
    exp=(char*)malloc(sizeof(char)*MAX); //allocating memory for the output string
    node *x; //a node that is going to be popped

    if (head!=NULL) //if the head of the stack is not empty
    {
        strcpy(exp, head->expression); //copy the expression at the top to the output string
        x = head; // removing what is currently at the top of the stack
        head = head->next; // //now the head will point to the next item and it will be at the top
        free(x); //free what was removed
    }

 return exp; //return the output string at the head of the stack

}

//push function
//this will push items into the stack
void push(char* exp)
{ //its parameter is the input expression

    node* x; //creating a new node
    char* string; //creating a new string

    x=(node*)malloc(sizeof(node)); //allocating memory for the new node
    string=(char*)malloc(sizeof(char)*MAX); //allocating memory for the new string

    strcpy(string, exp); //copy the expression into the string
    x->expression = string; // make the expression in the node as the string
    x->next=NULL; //have the next node point to nothing

    if(head!=NULL) //if the current head is not empty
    { //then push the current node down and make it the top of the stack
        x->next = head;
        head = x;
    }
    else { //if the current head is empty

        head = x; // then set the current node as the head
    }
}

//a function to check the priority (precedence) of the operators
//this function will return the priority of an operator as an integer
int priority(char opr)
{ //its parameters are the operators
    switch (opr)
    { //swicth statement for the operators
        case '/':
        case '*':
            return 2;
            break;
        case '^':
            return 3; //highest priority
            break;
        default:
            return 1;
            break;

    }
}


//function to check the position of the operator
//according to the position of the operator, it will return whether the
//expression is an infix expression, a prefix expression or a postfix expression
int position(char* exp)
{ //its parameter is the input expression
    int length = strlen(exp);
    if (exp[0] == '+' || exp[0]=='-' || exp[0]=='*' || exp[0]=='/' || exp[0]=='^') //if the first character is an operator
    {
        return 1; //it is a prefix expression
    }
    else if (exp[length-1]=='+' || exp[length-1]=='-' || exp[length-1]=='*' || exp[length-1]=='/' || exp[length-1]=='^')
        //else if the last character is an operator
    {
        return 3; //then it is a postfix expression
    }
    else
    {
        return 2; //else it is an infix expression
    }
}


//function to check if the parentheses are balanced or not
int balance(char* exp) {
//its parameter is the input expression

    //counter variables
    int i;
    int last=0, first=0;

    //counts the parentheses
    for(i=0; i<strlen(exp); i++)
    {
        if (exp[i] == '(')
                first++; //if in the expression there's an ( it will count it
        if (exp[i] == ')')
                last++; //if in the expression there's an ) it will count it
    }

    if (last>first || last<first){ //if one of the parentheses is more than the other
        printf("Imbalanced parentheses.\n"); //then the parentheses are imbalanced and we tell the user so
        printf("Restart the program.\n");
        exit(0);
    }

    return first!=last ; //it will return 1 (true) if they are not balanced


}

//function to remove brackets at the end and beginning of a string
char* brackets(char* exp){
//its parameter is the input expression

    int length=strlen(exp); //assigning the length of the expression to length for easier usage
    char* output=(char*)malloc(sizeof(char)*MAX ); //creating an output string and allocating memory for it

    if( exp[0]=='(' && exp[length-1]==')') //if the first and last character are parentheses
        { exp[length-1] = '\0';  //then the last character is the terminator for the expression
        output= exp + 1; } //then the output string will point to the first character after the first bracket

    return output; //returns the expression without parentheses
}

//this is a function that removes spaces
//this function is important as it takes a string and returns the same string
//without spaces and any new lines (it normalizes the string)
//this makes it easier for the conversion functions to work
char* spacesNo(char* exp){
//its parameter is the input expression

    char* t; //token variable
    char* output=malloc(sizeof(char)*MAX); //creating an output string and allocating memory for it
    int length=strlen(exp); //assigning the length of the expression to length for easier usage

    if(exp[length-1]=='\n') //removes new line from the end of the string
    {
        exp[length-1]='\0'; //changes it to string terminator
    }

    //this will tokenize the expression (which is a string)
    //this is important as it separates the expression entered from any space
    t=strtok(exp," ");
    strcpy(output,""); //emptying the output string

    while(t!='\0') //a loop to keep going till the end of the string
    {
        strcat(output, t); //this function joins the output string with the tokenized string
        t=strtok(NULL, " "); //this will keep tokenizing the strings
    }
    return output; //returns the string without any spaces or new lines

}

//a function to reverse the expressions
char* reversing( char* exp ) {
    //its parameter is the input expression

	int i; //counter variable
	int length=strlen(exp); //assigning the length of the expression to length for easier usage
	char* reverse = (char*)malloc(sizeof(char)*MAX); //creating an output string and allocating memory for it

	for ( i = length-1; i >= 0; i-- ) { //for each character in the expression, starting with the last one

        //if there are parentheses then it will reverse them
		if( exp[i] == '(')
			reverse[length - 1 - i] = ')';
		else if( exp[i] == ')')
			reverse[length - 1 - i] = '(';
		else //otherwise it will copy the characters into the output string in reverse
			reverse[length - 1 - i] = exp[i];
	}
	return reverse; //returns the reversed expression
}

//function that returns the length of the stack
//important to check if the expressions are valid or not
int stack (void ) {
//it has no parameters
	int l = 0; //counter variable for the length
	node* ptr; //pointer to node

	//loop to check from the head of the stack till its end
	for( ptr = head; ptr != 0; ptr = ptr->next ) {
		l++; //increase the length
	}
	return l; //return the length of the stack
}

//---------------------------------PREFIX EVALUATION--------------------------------------//

int expr[MAX], top=-1; //initializing variables
                        //initializing stack with top=-1

//push function for the prefix evaluation
//it will push items out of the stack
void prepush(int i)
{ //its parameter is an integer i

    if(top==MAX-1) //if top is currently pointing at the last item of the stack
    {
        printf("There is no more space in the stack.\n"); //then the stack is full and we can't push more things in it
                                                            //and we tell the user so
    }
    else //else if top is anywhere else
    {
        top++; //increment top so it points to the next item in the stack
        expr[top]=i; //this assigns the value of i to the array element
        //for, expr[top]=i;
        //for example if top=5 means top is pointing at the 6th item and so exp[top] becomes expr[5]
        //then if we say for example i=6 and expr[5]=6 then we are assigning 6 to the 6th element of the array
        //this is done so the function will push an item into that specific position into the stack
    }
}

//pop function for prefix evaluation
//it will pop items out of the stack
int prepop()
{ //it has no parameters
    int i; //initializing variable

    //the stack is empty when top==-1
    //if it is empty that means that the expression entered is wrong
    if(top==-1)
    {
        printf("There is nothing in the stack.\n Check your expression.\n"); //and we tell the user so
    }
    else //else if it is not empty
    {
        i=expr[top]; //we are assigning what is in the array element right now to i
                    //ex if expr[5]=6 then i=6
        top--; //decrement top to move down the stack so top will point to the next item in the stack after popping
    }

    return i; //return the value i
}

//function in which the evaluation occurs
int prefix(char expr[MAX])
{ //its parameter is the expression input by the user

    char temp[MAX]; //temporary string
    int i, j; //counter variables
    int result=0; //result initialization
    int op1, op2; //operands for evaluation

    j=0; //initializing j to 0
    i=0; //initializing i to 0
    top=-1; //initializing the stack

    while(expr[i]!='\0') //while we haven't reached the end of the expression
    {

        if(expr[i]>='0' && expr[i]<='99') //if the character in the expression is an operand between 0 and 99
        {
            j=0; //initializing j to 0
            temp[j]=expr[i]; //putting the characters in the expression into the temporary array
            //increment j so there will be one more space for us to put \0 (end of string) to the array
            j++;
            temp[j]='\0';
            prepush(atoi(temp)); //the temp array is a string so we should convert it to an integer first
                                //then we push temp into the stack
        }
        else //if the character in the expression is an operator
        {
            op2=prepop(); //pop the second operand out of the stack
            op1=prepop(); //pop the first operand out of the stack

            if(expr[i]=='+') //if the character in the expression is a plus
            {
                result = op2 + op1; //add the operands and put the result in 'result' variable
            }
            else if (expr[i]=='-') //if the character in the expression is a minus
            {
                result=op2-op1; //subtract the operands and put the result in 'result' variable
            }
            else if (expr[i]=='*') //if the character in the expression is a multiplication symbol
            {
                result=op2*op1; //multiply the operands and put the result in 'result' variable
            }
            else if (expr[i]=='/') //if the character in the expression is a division symbol
            {
                result=op2/op1; //divide the operands and put the result in 'result' variable
            }
            else if (expr[i]=='^') //if the character in the expression is a power symbol
            {
                result=pow(op1,op2); //make op1 be raised to the power of op2 (op1^op2)
                                    //and put the result in 'result' variable
            }

            prepush(result); //push the result into the stack
        }
        i++; //increment to go through all characters in the expression
    }

    result=prepop(); //pop the result out of the stack
    return result; //return the result of the evaluation
}

//this part is to be used only when the function strrev is not supported
//for example when running the code on online compilers like gdb

/*char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}*/

//function in which the user input is asked and the result is displayed
void evaluatePrefix()
{
    char expr[MAX], expr2[MAX]; //input expression arrays
    int result; //initializing result variable
    FILE *evPTR, *evPTRin; //file pointers

    evPTR=fopen("output.txt","a"); //opening the file using its pointer to save the output
    evPTRin=fopen("output.txt","a"); //opening the file using its pointer to save the input

    //asking the user to enter the expression
    printf("\nEnter the prefix expression (without any spaces between the operands and operators): ");
    scanf("%s", expr); //getting user input
    fprintf(evPTRin, "The prefix expression you entered was: %s\n", expr); //saving the input in the file so it will be
                                                                          //easier for the user to save the file
    printf("Your input was saved to output.txt.\n"); //telling the user that the input was saved
    fclose(evPTRin); //closing the file after the input was saved using its pointer

    strcpy(expr2, strrev(expr)); //reversing the input and putting into another array
    result=prefix(expr2); //calling the function that evaluates expressions and putting the result in 'result'

    printf("\nResult of the evaluation: %d\n", result); //displaying the result to the user

    fprintf(evPTR, "The result of the evaluation is: %d\n", result); //saving the result of the evaluation in the output file
    printf("The result was saved to output.txt.\n"); //telling the user the result was saved in the file
    fclose(evPTR); //closing the file using its pointer
}


//---------------------------------POSTFIX EVALUATION--------------------------------------//

int expression[MAX], topp=-1; //initializing variables
                            //initializing stack with topp=-1

//push function for the postfix evaluation
//it will push items out of the stack
void postpush(int i)
{ //its parameter is an integer i

    if (topp == MAX-1) //if topp is currently pointing at the last item of the stack
    {
        printf("There is no more space left in the stack."); //then the stack is full and we can't push more things in it
                                                            //and we tell the user so
    }
    else //else if topp is anywhere else
    {
        topp++; //increment topp so it points to the next item in the stack
        expression[topp]=i; //this assigns the value of i to the array element
        //for, expression[topp]=i;
        //for example if topp=5 means topp is pointing at the 6th item and so expression[topp] becomes exprssion[5]
        //then if we say for example i=6 and expression[5]=6 then we are assigning 6 to the 6th element of the array
        //this is done so the function will push an item into that specific position into the stack
    }
}

//pop function for postfix evaluation
//it will pop items out of the stack
int postpop()
{ //it has no parameters
    int i; //initializing variable

    //the stack is empty when topp==-1
    //if it is empty that means that the expression entered is wrong
    if(topp==-1)
    {
        printf("There is nothing in the stack.\n Check your expression.\n"); //and we tell the user so
    }
    else //else if it is not empty
    {
        i=expression[topp]; //we are assigning what is in the array element right now to i
                           //ex if expression[5]=6 then i=6
        topp--; //decrement top to move down the stack so top will point to the next item in the stack after popping
    }

    return i; //return the value i
}

//function in which the evaluation occurs
int postfix(char e[MAX])
{ //its parameter is the expression input by the user

    char temp[MAX]; //temporary string
    int i, op1, op2; //counter variable and operands
    int j=0; //initializing j to 0
    int result=0; //initializing result to 0

    i=0; //initializing i to 0
    topp=-1; //initializing the stack

    while(e[i]!='\0') //while we haven't reached the end of the expression
    {
        if(e[i]>='0' && e[i]<='99') //if the character in the expression is an operand between 0 and 99
        {
            j=0; //initializing j to 0
            temp[j]=e[i]; //putting the characters in the expression into the temporary array
            //increment j so there will be one more space for us to put \0 (end of string) to the array
            j++;
            temp[j]='\0';

            postpush(atoi(temp)); //the temp array is a string so we should convert it to an integer first
                                //then we push temp into the stack
        }
        else //if the character in the expression is an operator
        {
            op1=postpop(); //pop the second operand out of the stack
            op2=postpop(); //pop the first operand out of the stack

            if(e[i]=='+') //if the character in the expression is a plus
            {
                result = op1 + op2; //add the operands and put the result in 'result' variable
            }
            else if (e[i]=='-') //if the character in the expression is a minus
            {
                result = op2 - op1; //subtract the operands and put the result in 'result' variable
            }
            else if (e[i]=='*') //if the character in the expression is a multiplication symbol
            {
                result = op2 * op1; //multiply the operands and put the result in 'result' variable
            }
            else if (e[i]=='/') //if the character in the expression is a division symbol
            {
                result = op2/op1; //divide the operands and put the result in 'result' variable
            }
            else if (e[i]=='^') //if the character in the expression is a power symbol
            {
                result = pow(op1,op2); //make op1 be raised to the power of op2 (op1^op2)
                                       //and put the result in 'result' variable
            }

            postpush(result); //push the result into the stack
        }

         i++; //increment to go through all the characters
    }

    result=postpop(); //pop the result out of the stack

    return result; //return the result of the evaluation
}

//function in which the user input is asked and the result is displayed
void postfixEV()
{
    char e[MAX]; //user input (expression) array
    int result; //result variable

    FILE *evPTR2, *evPTRin2; //file pointers

    evPTR2=fopen("output.txt","a"); //open the file using its pointer to save the output
    evPTRin2=fopen("output.txt","a"); //open the file using its pointer to save the input

    //asking the user for their input
    printf("Please enter the postfix expression (with no spaces between operands and operators): ");
    scanf("%s", e); //getting user input

    fprintf(evPTRin2, "The prefix expression you entered was: %s\n", e); //saving the input into the file
    printf("Your input was saved to output.txt.\n"); //telling the user that the input was saved
    fclose(evPTRin2); //closing the file using its pointer

    result=postfix(e); //evaluating the expression and assigning that value to result

    printf("\nResult: %d\n", result); //showing the user the result of the evaluation

    fprintf(evPTR2, "The result of the evaluation is: %d\n", result); //saving the result of the evaluation into the file
    printf("The result was saved to output.txt.\n"); //telling the user that the result was saved
    fclose(evPTR2); //closing the file using its pointer

}



