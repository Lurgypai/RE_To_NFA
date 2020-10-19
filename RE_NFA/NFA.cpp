#include "NFA.h"

#include <sstream>

NFA::NFA()
{
	start = std::make_shared<State>();
	end = start;

	states.insert(start);
}

NFA::NFA(char acceptable)
{
	start = std::make_shared<State>();
	end = std::make_shared<State>();

	start->addNextState(acceptable, end);

	states.insert(start);
	states.insert(end);
}

void NFA::makeUnion(const NFA& nfa2) {
	auto newStart = std::make_shared<State>();
	newStart->addNextState(0, start);
	newStart->addNextState(0, nfa2.start);
	auto newEnd = std::make_shared<State>();
	end->addNextState(0, newEnd);
	nfa2.end->addNextState(0, newEnd);

	start = newStart;
	end = newEnd;

	states.insert(newStart);
	states.insert(newEnd);
	for (auto& state : nfa2.states)
		states.insert(state);
}

void NFA::concat(const NFA& nfa2) {
	end->addNextState(0, nfa2.start);
	end = nfa2.end;
	for (auto& state : nfa2.states)
		states.insert(state);
}

void NFA::kleene() {
	auto newStart = std::make_shared<State>();
	newStart->addNextState(0, start);
	end->addNextState(0, newStart);
	end = newStart;
	start = newStart;

	states.insert(newStart);
}

std::string NFA::serialize() {
	std::stringstream ret{};

	for (auto& currState : states) {
		if (currState->getNextStates().empty()) {
			std::string startStr{};
			if (currState == start)
				startStr = "S ";
			std::string finalStr{};
			if (currState == end)
				finalStr = "F ";
			ret << startStr << finalStr << "(q" << currState->getId() << ", " << "E)\n";
		}
		else {
			for (const auto& transition : currState->getNextStates()) {
				char pathChar = transition.first;
				if (pathChar == 0)
					pathChar = 'E';
				std::string startStr{};
				if (currState == start)
					startStr = "S ";
				std::string finalStr{};
				if (currState == end)
					finalStr = "F ";

				ret << startStr << finalStr << "(q" << currState->getId() << ", " << pathChar << ") -> ";

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

	return ret.str();
}
