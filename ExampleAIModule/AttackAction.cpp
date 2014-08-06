#include "AttackAction.h"

	AttackAction::AttackAction(Unitset::iterator s, Unit t) {
		u = s;
		targetUnit = t;
	}

	string AttackAction::makeDecision() {
		u->attack(Broodwar->getUnit(targetUnit->getID()),false);
		//u->patrol(targetUnit->getPosition(),false);
		return("attacking");
	}