#include "AIActorBase.h"
#include "AIBrainBase.h"


void AIActorBase::Update(float _dt)
{
	brain->Update();

}

void AIActorBase::PreTransition()
{

}


void AIActorBase::AddBBValue(std::string _key, float _value)
{
	brain->GetBrainBlackboard()->AddNewValue(_key, _value);

}
void AIActorBase::EditBBValue(std::string _key, float _newValue)
{
	brain->GetBrainBlackboard()->EditValue(_key, _newValue);
}
void AIActorBase::DeleteBBValue(std::string _key)
{
	brain->GetBrainBlackboard()->DeleteValue(_key);
}

float AIActorBase::GetBBValue(std::string _key)
{
	return brain->GetBrainBlackboard()->GetValue(_key);
}


void AIActorBase::AddBBValueVec2f(std::string _key, AIMath_Global::Vector2f  _value)
{
	brain->GetBrainBlackboard()->AddNewValueVec2f(_key, _value);

}
void AIActorBase::EditBBValueVec2f(std::string _key, AIMath_Global::Vector2f  _newValue)
{
	brain->GetBrainBlackboard()->EditValueVec2f(_key, _newValue);
}
void AIActorBase::DeleteBBValueVec2f(std::string _key)
{
	brain->GetBrainBlackboard()->DeleteValueVec2f(_key);
}

AIMath_Global::Vector2f  AIActorBase::GetBBValueVec2f(std::string _key)
{
	return brain->GetBrainBlackboard()->GetValueVec2f(_key);
}



void AIActorBase::AddBBValueIntVec(std::string _key, std::vector<int>  _value)
{
	brain->GetBrainBlackboard()->AddNewValueIntVec(_key, _value);

}

void AIActorBase::EditBBValueIntVec(std::string _key, std::vector<int>  _newValue)
{
	brain->GetBrainBlackboard()->EditValueIntVec(_key, _newValue);
}

void AIActorBase::DeleteBBValueIntVec(std::string _key)
{
	brain->GetBrainBlackboard()->DeleteValueIntVec(_key);
}

std::vector<int>  AIActorBase::GetBBValueIntVec(std::string _key)
{
	return brain->GetBrainBlackboard()->GetValueIntVec(_key);
}


void AIActorBase::AddBBValueString(std::string _key, std::string _value) {
	brain->GetBrainBlackboard()->AddNewValueString(_key, _value);
}

void AIActorBase::EditBBValueString(std::string _key, std::string _newValue) {
	brain->GetBrainBlackboard()->EditValueString(_key, _newValue);
}

void AIActorBase::DeleteBBValueString(std::string _key) {
	brain->GetBrainBlackboard()->DeleteValueString(_key);
}

std::string AIActorBase::GetBBValueString(std::string _key) {
	return brain->GetBrainBlackboard()->GetValueString(_key);
}



void AIActorBase::AddBBValueInt(std::string _key, int _value)
{
	brain->GetBrainBlackboard()->AddNewValueInt(_key, _value);
}
void AIActorBase::EditBBValueInt(std::string _key, int _newValue)
{
	brain->GetBrainBlackboard()->EditValueInt(_key, _newValue);
}
void AIActorBase::DeleteBBValueInt(std::string _key)
{
	brain->GetBrainBlackboard()->DeleteValueInt(_key);
}
int AIActorBase::GetBBValueInt(std::string _key)
{
	return brain->GetBrainBlackboard()->GetValueInt(_key);
}



std::string AIActorBase::GetActorID()
{
	return actorID;
}