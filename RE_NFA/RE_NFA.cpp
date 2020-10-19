
#include "NFA.h"
#include <iostream>
#include <deque>
#include <fstream>

int main(int argc, char* argv[])
{
	if (argc == 2) {

		std::deque<NFA> stack;
		std::ifstream file{};
		std::string fileName{ argv[1] };
		file.open(fileName);
		if (file.is_open()) {
			std::string line;
			while (std::getline(file, line)) {
				for (auto& c : line) {
					if (c == 'a' || c == 'b' || c == 'd' || c == 'e') {
						stack.emplace_front(NFA{ c });
					}
					else if (c == 'E') {
						stack.emplace_front(NFA{});
					}
					else if (c == '|') {
						if (stack.size() < 2) {
							std::cout << "error, insufficient input values\n";
							return 0;
						}
						NFA second = stack.front();
						stack.pop_front();
						NFA first = stack.front();
						stack.pop_front();
						first.makeUnion(second);
						stack.emplace_front(std::move(first));
					}
					else if (c == '&') {
						if (stack.size() < 2) {
							std::cout << "error, insufficient input values\n";
							return 0;
						}
						NFA second = stack.front();
						stack.pop_front();
						NFA first = stack.front();
						stack.pop_front();
						first.concat(second);
						stack.emplace_front(std::move(first));
					}
					else if (c == '*') {
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

				if (stack.size() > 1) {
					std::cout << "error, to many input values\n";
					return 0;
				}
				std::cout << stack.front().serialize() << '\n';
				State::resetIdCounter();
				stack.clear();
			}
		}
		else {
			std::cout << "error opening file \"" << fileName << "\"\n";
		}
	}
	else {
		std::cout << "incorrect number of args\n";
	}
	return 0;
}
