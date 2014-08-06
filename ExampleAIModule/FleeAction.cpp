#include "FleeAction.h"

FleeAction::FleeAction(Unitset::iterator s, Unit t) {
	u = s;
	targetUnit = t;
}

string FleeAction::makeDecision() {
	Position pos_u = u->getPosition(); //our unit position
	Position pos_e = targetUnit->getPosition(); //enemy position

	int x_e = pos_e.x;
	int y_e = pos_e.y;
	int x_u = pos_u.x;
	int y_u = pos_u.y;

	//vector from us to target
	int evadex = x_u - x_e;
	int evadey = y_u - y_e;

	//position behind us
	evadex = x_u + evadex;
	evadey = y_u + evadey;

	//rotate behind->us vector 90 degrees CCW
	int torotate_x = x_u - evadex;
	int torotate_y = y_u - evadey;
	int temp_x = torotate_x;
	torotate_x = -torotate_y;
	torotate_y = temp_x;

	//store 90 CCW position
	Position left;
	left.x = evadex + torotate_x;
	left.y = evadey + torotate_y;
	left = left.makeValid();

	//store 90 CW position
	Position right;
	right.x = evadex - torotate_x;
	right.y = evadey - torotate_y;
	right = right.makeValid();

	//store behind position
	Position back;
	back.x = evadex;
	back.y = evadey;
	back = back.makeValid();

	//get list of units in each area
	Unitset lefts = Broodwar->getUnitsInRadius(left, 75);
	Unitset rights = Broodwar->getUnitsInRadius(right, 75);
	Unitset backs = Broodwar->getUnitsInRadius(back, 75);

	//store the unit counts
	int leftcount = std::distance(lefts.begin(), lefts.end());
	int rightcount = std::distance(rights.begin(), rights.end());
	int backcount = std::distance(backs.begin(), backs.end());

	//find area with least amount
	int least;
	if(rightcount < leftcount) least = rightcount;
	else least = leftcount;
	if(least < backcount){}
	else least = backcount;

	//if a path exists, move to that area
	if(least == leftcount && u->hasPath(left)){
		u->move(left, false);
		//Broodwar << "left" << std::endl;
		//if(u->isStuck()) u->move(right, false);
	}
	else if(least == rightcount && u->hasPath(right)){
		u->move(right, false);
		//Broodwar << "right" << std::endl;
		//if(u->isStuck()) u->move(left, false);
	}
	else if(least == backcount && u->hasPath(back)){
		u->move(back, false);
		//Broodwar << "back" << std::endl;
		//if(u->isStuck()) u->move(right, false);
	}

	return("fleeing");
}