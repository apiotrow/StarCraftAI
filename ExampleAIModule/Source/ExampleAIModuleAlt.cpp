#include "ExampleAIModule.h"
#include <iostream>

using namespace BWAPI;
using namespace Filter;

int id1 = 999;
int id2 = 999;
int id3 = 999;

void ExampleAIModule::onStart()
{
	// Hello World!
	Broodwar->sendText("Hello world!");
	//Broodwar->sendText("black sheep wall");

	// Print the map name.
	// BWAPI returns std::string when retrieving a string, don't forget to add .c_str() when printing!
	Broodwar << "The map is " << Broodwar->mapName() << "!" << std::endl;

	// Enable the UserInput flag, which allows us to control the bot and type messages.
	Broodwar->enableFlag(Flag::UserInput);

	// Uncomment the following line and the bot will know about everything through the fog of war (cheat).
	Broodwar->enableFlag(Flag::CompleteMapInformation);

	// Set the command optimization level so that common commands can be grouped
	// and reduce the bot's APM (Actions Per Minute).
	Broodwar->setCommandOptimizationLevel(2);

	// Check if this is a replay
	if ( Broodwar->isReplay() )
	{

		// Announce the players in the replay
		Broodwar << "The following players are in this replay:" << std::endl;

		// Iterate all the players in the game using a std:: iterator
		Playerset players = Broodwar->getPlayers();
		for(auto p = players.begin(); p != players.end(); ++p)
		{
			// Only print the player if they are not an observer
			if ( !p->isObserver() )
				Broodwar << p->getName() << ", playing as " << p->getRace() << std::endl;
		}

	}
	else // if this is not a replay
	{
		// Retrieve you and your enemy's races. enemy() will just return the first enemy.
		// If you wish to deal with multiple enemies then you must use enemies().
		if ( Broodwar->enemy() ) // First make sure there is an enemy
			Broodwar << "The matchup is " << Broodwar->self()->getRace() << " vs " << Broodwar->enemy()->getRace() << std::endl;
	}

}

void ExampleAIModule::onEnd(bool isWinner)
{
	// Called when the game ends
	if ( isWinner )
	{
		// Log your win here!
	}
}

