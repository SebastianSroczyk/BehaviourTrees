#include "AIConstructor_BT.h"
#include "AIActor_Guard.h"

bool AIConstructor_BT::Init() {


	return true;
}


/*
DefineActions creates all the possible actions that the AI can perform
*/
void AIConstructor_BT::DefineActions()
{



	// ** Patrol Action **

	//Define the function for Patrolling
	auto patrolFunction = [](AIBrainBlackboardBase& bb) -> ActionStatus {
		AIActor_Guard* actor = static_cast<AIActor_Guard*>(bb.GetActorContext());

		// Call behaviour functions here
		// return the result of the action
		return actor->Patrol();


		};


	// Link the function to an identifier
	AddActionByName("ActionPatrol", patrolFunction);


	// ** Get Patrol Path Action **

	//Define the function for  Get Patrol Path 
	auto getPatrolPathFunction = [](AIBrainBlackboardBase& bb) -> ActionStatus {
		AIActor_Guard* actor = static_cast<AIActor_Guard*>(bb.GetActorContext());

		// Call behaviour functions here
		// return the result of the action
		return actor->GetPatrolPath();



		};


	// Link the function to an identifier
	AddActionByName("ActionGetPatrolPath", getPatrolPathFunction);




	// TASK TODO - Add Additional Actions






}

void AIConstructor_BT::DefineConsiderations()
{
	// Example Consideration - Can see an enemy?
	auto cCanSeeEnemy = [](AIBrainBlackboardBase& bb) -> bool {

		bool enemySeen = (bb.GetValueInt("CanSeePlayer") == 1);
		return(enemySeen);

		};


	AddConsiderationByName("ConsiderationSeePlayer", cCanSeeEnemy);


	// TASK TODO - Add Additional Considerations


}


/*
* DefineOptions links the Options with Considerations and Actions
*/
void AIConstructor_BT::DefineOptions()
{


	// Set the Node Type for the Root Node
	rootType = AIReasonerBase::NodeType::Fallback;

	// - LEAF NODES - ACTIONS - 
	// Add any leaf nodes (actions) using AddOptionByName()
	

	AddOptionByName("OptionGetPatrolPath", "ActionGetPatrolPath");
	AddOptionByName("OptionPatrol", "ActionPatrol");


	


	// - CONTROL NODES - SUB REASONERS - 
	// Add any Control Nodes using AddControlNodeByName()
	// You do not need to create the Root, that node is already created (called "Root")

	AddControlNodeByName("OptionPatrolSeq", AIReasonerBase::Sequence);





	// -  TREE CONNECTIONS - 
	// Add connections between nodes using AddOptionsToSubReasoner()
	




	// - CONSIDERATIONS - 
	// Add any considerations to Decorators using AddConsiderationToDecorator()
	// Add any considerations to Leaf nodes using AddOptionConsideration()

	






}








// ** Helper Functions **
// these link to the AI Framework and should not be edited 


void AIConstructor_BT::AddActionByName(std::string _actionName, std::function<ActionStatus(AIBrainBlackboardBase&)> _function)
{

	//Define an action, and init with the function which will be called when the action is selected
	AIAction* _action = new AIAction();
	_action->Init(_actionName, _function);
	actions.insert({ _actionName, _action });
}

void AIConstructor_BT::AddConsiderationByName(std::string _actionName, std::function<bool(AIBrainBlackboardBase&)> _function)
{

	//Define an action, and init with the function which will be called when the action is selected
	AIConsideration* _consideration = new AIConsideration();
	_consideration->Init(_actionName, _function);
	considerations.insert({ _actionName, _consideration });
}

void AIConstructor_BT::AddOptionByName(std::string _optionName, std::string _actionName, int _priority)
{
	// create an option for action
	AIOption* _option = new AIOption();
	_option->Init(_optionName, actions[_actionName], _priority);
	options.insert({ _optionName, _option });
}

void AIConstructor_BT::AddOptionConsideration(std::string _optionName, std::string _considerationName)
{
	// create an option for action


	options[_optionName]->AddOptionConsideration(considerations[_considerationName]);
}

void AIConstructor_BT::AddControlNodeByName(std::string _subReasonerName, AIReasonerBase::NodeType _nodeType, int _priority)
{

	/// create the Action - a SubReasoner Actions
	AIActionSubReasoner* _subReasoner = new AIActionSubReasoner();

	_subReasoner->Init(_subReasonerName, nullptr);
	_subReasoner->SetReasonerType(_nodeType);
	actions.insert({ _subReasonerName, _subReasoner });

	// create the option, and link to the Action
	AIOption* _option = new AIOption();
	_option->Init(_subReasonerName, actions[_subReasonerName]);
	options.insert({ _subReasonerName, _option });


}


void AIConstructor_BT::AddOptionsToSubReasoner(std::string _subreasoner, std::string _options)
{

	subReasonerLinks.insert({ _subreasoner, _options });



}


void AIConstructor_BT::AddConsiderationToDecorator(std::string _consideration, std::string _decorator) {

	decoratorConditions.insert({ _consideration, _decorator });


}

std::vector<std::string> AIConstructor_BT::GetOptionNamesForKey(std::string _subreasoner)
{

	std::vector<std::string> _matches;
	for (std::multimap<std::string, std::string>::iterator it = subReasonerLinks.begin(); it != subReasonerLinks.end(); ++it) {

		if (it->first == _subreasoner)
		{
			_matches.push_back(it->second);
		}
	}

	return _matches;

}


std::vector<std::string> AIConstructor_BT::GetConsiderationNamesForKey(std::string _condition)
{

	std::vector<std::string> _matches;
	for (std::multimap<std::string, std::string>::iterator it = decoratorConditions.begin(); it != decoratorConditions.end(); ++it) {

		if (it->first == _condition)
		{
			_matches.push_back(it->second);
		}
	}

	return _matches;

}



std::vector<AIConsiderationBase*> AIConstructor_BT::GetConsiderationsForKey(std::string _condition)
{

	std::vector< AIConsiderationBase*> _matches;
	for (std::multimap<std::string, std::string>::iterator it = decoratorConditions.begin(); it != decoratorConditions.end(); ++it) {

		if (it->first == _condition)
		{
			_matches.push_back(considerations[it->second]);
		}
	}

	return _matches;
}