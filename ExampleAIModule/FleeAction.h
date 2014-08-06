#ifndef FleeAction_H
#define FleeAction_H

#include "ExampleAIModule.h"
#include "DecisionTreeNode.h"
#include <string>

using namespace std;
using namespace BWAPI;
using namespace Filter;

class FleeAction : public DecisionTreeNode {
private:
	Unitset::iterator u;
	Unit targetUnit;
public:
	FleeAction(Unitset::iterator s, Unit t);
	string makeDecision();
};

#endif FleeAction_H