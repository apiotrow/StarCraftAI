#ifndef PushForwardAction_H
#define PushForwardAction_H

#include "ExampleAIModule.h"
#include "DecisionTreeNode.h"
#include <string>

using namespace std;
using namespace BWAPI;
using namespace Filter;

class PushForwardAction : public DecisionTreeNode {
private:
	Unitset::iterator u;
	Position p;
public:
	PushForwardAction(Unitset::iterator s, Position j);
	string makeDecision();
};

#endif PushForwardAction_H