#include "State.h"

//initialize default values
State::State() :
	nextStates{},
	id{ ++idCounter }
{}


void State::addNextState(char edge, std::shared_ptr<State> nextState) {
	//copy the new state into the edge vector
	nextStates[edge].push_back(nextState);
}

//this stuff is self explainatory
const std::unordered_map<char, std::vector<std::shared_ptr<State>>>& State::getNextStates() const {
	return nextStates;
}

unsigned int State::getId() const {
	return id;
}

void State::resetIdCounter() {
	idCounter = 0;
}

//definition of idCounter because its a static variable
unsigned int State::idCounter{ 0 };