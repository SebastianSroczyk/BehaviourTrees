#pragma once
#ifndef AI_BRAIN_BASE_H
#define AI_BRAIN_BASE_H

/*
CMP304/MAT501 AI Framework (2025)
*/


#include "AIReasonerBase.h"
#include "AIBrainBlackboardBase.h"
#include "AIConstructorBase.h"
/*
AIBrainBase represents an the brain of an Action, containing the information needed to make decisions (brainBlackboard) and the logic for making a decision (brainReasoner). 
*/
class AIBrainBase
{
public:
	~AIBrainBase();
	virtual bool Init(AIConstructorBase& _constructor, AIActorBase& _actorContext) = 0;
	virtual void Update() = 0;

	AIReasonerBase* GetReasoner();
	AIBrainBlackboardBase* GetBrainBlackboard();
protected:
	AIReasonerBase* brainReasoner;
	AIBrainBlackboardBase* brainBlackboard;
};

#endif // !AI_BRAIN_BASE_H