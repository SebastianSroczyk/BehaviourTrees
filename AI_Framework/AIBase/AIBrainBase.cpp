#include "AIBrainBase.h"


AIBrainBase::~AIBrainBase()
{
	delete brainBlackboard;
	delete brainReasoner;
}


AIReasonerBase* AIBrainBase::GetReasoner()
{
	return brainReasoner;
}
AIBrainBlackboardBase* AIBrainBase::GetBrainBlackboard()
{
	return brainBlackboard;
}