#include "AIActionSubReasoner.h"

bool AIActionSubReasoner::Init(std::string _id, std::function<ActionStatus(AIBrainBlackboardBase&)> _action)
{
	actionID = _id;
	action = _action;
	return true;
}

void AIActionSubReasoner::SetChildReasoner(AIReasonerBase* _child)
{
	childReasoner = _child;
}

AIReasonerBase* AIActionSubReasoner::GetChildReasoner()
{
	return childReasoner;
}

ActionStatus AIActionSubReasoner::PerformAction(AIBrainBlackboardBase& _context)
{
	// call the child reasoner - it will perform it's own decision making to decide upon the action. The status of this is returned. 
	return childReasoner->Update();
}

void AIActionSubReasoner::Reset()
{
	childReasoner->Reset();
}

void AIActionSubReasoner::SetReasonerType(AIReasonerBase::NodeType _type)
{
	reasonerType = _type;
}

AIReasonerBase::NodeType AIActionSubReasoner::GetReasonerType()
{
	return reasonerType;
}