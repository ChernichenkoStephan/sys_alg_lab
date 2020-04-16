#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstdint>
#include <vector>
#include <ctime>
#include <chrono>
#include <limits.h>


long factorial(int n) {
	if ( n == 0 ) { return 1; }
	return ( n * factorial(n - 1) );
}

long power(long num, int degree) {
	if (degree - 1 == 0) { return num; }
	num *= power(num, degree - 1 );
	return num;
}

long f_solver(int n) {
	return power(2, n) * factorial( n - 1 );
}

/* ---------------- Task 1 ---------------- */

struct Node {
	char name;
	Node *next;
};

struct Stack {
	std::string name;
	Node *head;
};

struct Res {
	bool is_empty;
	bool is_correct;
	char character;

	Res(bool e, bool c, char ch) {
		is_empty = e;
		is_correct = c;
		character = ch;
    }
	Res() {
		is_empty = false;
		is_correct = false;
		character = '\0';
    }
};

// printf("is_empty: %d\n", s->head == NULL);
bool is_empty( Stack *s ) { return s->head == NULL; }

bool push ( char c, Stack *s ) {
	//memory allocated using malloc
	// printf("push\n");

	Node *new_node=(Node*)malloc(sizeof(new_node));
	new_node->name = c;
	new_node->next = NULL;
    if(new_node == NULL) { return false; }
	if (s->head == NULL) {
		s->head = new_node;
		return true;
	}
	new_node->next = s->head;
	s->head = new_node;
	return true;
}

Res pop ( Stack *s ) {
	// if stack is empty
	if ( s->head == NULL ) { return Res(true, false, '\0'); }
	// if it is the last one
	if ( s->head->next == NULL ) {
		Res r = Res(true, true, s->head->name);
		s->head = NULL;
		return r;
	}
	s->head = s->head->next;

	return Res(false, true, s->head->name);
}

Res expression_is_correct ( char *c, Stack *brackets, char prew ) {
	Res r = Res();
	// printf("%c\n", *c);
	switch (*c) {
		case '(':
			// if expression is correct but stack is overloaded
			if (!push(*c, brackets)) { return Res(true, true, '\0'); }
			break;
		case '*':
			// if expression isn't correct, because invalid operator
			if (*c == prew) { return Res(false, false, '\0'); }
			break;
		case '/':
			// if expression isn't correct, because invalid operator
			if (*c == prew) { return Res(false, false, '\0'); }
			break;
		case '+':
			// if expression isn't correct, because invalid operator
			if (*c == prew) { return Res(false, false, '\0'); }
			break;
		case ')':
			// if expression isn't correct, because num of opened brackets isn't equal to closed
			r = pop(brackets);
			if (r.is_empty && !r.is_correct) { return Res(true, false, '\0'); }
			break;
		case '#':
			// if it is last character
			return Res(is_empty(brackets), is_empty(brackets), '\0');
		case ' ':
			// if it is last entered character
			return Res(is_empty(brackets), is_empty(brackets), '\0');
		default:
			break;
	}
	return expression_is_correct( c + 1, brackets, *c);
}

char* to_array(std::string s) {
	char *e = (char*)malloc(sizeof(e) * (s.size() + 1));
	s.copy(e, s.size() + 1);
	e[s.size()] = '\0';
	return e;
}

bool memory_clear(Stack *brackets) {

}


int main(int argc, char **argv) {

    system("clear");

	std::string str_exp;
	std::string str_exp1 = "a+b+((c*d)#";
	std::string str_exp2 = "a+b+(c*d)#";
	std::string str_exp3 = "a+b+(c*d))#";
	Stack brackets = Stack();
	Stack brackets1 = Stack();
	Stack brackets2 = Stack();
	Stack brackets3 = Stack();

	std::cout << "Enter expresiion" << '\n';
	std::cin >> str_exp;
	char *expression = to_array(str_exp);
	char *expression1 = to_array(str_exp1);
	char *expression2 = to_array(str_exp2);
	char *expression3 = to_array(str_exp3);

	std::cout << "Entered expression: ";
	std::cout << expression << '\n';
	std::cout << "Expression is " << (expression_is_correct(expression, &brackets, '\0' ).is_correct ? "\033[0;32m correct \033[0m" : "\033[0;31mnot correct\033[0m") << '\n';

	std::cout << "Test expression1: ";
	std::cout << expression1 << '\n';
	std::cout << "Expression is " << (expression_is_correct(expression1, &brackets1, '\0' ).is_correct ? "\033[0;32m correct \033[0m" : "\033[0;31mnot correct\033[0m") << '\n';

	std::cout << "Test expression2: ";
	std::cout << expression2 << '\n';
	std::cout << "Expression is " << (expression_is_correct(expression2, &brackets2, '\0' ).is_correct ? "\033[0;32m correct \033[0m" : "\033[0;31mnot correct\033[0m") << '\n';

	std::cout << "Test expression3: ";
	std::cout << expression3 << '\n';
	std::cout << "Expression is " << (expression_is_correct(expression3, &brackets3, '\0' ).is_correct ? "\033[0;32m correct \033[0m" : "\033[0;31mnot correct\033[0m") << '\n';

	free(expression1);
	free(expression2);
	free(expression3);
	// printf("num: %d\n", num);
	// num = f_solver(5);
	// printf("num: %d\n", num);


    return 0;
}
