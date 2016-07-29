#include <iostream>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <strstream>
#include <stdlib.h>

const int LENGTH_WORD = 255;
const int STACK_DEPTH = 100;

class Stack
{
    private:
        double stack_array[STACK_DEPTH];
	int stack_pointer;
		
    public:	
    	Stack()
	{
		stack_pointer = 0;
	}

        void push_stack(double *element)
        {
            assert(element);
			if (stack_pointer == STACK_DEPTH) {
				std::cout << "Stack is full" << std::endl;
			} else {
				stack_array[stack_pointer] = *element;
				stack_pointer++;
			}
        }

        double pop_stack()
        {
			if (stack_pointer == 0) { 
				std::cout << "Stack is empty" << std::endl;
				return 0;
			} else {
				stack_pointer--;
				return stack_array[stack_pointer];
			}
        }

};

Stack stack_expression;

void get_word(char * source, char * word)
{
    int i = 0;
    char * pch;
    int numsimbol;

    memset(word, 0, LENGTH_WORD);
    pch = strchr(source, ' ');
    numsimbol = pch - source + 1;

    if (pch == NULL)
        strncpy(word, source, LENGTH_WORD);
    else {
        strncpy(word, source, numsimbol - 1); // without space
        strncpy(source, source + numsimbol, LENGTH_WORD - numsimbol);
    }
}

void operation(char * line)
{
	
    char word[LENGTH_WORD];
	
    get_word(line, word);

	if (!strcmp(word,"push")) {
		double expression = strtod(line, NULL);
		stack_expression.push_stack( &expression );
	}
	
	if (!strcmp(word,"pop")) std::cout << stack_expression.pop_stack() << std::endl;
		
	if (!strcmp(word,"add")) {
		double expression = stack_expression.pop_stack() + stack_expression.pop_stack();		
		stack_expression.push_stack( &expression );
	}
	
	if (!strcmp(word,"sub")) {
		double expression = stack_expression.pop_stack() - stack_expression.pop_stack();
		stack_expression.push_stack( &expression );
	}
	
	if (!strcmp(word,"mul")) {
		double expression = stack_expression.pop_stack() * stack_expression.pop_stack();
		stack_expression.push_stack( &expression );
	}
	
	if (!strcmp(word,"div")) {
		double expression = stack_expression.pop_stack() / stack_expression.pop_stack();
		stack_expression.push_stack( &expression );
	}
	
	if (!strcmp(word,"pow")) {
		double expression = pow(stack_expression.pop_stack(), stack_expression.pop_stack());
		stack_expression.push_stack( &expression );
	}
	
	if (!strcmp(word,"sin")) {
		double expression = sin( stack_expression.pop_stack() );
		stack_expression.push_stack( &expression );
	}
	
	if (!strcmp(word,"cos")) {
		double expression = cos( stack_expression.pop_stack() );
		stack_expression.push_stack( &expression );
	}
}

bool check_end(char * line)
{
	char word[LENGTH_WORD];
	
    get_word(line, word);

	if (!strcmp(word,"end"))
		return true;
	else
		return false;
}

int main()
{
    char s[LENGTH_WORD];
    
    while (!check_end(s)) {
		std::cin.getline(s, LENGTH_WORD);	
		operation(s);
	}    
    return 0;
}

