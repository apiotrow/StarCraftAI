#include "DecisionTreeNode.h"
#include "Decision.h"
#include "Action.h"
#include "BoolDecision.h"
#include "StringAction.h"
#include <string>
#include <iostream>

using namespace std;

int main() {

		bool raining = false;
		bool coat = false;

		Decision* decisions[3];
		
		decisions[0] = new Decision();
		decisions[1] = new Decision();
		decisions[2] = new Decision();
		
		decisions[0]->setFalseNode(decisions[1]);
		decisions[0]->setTrueNode(decisions[2]);
		decisions[0]->setCondition(new BoolDecision(raining));

		decisions[1]->setFalseNode(new StringAction("Nice day"));
		decisions[1]->setTrueNode(new StringAction("You're sweating"));
		decisions[1]->setCondition(new BoolDecision(coat));

		decisions[2]->setFalseNode(new StringAction("You're wet"));
		decisions[2]->setTrueNode(new StringAction("You're dry"));
		decisions[2]->setCondition(new BoolDecision(coat));

		cout << decisions[0]->makeDecision() << endl;
		system("pause");
	}