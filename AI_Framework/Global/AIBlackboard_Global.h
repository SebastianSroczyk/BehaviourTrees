

#ifndef AI_BLACKBOARD_GLOBAL_H
#define AI_BLACKBOARD_GLOBAL_H

/*
CMP304/MAT501 AI Framework (2025)
*/


#pragma once
class AIBlackboard_Global
{

public:

	AIBlackboard_Global(const AIBlackboard_Global& obj) = delete;

	static AIBlackboard_Global* getInstance();

	void setValue(int val) { value_ = val; }
	int getValue() {
		return value_;
	}


protected:
	int value_;


private:

	static AIBlackboard_Global* instancePointer;
	AIBlackboard_Global() :value_(0) {}



};

#endif //!AI_BLACKBOARD_GLOBAL_H

