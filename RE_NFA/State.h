#ifndef STATE_H
#define STATE_H

#include <unordered_map>
#include <vector>
#include <memory>

class State {
public:

	State();
	void addNextState(char edge, std::shared_ptr<State> nextState);
	const std::unordered_map<char, std::vector<std::shared_ptr<State>>>& getNextStates() const;
	unsigned int getId() const;

	static void resetIdCounter();
private:
	std::unordered_map<char, std::vector<std::shared_ptr<State>>> nextStates;
	unsigned int id;
	static unsigned int idCounter;
};

#endif // !STATE_H
