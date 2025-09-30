
#ifndef AI_BRAIN_BB_BASE_H
#define AI_BRAIN_BB_BASE_H

/*
CMP304/MAT501 AI Framework (2025)
*/


class AIActorBase;

#include <map>
#include <vector>
#include <string>
#include "../Global/AIMath_Global.h"

#pragma once

/*
* AIBrainBlackboardBase holds all data reqiured for the Reasoner to make a decision, including the entity this reasoner belongs to
*/
class AIBrainBlackboardBase
{
public:
	virtual bool Init(AIActorBase& _context) = 0;
	AIActorBase* GetActorContext();
	void AddNewValue(std::string name, float data);
	float GetValue(std::string name);
	int GetAndDeleteValue(std::string name);
	void EditValue(std::string name, float new_value);
	void DeleteValue(std::string name);

	void AddNewValueVec2f(std::string name, AIMath_Global::Vector2f data);
	AIMath_Global::Vector2f GetValueVec2f(std::string name);
	AIMath_Global::Vector2f GetAndDeleteValueVec2f(std::string name);
	void EditValueVec2f(std::string name,  AIMath_Global::Vector2f new_value);
	void DeleteValueVec2f(std::string name);

	void AddNewValueIntVec(std::string name, std::vector<int> new_value);
	std::vector<int> GetValueIntVec(std::string name);
	std::vector<int> GetAndDeleteValueIntVec(std::string name);
	void EditValueIntVec(std::string name, std::vector<int>  new_value);
	void DeleteValueIntVec(std::string name);

	void AddNewValueString(std::string name, std::string new_value);
	std::string GetValueString(std::string name);
	std::string GetAndDeleteValueString(std::string name);
	void EditValueString(std::string name, std::string);
	void DeleteValueString(std::string name);

	void AddNewValueInt(std::string name, int new_value);
	int GetValueInt(std::string name);
	int GetAndDeleteValueInt(std::string name);
	void EditValueInt(std::string name, int new_value);
	void DeleteValueInt(std::string name);

protected:
	std::map<std::string, float> datamap;
	std::map<std::string, AIMath_Global::Vector2f> datamapVec2f;
	std::map<std::string, std::vector<int> > datamapIntVec;
	std::map<std::string, std::string > datamapStr;
	std::map<std::string, int> datamapInt;

	AIActorBase* actorContext;
};

#endif //!AI_BRAIN_BB_BASE_H