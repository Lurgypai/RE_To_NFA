#ifndef NFA_H
#define NFA_H

#include <memory>
#include <string>
#include <set>
#include "State.h"


class NFA {
public:
	// an nfa accepting the empty string
	NFA();
	// an nfa accepting char acceptable
	NFA(char acceptable);

	//make this NFA into a union with the provided
	void makeUnion(const NFA& nfa2);

	//concatenate with provided nfa
	void concat(const NFA& nfa2);

	//make us into new nfa under kleene closure
	void kleene();

	std::string serialize();
private:

	std::shared_ptr<State> start;
	std::shared_ptr<State> end;

	std::set<std::shared_ptr<State>> states;
};
#endif // !NFA_H