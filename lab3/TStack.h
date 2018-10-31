#ifndef __TSTACK_H__
#define __TSTACK_H__

const int STACK_MAX_SIZE = 100;

template <class ElemType>
class TStack
{
	int Lii;   //last item index
	ElemType Stack[STACK_MAX_SIZE];

public:
	TStack()
	{
		Lii = -1;
		for (int i = 0; i < STACK_MAX_SIZE; i++)
			Stack[i] = {};
	}
	~TStack()
	{

	}

	bool is_full()
	{
		if (Lii >= STACK_MAX_SIZE || Lii < -1)
			throw("!Error! Stack size incorrect.");
		if (Lii == STACK_MAX_SIZE - 1)
			return 1;
		return 0;
	}

	bool is_empty()
	{
		if (Lii >= STACK_MAX_SIZE || Lii < -1)
			throw("!Error! Stack size incorrect.");
		if (Lii == -1)
			return 1;
		return 0;
	}
	void push(ElemType Element)
	{
		if (is_full())
			throw("!Error! Full Stack.");
		Lii++;
		Stack[Lii] = Element;
	}
	ElemType pop()
	{
		if (is_empty()) throw("!Error! Empty Stack.");
		Lii--;
		return Stack[Lii + 1];

	}
	ElemType top()
	{
		if (is_empty()) throw("!Error! Empty Stack.");
		return Stack[Lii];
	}
};

#endif