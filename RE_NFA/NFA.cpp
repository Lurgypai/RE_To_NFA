#include "NFA.h"

#include <sstream>

NFA::NFA()
{
	//make a shared pointer default state, set it to the start and end, and store it
	start = std::make_shared<State>();
	end = start;

	states.insert(start);
}

NFA::NFA(char acceptable)
{
	//make start and end states, set the transition between them, store them
	start = std::make_shared<State>();
	end = std::make_shared<State>();

	start->addNextState(acceptable, end);

	states.insert(start);
	states.insert(end);
}

void NFA::makeUnion(const NFA& nfa2) {
	//create new star state
	auto newStart = std::make_shared<State>();
	//make it then transfer to the old start states
	newStart->addNextState(0, start);
	newStart->addNextState(0, nfa2.start);
	//make a new end state
	auto newEnd = std::make_shared<State>();
	//make the old states transfer to it
	end->addNextState(0, newEnd);
	nfa2.end->addNextState(0, newEnd);

	//set the start and end states
	start = newStart;
	end = newEnd;

	//store the new states, as well as all of the states from the other nfa. because of the way nfa's are generated, they are distinct, and we don't have to worry about the same state being added multiple times
	states.insert(newStart);
	states.insert(newEnd);
	for (auto& state : nfa2.states)
		states.insert(state);
}

void NFA::concat(const NFA& nfa2) {
	//set the end to move to the start of the other state
	end->addNextState(0, nfa2.start);
	//set the new end to the end of the other state
	end = nfa2.end;
	//store the states.
	for (auto& state : nfa2.states)
		states.insert(state);
}

void NFA::kleene() {
	//create the new start, and set its next state to the old start
	auto newStart = std::make_shared<State>();
	newStart->addNextState(0, start);
	//set the end to loop back to the newStart
	end->addNextState(0, newStart);
	//set the end and start to the new start state
	end = newStart;
	start = newStart;

	//add the new start state
	states.insert(newStart);
}

std::string NFA::serialize() {
	//prepare a string stream to write into (its more convenient then converting the ints to strings and such)
	std::stringstream ret{};

	//for every state we have
	for (auto& currState : states) {
		//if there are no states after this
		if (currState->getNextStates().empty()) {
			//print just this state, marking if its the start or end state
			std::string startStr{};
			if (currState == start)
				startStr = "S ";
			std::string finalStr{};
			if (currState == end)
				finalStr = "F ";
			//write out
			ret << startStr << finalStr << "(q" << currState->getId() << ", " << "E)\n";
		}
		//otherwise, if there are states following this
		else {
			//for every pair in the map (key is a char, value is the states that char leads to)
			for (const auto& transition : currState->getNextStates()) {
				//if the start is 0, set the appropriate symbol
				//also set the start and final markers appropriately
				char pathChar = transition.first;
				if (pathChar == 0)
					pathChar = 'E';
				std::string startStr{};
				if (currState == start)
					startStr = "S ";
				std::string finalStr{};
				if (currState == end)
					finalStr = "F ";

				//write it all out
				ret << startStr << finalStr << "(q" << currState->getId() << ", " << pathChar << ") -> ";

				//print out all the states it leads to
				for (auto i = 0; i != transition.second.size(); ++i) {
					ret << 'q' << transition.second[i]->getId();
					if (i < transition.second.size() - 1) {
						ret << ", ";
					}
					else {
						ret << '\n';
					}
				}
			}
		}
	}
	//return the streams string
	return ret.str();
}
