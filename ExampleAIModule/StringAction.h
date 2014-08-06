#ifndef STRINGACTION_H
#define STRINGACTION_H

//#include "Action.h"
#include "DecisionTreeNode.h"
#include <string>

using namespace std;

class StringAction : public DecisionTreeNode {
private:
	string S;
public:
	StringAction(string s);
	string makeDecision();
};

#endif STRINGACTION_H