#pragma once
#include "BT_ReasonerNode.h"
class BT_RandomNode :
    public BT_ReasonerNode
{
public:
    void Think() override;
    ActionStatus Act() override;
    void Reset() override;
    //void SetOptions(AIConstructorBase& _constructor) override;
private:
    int runningOptionIndex;
};

