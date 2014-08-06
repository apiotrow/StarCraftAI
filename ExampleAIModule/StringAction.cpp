#include "StringAction.h"

	StringAction::StringAction(string s) {
		S = s;
	}

	string StringAction::makeDecision() {
		return S;
	}