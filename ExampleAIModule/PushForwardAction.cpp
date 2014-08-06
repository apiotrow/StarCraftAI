#include "PushForwardAction.h"

	PushForwardAction::PushForwardAction(Unitset::iterator s, Position j) {
		u = s;
		p = j;
	}

	string PushForwardAction::makeDecision() {
		u->move(p,false);
		return("pushing forward");
	}