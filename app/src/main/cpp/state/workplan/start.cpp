//
// Created by 17719242718 on 2021/3/15.
//

#include <iostream>
#include "configuring.hpp"
#include "idle.hpp"

using namespace std;

Start::Start()
{
    cout << "Enter Start." << endl;
}

Start::~Start()
{
    cout << "Exit Start" << endl;
}

string Start::getStateName() const
{
    return string("Start");
}

result start::react(const EvStart & evStart)
{
    cout << "Start::react( const EvStart & evStart )" << endl;
    return transit< Configuring >();
}
