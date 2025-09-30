#pragma once
#include "../AI_Framework/framework.h"
class AIConstructor_BT :
    public AIConstructorBase
{
public:


	bool Init() override;
	void DefineActions() override;
	void DefineConsiderations() override;
	void DefineOptions() override;

	AIOptionBase* GetOptionByName(std::string _optionName);


	std::vector<std::string> GetOptionNamesForKey(std::string _subreasoner);
	std::vector<std::string> GetConsiderationNamesForKey(std::string _condition);
	std::vector<AIConsiderationBase*> GetConsiderationsForKey(std::string _condition);
	AIReasonerBase::NodeType rootType;

private:
	void AddOptionByName(std::string _optionName, std::string _actionName, int _priority = 0);
	void AddConsiderationByName(std::string _actionName, std::function<bool(AIBrainBlackboardBase&)> _function);
	void AddActionByName(std::string _actionName, std::function<ActionStatus(AIBrainBlackboardBase&)> _action);
	void AddOptionConsideration(std::string _optionName, std::string _considerationName);

	void AddControlNodeByName(std::string _subReasonerName, AIReasonerBase::NodeType _nodeType, int _priority = 0);
	void AddOptionsToSubReasoner(std::string _subreasoner, std::string _options);
	void AddConsiderationToDecorator(std::string _consideration, std::string _decorator);

	std::multimap<std::string, std::string> subReasonerLinks;
	std::multimap<std::string, std::string> decoratorConditions;


};

