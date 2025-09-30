#include "AIActionBase.h"



ActionStatus AIActionBase::PerformAction(AIBrainBlackboardBase& _context)
{
	return action(_context);
}

void AIActionBase::Reset()
{

}

