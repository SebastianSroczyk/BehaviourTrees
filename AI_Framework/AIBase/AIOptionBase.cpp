#include "AIOptionBase.h"


AIActionBase* AIOptionBase::GetOptionAction()
{
	return(optionAction);
}

void AIOptionBase::AddOptionConsideration(AIConsiderationBase* _consideration)
{
	optionConsiderations.push_back(_consideration);
}


std::vector<AIConsiderationBase*> AIOptionBase::GetOptionConsiderations()
{
	return optionConsiderations;
}

std::string AIOptionBase::GetOptionID()
{
	return optionID;
}

int AIOptionBase::GetPriority()
{
	return priority;
}