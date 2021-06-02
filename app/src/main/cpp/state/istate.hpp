//
// Created by 17719242718 on 2021/3/15.
//

#pragma once
#include <string>


struct IState
{
    virtual std::string getStateName() const =0;
};
