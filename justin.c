/*******************************************************************************
 * Name        : ONP.c
 * Author      : Michael Curry and Justin Tsang
 * Version     : 1.0
 * Date        : 2/16/2015
 * Description : Print Reverse Polish Notation of input
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARR_MAX 401
#define TRUE 1
#define FALSE 0

// Checks if operator o2 has less precedence than o1
// o1 is the next token in input
// o2 is the char at top of stack
int lessPrecedence(char o1, char o2) {
	// Return 1 if o1 has greater precedence than o2
	if ((o1 == '^') && (o2 != '^')) {
		return 1;
	}
	if (((o1 == '*') || (o1 == '/')) &&
		((o2 == '+') || (o2 == '-'))) {
		return 1;
	}
	// Return 0 means o2 has greater or equal precedence and should be pushed onto output
	return 0;
}

// Checks if the parameter, operator, is actually an operator
// Return 0 if not operator; otherwise return 1
int isOperator(char operator) {
	if ((operator == '+') || (operator == '-') ||
		(operator == '/') || (operator == '*') ||
		(operator == '^')) {
        return 1;
    }
    return 0;
}

int main() {
	int num_expressions;
	scanf("%d", &num_expressions);
	getchar();
	if (num_expressions > 100) {
		num_expressions = 100;
	}

	int i;
	char tokens[ARR_MAX];
	char stack[ARR_MAX];
	char output[ARR_MAX];
	for (i = 0; i < num_expressions; ++i) {
		int stack_top = -1, output_top = 0, token_index = 0;
		fgets(tokens, ARR_MAX, stdin);
		char token;
		while ((token = tokens[token_index++]) != '\0') {
			//Check if operand
			if ((token >= 'a') && (token <= 'z')) {
				output[output_top++] = token;
			//Check if left parenthesis
			} else if (token == '(') {
				stack[++stack_top] = token;
			//Check if operator
			} else if (isOperator(token) == TRUE) {
				//Check precedence of o2
				while ((isOperator(stack[stack_top]) == TRUE) &&
					   (lessPrecedence(token, stack[stack_top]) == FALSE)) {
					   	output[output_top++] = stack[stack_top--];
				}
				stack[++stack_top] = token;
			// Check if right parenthesis
			} else if (token == ')') {
				//Check if there are operators before the next left parenthesis
				while (stack[stack_top] != '(') {
					output[output_top++] = stack[stack_top--];
				}
				--stack_top;
			}
		}
		//If more tokens
		while (stack_top >= 0) {
			if (isOperator(stack[stack_top]) == TRUE) {
				output[output_top++] = stack[stack_top];
			}
			--stack_top;
		}
		int out;
		for (out = 0; out < output_top; ++out) {
			printf("%c", output[out]);
		}
		printf("\n");
	}
}
