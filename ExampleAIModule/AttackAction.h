#ifndef AttackAction_H
#define AttackAction_H

#include "ExampleAIModule.h"
#include "DecisionTreeNode.h"
#include <string>

using namespace std;
using namespace BWAPI;
using namespace Filter;

class AttackAction : public DecisionTreeNode {
private:
	Unitset::iterator u;
	Unit targetUnit;
public:
	AttackAction(Unitset::iterator s, Unit t);
	string makeDecision();
};

#endif AttackAction_H