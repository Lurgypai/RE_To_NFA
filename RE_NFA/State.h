#ifndef STATE_H
#define STATE_H

#include <unordered_map>
#include <vector>
#include <memory>

class State {
public:
	//constructor
	State();
	//add a new next state to the character path described
	void addNextState(char edge, std::shared_ptr<State> nextState);
	//get the map of all next states as a const reference
	const std::unordered_map<char, std::vector<std::shared_ptr<State>>>& getNextStates() const;
	//get the id of this state
	unsigned int getId() const;

	static void resetIdCounter();
private:
	//if you haven't done c++, we've got a hashmap, where the keys are chars, and the values are dynamic arrays of smart pointers (shared pointers as I wanted it to be simple. They'll automatically deallocate when the last shared pointer is destroyed) 
	std::unordered_map<char, std::vector<std::shared_ptr<State>>> nextStates;
	//id and id counter
	unsigned int id;
	static unsigned int idCounter;
};

#endif // !STATE_H
