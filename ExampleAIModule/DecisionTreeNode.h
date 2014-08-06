#ifndef DECISIONTREENODE_H
#define DECISIONTREENODE_H

#include <string>

using namespace std;

class DecisionTreeNode {
public:
	virtual string makeDecision() = 0;
};

#endif DECISIONTREENODE_H