void ExampleAIModule::onFrame()
{
	// Called once every game frame

	// Display the game frame rate as text in the upper left area of the screen
	Broodwar->drawTextScreen(200, 0,  "FPS: %d", Broodwar->getFPS() );
	Broodwar->drawTextScreen(200, 20, "Average FPS: %f", Broodwar->getAverageFPS() );

	// Return if the game is a replay or is paused
	if ( Broodwar->isReplay() || Broodwar->isPaused() || !Broodwar->self() )
		return;

	// Prevent spamming by only running our onFrame once every number of latency frames.
	// Latency frames are the number of frames before commands are processed.
	if ( Broodwar->getFrameCount() % Broodwar->getLatencyFrames() != 0 )
		return;

	// Iterate through all the units that we own
	Unitset myUnits = Broodwar->self()->getUnits();
	Unitset enemyUnits = Broodwar->enemy()->getUnits();

	for ( Unitset::iterator u = myUnits.begin(); u != myUnits.end(); ++u )
	{
		// Ignore the unit if it no longer exists
		// Make sure to include this block when handling any Unit pointer!
		if ( !u->exists() )
			continue;

		// Ignore the unit if it has one of the following status ailments
		if ( u->isLockedDown() || u->isMaelstrommed() || u->isStasised() )
			continue;

		// Ignore the unit if it is in one of the following states
		if ( u->isLoaded() || !u->isPowered() || u->isStuck() )
			continue;

		// Ignore the unit if it is incomplete or busy constructing
		if ( !u->isCompleted() || u->isConstructing() )
			continue;


		// Finally make the unit do some stuff!


		// If the unit is a worker unit
		if ( u->getType().isWorker() )
		{
			// if our worker is idle
			if ( u->isIdle() )
			{
				// Order workers carrying a resource to return them to the center,
				// otherwise find a mineral patch to harvest.
				if ( u->isCarryingGas() || u->isCarryingMinerals() )
				{
					u->returnCargo();
				}
				else if ( !u->getPowerUp() )  // The worker cannot harvest anything if it
				{                             // is carrying a powerup such as a flag
					// Harvest from the nearest mineral patch or gas refinery
					if ( !u->gather( u->getClosestUnit( IsMineralField || IsRefinery )) )
					{
						// If the call fails, then print the last error message
						Broodwar << Broodwar->getLastError() << std::endl;
					}

				} // closure: has no powerup
			} // closure: if idle

		}

		else if ( u->getType() == 2)
		{
			if(id1 == 999 ) id1 = u->getID();
			else if(id2 == 999 ) id2 = u->getID();
			else if(id3 == 999 ) id3 = u->getID();

			Unit closestTarget;
			int distToTarget;

			if((id1 != 999 && id1 == u->getID())){
					closestTarget = 
						u->getClosestUnit(GetType == UnitTypes::Enum::Zerg_Zergling
						 || GetType == UnitTypes::Enum::Zerg_Hatchery
						 || GetType == UnitTypes::Enum::Zerg_Drone);
					distToTarget = u->getDistance(closestTarget);
					Broodwar << closestTarget << std::endl;
			}
			else if((id2 != 999 && id2 == u->getID()) || (id3 != 999 && id3 == u->getID())){
					closestTarget = 
						u->getClosestUnit(GetType == UnitTypes::Enum::Zerg_Zergling);
					distToTarget = u->getDistance(closestTarget);
					Broodwar << closestTarget << std::endl;
			}

			if (closestTarget != nullptr){
				if(distToTarget > 165){
					u->attack(Broodwar->getUnit(closestTarget->getID()),false);
				}
				else{

					Position pos_e = closestTarget->getPosition(); //enemy position
					Position pos_u = u->getPosition(); //our unit position

					Unitset self = Broodwar->getUnitsInRadius(pos_u, 75);
					int selfcount = std::distance(lefts.begin(), lefts.end());
					if(selfcount > 4){
						bool useTech(Spider_Mine, self);
					}

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
		}
		else if ( u->getType().isResourceDepot() ) // A resource depot is a Command Center, Nexus, or Hatchery
		{

			// Order the depot to construct more workers! But only when it is idle.
			if ( u->isIdle() && !u->train(u->getType().getRace().getWorker()) )
			{
				// If that fails, draw the error at the location so that you can visibly see what went wrong!
				// However, drawing the error once will only appear for a single frame
				// so create an event that keeps it on the screen for some frames
				Position pos = u->getPosition();
				Error lastErr = Broodwar->getLastError();
				Broodwar->registerEvent([pos,lastErr](Game*){ Broodwar->drawTextMap(pos, "%c%s", Text::White, lastErr.c_str()); },   // action
					nullptr,    // condition
					Broodwar->getLatencyFrames());  // frames to run

				// Retrieve the supply provider type in the case that we have run out of supplies
				UnitType supplyProviderType = u->getType().getRace().getSupplyProvider();
				static int lastChecked = 0;

				// If we are supply blocked and haven't tried constructing more recently
				if (  lastErr == Errors::Insufficient_Supply &&
					lastChecked + 400 < Broodwar->getFrameCount() &&
					Broodwar->self()->incompleteUnitCount(supplyProviderType) == 0 )
				{
					lastChecked = Broodwar->getFrameCount();

					// Retrieve a unit that is capable of constructing the supply needed
					Unit supplyBuilder = u->getClosestUnit(  GetType == supplyProviderType.whatBuilds().first &&
						(IsIdle || IsGatheringMinerals) &&
						IsOwned);
					// If a unit was found
					if ( supplyBuilder )
					{
						if ( supplyProviderType.isBuilding() )
						{
							TilePosition targetBuildLocation = Broodwar->getBuildLocation(supplyProviderType, supplyBuilder->getTilePosition());
							if ( targetBuildLocation )
							{
								// Register an event that draws the target build location
								Broodwar->registerEvent([targetBuildLocation,supplyProviderType](Game*)
								{
									Broodwar->drawBoxMap( Position(targetBuildLocation),
										Position(targetBuildLocation + supplyProviderType.tileSize()),
										Colors::Blue);
								},
									nullptr,  // condition
									supplyProviderType.buildTime() + 100 );  // frames to run

								// Order the builder to construct the supply structure
								supplyBuilder->build( supplyProviderType, targetBuildLocation );
							}
						}
						else
						{
							// Train the supply provider (Overlord) if the provider is not a structure
							supplyBuilder->train( supplyProviderType );
						}
					} // closure: supplyBuilder is valid
				} // closure: insufficient supply
			} // closure: failed to train idle unit

		}

	} // closure: unit iterator
}

void ExampleAIModule::onSendText(std::string text)
{

	// Send the text to the game if it is not being processed.
	Broodwar->sendText("%s", text.c_str());


	// Make sure to use %s and pass the text as a parameter,
	// otherwise you may run into problems when you use the %(percent) character!

}

void ExampleAIModule::onReceiveText(BWAPI::Player player, std::string text)
{
	// Parse the received text
	Broodwar << player->getName() << " said \"" << text << "\"" << std::endl;
}

void ExampleAIModule::onPlayerLeft(BWAPI::Player player)
{
	// Interact verbally with the other players in the game by
	// announcing that the other player has left.
	Broodwar->sendText("Goodbye %s!", player->getName().c_str());
}

void ExampleAIModule::onNukeDetect(BWAPI::Position target)
{

	// Check if the target is a valid position
	if ( target )
	{
		// if so, print the location of the nuclear strike target
		Broodwar << "Nuclear Launch Detected at " << target << std::endl;
	}
	else 
	{
		// Otherwise, ask other players where the nuke is!
		Broodwar->sendText("Where's the nuke?");
	}

	// You can also retrieve all the nuclear missile targets using Broodwar->getNukeDots()!
}

void ExampleAIModule::onUnitDiscover(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitEvade(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitShow(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitHide(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitCreate(BWAPI::Unit unit)
{
	if ( Broodwar->isReplay() )
	{
		// if we are in a replay, then we will print out the build order of the structures
		if ( unit->getType().isBuilding() && !unit->getPlayer()->isNeutral() )
		{
			int seconds = Broodwar->getFrameCount()/24;
			int minutes = seconds/60;
			seconds %= 60;
			Broodwar->sendText("%.2d:%.2d: %s creates a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
		}
	}
}

void ExampleAIModule::onUnitDestroy(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitMorph(BWAPI::Unit unit)
{
	if ( Broodwar->isReplay() )
	{
		// if we are in a replay, then we will print out the build order of the structures
		if ( unit->getType().isBuilding() && !unit->getPlayer()->isNeutral() )
		{
			int seconds = Broodwar->getFrameCount()/24;
			int minutes = seconds/60;
			seconds %= 60;
			Broodwar->sendText("%.2d:%.2d: %s morphs a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
		}
	}
}

void ExampleAIModule::onUnitRenegade(BWAPI::Unit unit)
{
}

void ExampleAIModule::onSaveGame(std::string gameName)
{
	Broodwar << "The game was saved to \"" << gameName << "\"" << std::endl;
}

void ExampleAIModule::onUnitComplete(BWAPI::Unit unit)
{
}
