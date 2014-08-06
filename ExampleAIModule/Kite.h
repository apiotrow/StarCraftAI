#ifndef KITE_H_
#define KITE_H_
#include "BehaviorTree.h"
#include <iostream>
//#include "ExampleAIModule.h"

using namespace BehaviorTree;
namespace SL
{
	namespace Behaviors
	{
	/// Fire your weapon
	class Kite:public BehaviorTree::BehaviorTreeNode
	{
	public:
		BehaviorTree::BEHAVIOR_STATUS execute(void* agent);
		void init(void* agent);
		//Kite::Kite(Unitset::iterator vulture, Unit t);
		Kite::Kite(Unitset::iterator, Unit);
		const BehaviorTree::BehaviorTreeList* getChildren() const
		{
			return NULL;
		}
	};
	}

}
#endif

