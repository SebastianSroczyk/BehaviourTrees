#include "AIBlackboard_Global.h"


AIBlackboard_Global* AIBlackboard_Global::instancePointer = nullptr;

AIBlackboard_Global* AIBlackboard_Global::getInstance()
{

	if (instancePointer == nullptr)
	{
		instancePointer = new AIBlackboard_Global();
	}

	return(instancePointer);
}