#ifndef EXPRESSION_CHEKER
#define EXPRESSION_CHEKER

struct BrNode {
	char name;
	BrNode *next;
};

struct Stack {
	std::string name;
	BrNode *head;
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


bool is_empty( Stack *s );
bool push ( char c, Stack *s );
Res pop ( Stack *s );
Res expression_is_correct ( char *c, Stack *brackets, char prew );
char* to_array(std::string s);

#endif /* end of include guard: EXPRESSION_CHEKER */
