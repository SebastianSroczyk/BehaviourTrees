#include "AIConsiderationBase.h"


bool AIConsiderationBase::Init(std::string _id, std::function<bool(AIBrainBlackboardBase&)> _rule) {


	considerationID = _id;
	rule = _rule;
	return true;
}


bool AIConsiderationBase::Calculate(AIBrainBlackboardBase& _bb) {

	return rule(_bb);

}


std::string AIConsiderationBase::GetID()
{
	return considerationID;
}

std::function<bool(AIBrainBlackboardBase&)> AIConsiderationBase::GetRule()
{
	return rule;
}
