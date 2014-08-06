#ifndef DECISION_H
#define DECISION_H

#include "DecisionTreeNode.h"
#include "Condition.h"
#include <string>

using namespace std;

class Decision : public DecisionTreeNode {
protected:
	DecisionTreeNode* trueNode;
	DecisionTreeNode* falseNode;
	Condition* condition;
	
public:
	DecisionTreeNode* getTrueNode();
	DecisionTreeNode* getFalseNode();
	void setTrueNode(DecisionTreeNode *node);
	void setFalseNode(DecisionTreeNode *node);
	void setCondition(Condition* C);
	//string getAction();
	
	string makeDecision();
};

#endif DECISION_H