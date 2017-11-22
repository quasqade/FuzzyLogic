#pragma once
#include "ifuzzy_set.h"
#include <iostream>
#include <typeinfo>
using namespace std;
class FuzzySet : public IFuzzySet
{
    public:
        vector<FuzzyElement> getVector()
        {
            vector<FuzzyElement> vec(0);
            return vec;
        }

        shared_ptr<IFuzzySet> operator+(const IFuzzySet& right)
        {
            FuzzySet set = FuzzySet();
            shared_ptr<IFuzzySet> ptr = make_shared<FuzzySet>();
            cout << "created ptr of object type " << typeid(this).name() << std::endl;
            return ptr;
        }
        
        void derivedFoo()
        {
            cout << "called derived function" << std::endl;
        }
};