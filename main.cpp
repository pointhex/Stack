#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

static const int LENGTH_WORD = 255;

struct Stack
{
    static const int STACK_DEPTH = 100;

    double stack_array[STACK_DEPTH];
	int stack_pointer;

    void Stack_constructor() { stack_pointer = 0; };
    void Stack_destructor() { stack_pointer = 0; };
    void push(double *element);
    double pop();
    void dump();
};

struct Processor
{
    Stack *p_stack;

    void Processor_constructor() { p_stack = new Stack; p_stack->Stack_constructor(); };
    void Processor_destructor() { p_stack->Stack_destructor(); delete p_stack; };
    void IsOk(){ assert(p_stack); };

	void Add();
	void Sub();
	void Mul();
	void Div();
	void Pow();
	void Sin();
	void Cos();
};


int main()
{
    double element = 0;
    char command[LENGTH_WORD] = "";
    Processor *my_proc = new Processor();

    my_proc->Processor_constructor();
    my_proc->IsOk();

    while (true) {
        scanf("%s", command);
        if (!strcmp(command,"push")) {
            scanf("%lf", &element);
            my_proc->p_stack->push(&element);
        }
        if (!strcmp(command,"pop")) printf("%lf\n", my_proc->p_stack->pop());

        if (!strcmp(command,"add")) my_proc->Add();
        if (!strcmp(command,"sub")) my_proc->Sub();
        if (!strcmp(command,"mul")) my_proc->Mul();
        if (!strcmp(command,"div")) my_proc->Div();
        if (!strcmp(command,"pow")) my_proc->Pow();
        if (!strcmp(command,"sin")) my_proc->Sin();
        if (!strcmp(command,"cos")) my_proc->Cos();

		if (!strcmp(command,"end")) {
		    my_proc->p_stack->dump();
            my_proc->Processor_destructor();
            delete my_proc;
            break;
		}
	}
    return 0;
}


void Stack::push(double *element)
{
    assert(element);
    if (stack_pointer ==  Stack::STACK_DEPTH) {
        printf("Stack is full.\n");
    } else {
        stack_array[stack_pointer] = *element;
        stack_pointer++;
    }
}

double Stack::pop()
{
    if (stack_pointer == 0) {
        printf("Stack is empty.\n");
        return 0;
    } else {
        stack_pointer--;
        return stack_array[stack_pointer];
    }
}

void Stack::dump()
{
    printf("Quantity elements: %d\n", stack_pointer );
	printf("Stack size: %d\n", STACK_DEPTH);
}


void Processor::Add()
{
    double value = p_stack->pop() + p_stack->pop();
    p_stack->push(&value);
}

void Processor::Sub()
{
    double value = p_stack->pop();
    value = p_stack->pop() - value;
    p_stack->push(&value);
}

void Processor::Mul()
{
    double value = p_stack->pop() * p_stack->pop();
    p_stack->push(&value);
}

void Processor::Div()
{
    double value = p_stack->pop();
    value = p_stack->pop() / value;
    p_stack->push(&value);
}

void Processor::Pow()
{
    double value = pow(p_stack->pop(), p_stack->pop());
    p_stack->push(&value);
}

void Processor::Sin()
{
    double value = sin(p_stack->pop());
    p_stack->push(&value);
}

void Processor::Cos()
{
    double value = cos(p_stack->pop());
    p_stack->push(&value);
}

