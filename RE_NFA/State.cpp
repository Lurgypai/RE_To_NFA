#include "State.h"

State::State() :
	nextStates{},
	id{ ++idCounter }
{}

void State::addNextState(char edge, std::shared_ptr<State> nextState) {
	nextStates[edge].push_back(nextState);
}

const std::unordered_map<char, std::vector<std::shared_ptr<State>>>& State::getNextStates() const {
	return nextStates;
}

unsigned int State::getId() const {
	return id;
}

void State::resetIdCounter() {
	idCounter = 0;
}

unsigned int State::idCounter{ 0 };