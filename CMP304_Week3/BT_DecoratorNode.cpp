#include "BT_DecoratorNode.h"
#include "AIConstructor_BT.h"

#include "BT_FallbackNode.h"
#include "BT_SequenceNode.h"
#include <iostream>



void BT_DecoratorNode::Think()
{
	ActionStatus _currentStatus = GetStatus();
	if (_currentStatus == ActionStatus::ACTION_IDLE)
	{
		Start();

	
		
	}
	else if (_currentStatus == ActionStatus::ACTION_RUNNING)
	{
		
	}


	bool conditionsMet = true;
	for (AIConsiderationBase* c : nodeConsiderations)
	{
		bool ruleResult = c->Calculate(*actorBlackboard);

		if (!ruleResult)
		{
			conditionsMet = false;
		}
	}

	if (conditionsMet)
	{
		std::cout << "[" << actorBlackboard->GetActorContext()->GetActorID() << "] BT Log: Decorator " << reasonerID << " Conditions met, returning SUCCESS " << std::endl;

		SetStatus(ActionStatus::ACTION_SUCCESS);
	}
	else
	{
		std::cout << "[" << actorBlackboard->GetActorContext()->GetActorID() << "] BT Log: Decorator " << reasonerID << " Conditions NOT met, returning FAILURE " << std::endl;
		SetStatus(ActionStatus::ACTION_FAILURE);
	}

}


ActionStatus BT_DecoratorNode::Act()
{


	return GetStatus();
}

void BT_DecoratorNode::Reset()
{

	BT_ReasonerNode::Reset();
	selectedOption = nullptr;
	SetStatus(ActionStatus::ACTION_IDLE);
}

void BT_DecoratorNode::InitConsideration(AIConstructorBase& _constructor)
{
	AIConstructor_BT* btConstructor = static_cast<AIConstructor_BT*>(&_constructor);
	std::vector<AIConsiderationBase*> _nodeConsideratrions = btConstructor->GetConsiderationsForKey(reasonerID);

	for (int j = 0; j < _nodeConsideratrions.size(); j++)
	{
		AIConsideration* c = new AIConsideration();
		c->Init(_nodeConsideratrions[j]->GetID(), _nodeConsideratrions[j]->GetRule());
		nodeConsiderations.push_back(c);
	}

}
















void BT_DecoratorNode::SetOptions(AIConstructorBase& _constructor)
{


	InitConsideration(_constructor);



	AIConstructor_BT* btConstructor = static_cast<AIConstructor_BT*>(&_constructor);

	std::vector<std::string> _reasonerOptions = btConstructor->GetOptionNamesForKey(reasonerID);

	std::vector<AIOptionBase*> _options = _constructor.GetOptionVector(_reasonerOptions);

	for (int i = 0; i < _options.size(); i++)
	{
		AIOption* o = new AIOption();


		std::string on = typeid(*_options[i]->GetOptionAction()).name();
		std::string::size_type n = on.find("AIActionSubReasoner");




		if (n != std::string::npos)
		{

			// if the action for the option is an AIActionSubReasoner, we need to create the SubReasoner, and add its options
			AIActionSubReasoner* actionReasoner = new AIActionSubReasoner();
			actionReasoner->Init(on, nullptr);


			AIActionSubReasoner* _optionAction = static_cast<AIActionSubReasoner*>(_options[i]->GetOptionAction());

			BT_ReasonerNode* subReasoner = nullptr;
			
			if (_optionAction->GetReasonerType() == AIReasonerBase::NodeType::Decorator)
			{
				subReasoner = new BT_DecoratorNode();

			}
			else if (_optionAction->GetReasonerType() == AIReasonerBase::NodeType::Fallback)
			{
				subReasoner = new BT_FallbackNode();
			}
			else if (_optionAction->GetReasonerType() == AIReasonerBase::NodeType::Sequence)
			{
				subReasoner = new BT_SequenceNode();
			}
	
		
			
			std::string _optionName = _options[i]->GetOptionID();

			subReasoner->Init(_optionName, *actorBlackboard);

			std::vector<std::string> _suboptions = btConstructor->GetOptionNamesForKey(_optionName);

			// call the SetOptions function to add options associated with this option
			// will also crate and initalise any sub reasoner actions within them
			subReasoner->SetOptions(_constructor);

			actionReasoner->SetChildReasoner(subReasoner);

			o->Init(_options[i]->GetOptionID(), actionReasoner, _options[i]->GetPriority());

		}
		else
		{
			o->Init(_options[i]->GetOptionID(), _options[i]->GetOptionAction(), _options[i]->GetPriority());

		}


		for (int j = 0; j < _options[i]->GetOptionConsiderations().size(); j++)
		{
			AIConsideration* c = new AIConsideration();
			c->Init(_options[i]->GetOptionConsiderations()[j]->GetID(), _options[i]->GetOptionConsiderations()[j]->GetRule());
			o->AddOptionConsideration(c);
		}

		options.push_back(o);
	}

}


