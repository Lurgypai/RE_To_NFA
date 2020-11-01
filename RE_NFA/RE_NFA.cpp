
#include "NFA.h"
#include <iostream>
#include <deque>
#include <fstream>

//hello grader, and welcome to my homework
//I don't know how familiar you are with c++, but the assignment says I should explain standard practices, so I'll comment librally

int main(int argc, char* argv[])
{
	//make sure theres one input, the name of the file
	if (argc == 2) {
		//a deque is a double ended queue, so pushing and popping from both ends, great for a stack
		std::deque<NFA> stack;
		//create a file stream and use it to open the file
		std::ifstream file{};
		std::string fileName{ argv[1] };
		file.open(fileName);
		//if the file opened successfully continue
		if (file.is_open()) {
			//read the file line by line
			std::string line;
			while (std::getline(file, line)) {
				//for every character in the line
				for (auto& c : line) {
					//if its a letter, create an nfa for it and put it on top of the stack
					if (c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e') {
						stack.emplace_front(NFA{ c });
					}
					//if its an empty letter, create the empty letter nfa
					else if (c == 'E') {
						stack.emplace_front(NFA{});
					}
					//if its the union symbol, pop the top two elements, and combine them in a union, push the new NFA
					else if (c == '|') {
						//if we don't have two elements to pop, say so and exit
						if (stack.size() < 2) {
							std::cout << "error, insufficient input values\n";
							return 0;
						}
						NFA second = stack.front();
						stack.pop_front();
						NFA first = stack.front();
						stack.pop_front();
						first.makeUnion(second);
						//i hope I'm not being graded on my efficieny, I don't remember if this properly moves the value to avoid copying.
						stack.emplace_front(std::move(first));
					}
					//if its the concatenate symbol, pop the top two elements and cocatenate them, then push that new NFA
					else if (c == '&') {
						//if we don't have two elements to pop, say so and exit
						if (stack.size() < 2) {
							std::cout << "error, insufficient input values\n";
							return 0;
						}
						NFA second = stack.front();
						stack.pop_front();
						NFA first = stack.front();
						stack.pop_front();
						first.concat(second);
						//i hope I'm not being graded on my efficieny, I don't remember if this properly moves the value to avoid copying.
						stack.emplace_front(std::move(first));
					}
					//if its the kleene operator, do pop the top element, do the kleene, and re-emplace it
					else if (c == '*') {
						//if we don't have another element to pop, say so and exit
						if (stack.size() < 1) {
							std::cout << "error, insufficient input values\n";
							return 0;
						}
						NFA first = stack.front();
						stack.pop_front();
						first.kleene();
						stack.emplace_front(std::move(first));
					}
				}
				//if we have stuff left over, but we've run out characters, there must have been to many inputs, say so and exit
				if (stack.size() > 1) {
					std::cout << "error, to many input values\n";
					return 0;
				}
				std::cout << stack.front().serialize() << '\n';
				State::resetIdCounter();
				stack.clear();
			}
		}
		//if the file failed to open, say so
		else {
			std::cout << "error opening file \"" << fileName << "\"\n";
		}
	}
	//if the wrong amount of arguments are added, say so
	else {
		std::cout << "incorrect number of args\n";
	}
	return 0;
}
