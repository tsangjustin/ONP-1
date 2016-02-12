#include <stdio.h>
#include <string.h>

int isOperator(char c){
    if (c == '+' || c == '-' || c == '/' || c == '*' || c == '^'){
        return 1;
    }
    else{
        return 0;
    }
}

int precedenceIsGreater(char op1, char op2){    // if op1 has greater precedence than 2
    if (op1 == '^' && op2 != '^'){
        return 1;
    }
    if (op1 == '*' || op1 == '/'){
        if (op2 == '+' || op2 == '-') {
            return 1;
        }
    }
    return 0;
}

int main() {

    int num;
    scanf("%d\n", &num);  // get number of expression
    char output[401], stack[401], input[401]; 
    int outputTop = -1;

    while (num > 0) {
		outputTop = -1;
        int stackTop = -1;
        int curr = 0;
        fgets(input, 401, stdin);    // take input
        while (input[curr] != '\0') {   // also can use "\0"
            if (input[curr] == '(') {
                stack[++stackTop] = input[curr];
            }
            else if (isOperator(input[curr]) == 1) {
                while (isOperator(stack[stackTop]) == 1 && 
					(precedenceIsGreater(stack[stackTop], input[curr]) == 1)){
                        output[++outputTop] = stack[stackTop];
                        stackTop--;
                }
                stack[++stackTop] = input[curr];
            }
            else if (input[curr] == ')'){
                while(stack[stackTop] != '('){
                    output[++outputTop] = stack[stackTop];
                    stackTop--;
                }
                stackTop--;
            }
            else{   // operand case
                output[++outputTop] = input[curr];
            }
            ++curr;
        }
        while(stackTop >= 0){
            output[++outputTop] = stack[stackTop];
            stackTop--;
        }
        --num;
        int i = 0;
		while(i <= outputTop){
			printf("%c", output[i]);
			++i;
		}
		printf("\n");
    }

    return 0;
}
