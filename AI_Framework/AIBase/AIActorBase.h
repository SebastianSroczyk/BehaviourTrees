
#ifndef AI_ACTOR_BASE_H
#define AI_ACTOR_BASE_H
#include <string>
#include "AIReasonerBase.h"
#include "AIConstructorBase.h"
class AIBrainBase;

/*
CMP304/MAT501 AI Framework (2025)
*/


#pragma once
/*
AIActorBase represents an actor or entity in the game scene that uses AI to make decisions
*/
class AIActorBase
{
public:
	virtual bool Init(std::string _id, AIConstructorBase& _constructor) = 0;

	// called each frame or decision point to make and carry out a decision
	virtual void Update(float _dt);
	virtual void PreTransition();

	void AddBBValue(std::string _key, float _value);
	void EditBBValue(std::string _key, float _newValue);
	void DeleteBBValue(std::string _key);
	float GetBBValue(std::string _key);

	void AddBBValueVec2f(std::string _key, AIMath_Global::Vector2f  _value);
	void EditBBValueVec2f(std::string _key, AIMath_Global::Vector2f  _newValue);
	void DeleteBBValueVec2f(std::string _key);
	AIMath_Global::Vector2f  GetBBValueVec2f(std::string _key);

	void AddBBValueIntVec(std::string _key, std::vector<int>  _value);
	void EditBBValueIntVec(std::string _key, std::vector<int>  _newValue);
	void DeleteBBValueIntVec(std::string _key);
	std::vector<int> GetBBValueIntVec(std::string _key);

	void AddBBValueString(std::string _key, std::string _value);
	void EditBBValueString(std::string _key, std::string _newValue);
	void DeleteBBValueString(std::string _key);
	std::string GetBBValueString(std::string _key);


	void AddBBValueInt(std::string _key,int _value);
	void EditBBValueInt(std::string _key, int _newValue);
	void DeleteBBValueInt(std::string _key);
	int GetBBValueInt(std::string _key);

	std::string GetActorID();


protected:
	std::string actorID;
	AIBrainBase* brain;
};

#endif // !AI_ACTOR_BASE_H