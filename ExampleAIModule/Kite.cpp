//#include "Kite.h"
//#include "ExampleAIModule.h"
#include <iostream>

using namespace SL;
using namespace SL::Behaviors;
using namespace BehaviorTree;
using namespace std;
using namespace BWAPI;

Unit closestTarget;
int distToTarget;
Unitset::iterator u;

//Kite::Kite(void)
void Kite::init(void* agent)
{
}


//Kite::~Kite(void)
Kite::Kite(Unitset::iterator vulture, Unit t)
{
	u = vulture;
	closestTarget  = t;
	distToTarget = u->getDistance(closestTarget);
}

BEHAVIOR_STATUS Kite::execute(void* agent)
{
	/*
	cout << "Fire!" << endl;
	Ship* ship = (Ship*) agent;
	Projectile* p = new Projectile();
	p->setSprite("Ammo\\test");
	p->brain = ship->projectileBrain();
	p->owner = ship;
	ship->fire(p);
	*/


	if (closestTarget != nullptr){
		if(distToTarget > 155){
			u->attack(Broodwar->getUnit(closestTarget->getID()),false);
		}
		else{
			Position pos_e = closestTarget->getPosition(); //enemy position
			Position pos_u = u->getPosition(); //our unit position
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

			//store 90 CW position
			Position right;
			right.x = evadex - torotate_x;
			right.y = evadey - torotate_y;

			//store behind position
			Position back;
			back.x = evadex;
			back.y = evadey;

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
			}
			else if(least == rightcount && u->hasPath(right)){
				u->move(right, false);
			}
			else if(least == backcount && u->hasPath(back)){
				u->move(back, false);
			}
		}
	}
	//else{
		//return BT_FAILURE;
	//}

	return BT_SUCCESS;
}
