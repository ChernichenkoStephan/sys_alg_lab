#include <iostream>

#include "expression_is_correct.h"

// printf("is_empty: %d\n", s->head == NULL);
bool is_empty( Stack *s ) { return s->head == NULL; }

bool push ( char c, Stack *s ) {
	//memory allocated using malloc
	// printf("push\n");

	BrNode *new_node=(BrNode*)malloc(sizeof(new_node));
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
		case 0:
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
