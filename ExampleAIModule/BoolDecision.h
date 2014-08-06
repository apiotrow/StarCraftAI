#ifndef BOOLDECISION_H
#define BOOLDECISION_H

#include "DecisionTreeNode.h"
#include "Condition.h"

class BoolDecision : public Condition {
private:
	bool boolVal;
	
public:
	BoolDecision(bool b);
	bool test();
};

#endif BOOLDECISION_H