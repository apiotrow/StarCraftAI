#include "BoolDecision.h"

	BoolDecision::BoolDecision(bool b)
	{
		boolVal = b;
	}
	
	bool BoolDecision::test()
	{
		if(boolVal == true) { return true; }
		else return false;
	}