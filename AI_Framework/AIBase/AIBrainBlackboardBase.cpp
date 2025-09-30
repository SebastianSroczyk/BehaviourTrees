#include "AIBrainBlackboardBase.h"

void AIBrainBlackboardBase::AddNewValue(std::string name, float data)
{
	datamap[name] = data;
}

float AIBrainBlackboardBase::GetValue(std::string name)
{
	return datamap[name];
}

int AIBrainBlackboardBase::GetAndDeleteValue(std::string name)
{
	int returnValue = datamap[name];
	datamap.erase(name);
	return returnValue;
}

void AIBrainBlackboardBase::DeleteValue(std::string name)
{

	datamap.erase(name);

}

void AIBrainBlackboardBase::EditValue(std::string name, float new_value)
{
	datamap.erase(name);
	datamap[name] = new_value;
}


AIActorBase* AIBrainBlackboardBase::GetActorContext()
{
	return actorContext;
}


void AIBrainBlackboardBase::AddNewValueVec2f(std::string name, AIMath_Global::Vector2f data)
{
	datamapVec2f[name] = data;
}

AIMath_Global::Vector2f AIBrainBlackboardBase::GetValueVec2f(std::string name)
{
	return datamapVec2f[name];
}

AIMath_Global::Vector2f AIBrainBlackboardBase::GetAndDeleteValueVec2f(std::string name)
{
	AIMath_Global::Vector2f returnValue = datamapVec2f[name];
	datamapVec2f.erase(name);
	return returnValue;
}

void AIBrainBlackboardBase::EditValueVec2f(std::string name, AIMath_Global::Vector2f new_value)
{
	
		datamapVec2f.erase(name);
		datamapVec2f[name] = new_value;
}

void AIBrainBlackboardBase::DeleteValueVec2f(std::string name) {

	datamapVec2f.erase(name);
}


void AIBrainBlackboardBase::AddNewValueIntVec(std::string name, std::vector<int> _newValue)
{
	datamapIntVec[name] = _newValue;
}

std::vector<int> AIBrainBlackboardBase::GetValueIntVec(std::string name)
{
	return datamapIntVec[name];
}

std::vector<int> AIBrainBlackboardBase::GetAndDeleteValueIntVec(std::string name)
{
	std::vector<int>returnValue = datamapIntVec[name];
	datamapIntVec.erase(name);
	return returnValue;
}

void AIBrainBlackboardBase::EditValueIntVec(std::string name,  std::vector<int> _newValue)
{

	datamapIntVec.erase(name);
	datamapIntVec[name] = _newValue;
}

void AIBrainBlackboardBase::DeleteValueIntVec(std::string name)
{
	datamapIntVec.erase(name);
}



void AIBrainBlackboardBase::AddNewValueString(std::string name, std::string new_value) {
	datamapStr[name] = new_value;
}

std::string AIBrainBlackboardBase::GetValueString(std::string name)
{
	return datamapStr[name];
}

std::string AIBrainBlackboardBase::GetAndDeleteValueString(std::string name)
{
	std::string returnValue = datamapStr[name];
	datamapIntVec.erase(name);
	return returnValue;
}


void AIBrainBlackboardBase::EditValueString(std::string name, std::string _newValue)
{
	datamapStr.erase(name);
	datamapStr[name] = _newValue;
}

void AIBrainBlackboardBase::DeleteValueString(std::string name)
{
	datamapStr.erase(name);
}


void AIBrainBlackboardBase::AddNewValueInt(std::string name, int new_value)
{
	datamapInt[name] = new_value;
}

int AIBrainBlackboardBase::GetValueInt(std::string name)
{
	return datamapInt[name];
}

int AIBrainBlackboardBase::GetAndDeleteValueInt(std::string name)
{
	int returnValue = datamapInt[name];
	datamapInt.erase(name);
	return returnValue;
}

void AIBrainBlackboardBase::EditValueInt(std::string name, int new_value)
{
	datamapInt.erase(name);
	datamapInt[name] = new_value;
}

void AIBrainBlackboardBase::DeleteValueInt(std::string name)
{
	datamapInt.erase(name);
}