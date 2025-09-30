#ifndef AI_OPTION_BASE_H
#define AI_OPTION_BASE_H

/*
CMP304/MAT501 AI Framework (2025)
*/


#pragma once
#include <string>
#include "AIConsiderationBase.h"
#include <vector>
#include "AIActionBase.h"

/*
* AIOptionBase represents one of the possible options a Reasoner can select from. Considerations can be used to determine if the option is valid for the current context. 
*/
class AIOptionBase
{
public:
	virtual bool Init(std::string, AIActionBase* _action, int _priority = 0) = 0;
	void AddOptionConsideration(AIConsiderationBase* _consideration);
	AIActionBase* GetOptionAction();
	std::vector<AIConsiderationBase*> GetOptionConsiderations();
	std::string GetOptionID();
	int GetPriority();

protected:
	AIActionBase* optionAction;
	std::vector<AIConsiderationBase*> optionConsiderations;
	std::string optionID;
	int priority;
};



#endif //!AI_OPTION_BASE_H