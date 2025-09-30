#include "BT_ReasonerNode.h"
#include <iostream>
#include "AIConstructor_BT.h"

#include "BT_DecoratorNode.h"
#include "BT_FallbackNode.h"
#include "BT_SequenceNode.h"
#include "BT_ConcurrentNode.h"
#include "BT_RandomNode.h"


bool BT_ReasonerNode::Init(std::string _id, AIBrainBlackboardBase& _context)
{
	actorBlackboard = &_context;
	reasonerID = _id;
	return true;
}

void BT_ReasonerNode::SetStatus(ActionStatus _status)
{
	nodeStatus = _status;
}

ActionStatus BT_ReasonerNode::GetStatus()
{
	return nodeStatus;
}

void BT_ReasonerNode::Start()
{
	std::cout << "[" << actorBlackboard->GetActorContext()->GetActorID() << "] BT Log: Node " << reasonerID << " is starting " << std::endl;
	Reset();
	nodeStatus = ActionStatus::ACTION_RUNNING;
}

void BT_ReasonerNode::Reset()
{
	for (const auto& option : options)
	{
		option->GetOptionAction()->Reset();
	}
}










// - AI Framework - 



/*
SetOptions will create the options for this node based on the provided constructor
*/
void BT_ReasonerNode::SetOptions(AIConstructorBase& _constructor)
{
	AIConstructor_BT* btConstructor = static_cast<AIConstructor_BT*>(&_constructor);

	std::vector<std::string> _reasonerOptions = btConstructor->GetOptionNamesForKey(reasonerID);

	std::vector<AIOptionBase*> _options = _constructor.GetOptionVector(_reasonerOptions);

	for (int i = 0; i < _options.size(); i++)
	{
		AIOption* o = new AIOption();


		if (_options[i] == NULL)
		{
			std::cout << "ERROR  - did not find option for " << _reasonerOptions[i] << std::endl;
		}
		if (_options[i]->GetOptionAction() == NULL)
		{
			std::cout << "ERROR  - did not find action for " << _reasonerOptions[i] << std::endl;
		}


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
			else if (_optionAction->GetReasonerType() == AIReasonerBase::NodeType::Concurrent)
			{
				subReasoner = new BT_ConcurrentNode();
			}
			else if (_optionAction->GetReasonerType() == AIReasonerBase::NodeType::Random)
			{
				subReasoner = new BT_RandomNode();
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
