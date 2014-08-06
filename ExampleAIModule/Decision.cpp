#include "Decision.h"

	DecisionTreeNode* Decision::getTrueNode() { return trueNode; }
	DecisionTreeNode* Decision::getFalseNode() { return falseNode; }
	void Decision::setTrueNode(DecisionTreeNode* node) { trueNode = node; }
	void Decision::setFalseNode(DecisionTreeNode* node) { falseNode = node; }
	void Decision::setCondition(Condition* C) { condition = C; }
	/*
	string Decision::getAction() { //pointless method so DecisionTreeNode can call getAction
		return " ";
	}
	*/
	
	string Decision::makeDecision() {
		if(condition->test() == true) {
			return trueNode->makeDecision();
		}
		else return falseNode->makeDecision();
	}