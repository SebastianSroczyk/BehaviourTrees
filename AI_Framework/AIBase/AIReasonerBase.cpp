#include "AIReasonerBase.h"
#include <iostream>

void AIReasonerBase::ClearOptions()
{
	options.clear();
}


AIOptionBase* AIReasonerBase::GetSelectedOption()
{
	return selectedOption;
}

ActionStatus AIReasonerBase::Update()
{
	Sense();
	Think();
	return Act();

}

void AIReasonerBase::Sense()
{

}


ActionStatus AIReasonerBase::Act()
{

	if (selectedOption == nullptr)
	{
		std::cout << "WARNING: Null Selected option, no action taken. " << std::endl;
		return ActionStatus::ACTION_FAILURE;
	}

	return selectedOption->GetOptionAction()->PerformAction(*actorBlackboard);

}


void AIReasonerBase::Reset()
{

}

AIOptionBase* AIReasonerBase::GetOptionByName(std::string _name)
{
	for (auto const option : options)
	{
		if (option->GetOptionID() == _name)
		{
			return option;
		}
	}

	return nullptr;

}

void AIReasonerBase::AddOption(AIOptionBase* _option)
{
	options.push_back(_option);
}
