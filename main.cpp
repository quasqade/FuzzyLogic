#include "ifuzzy_set.h"
#include "fuzzy_set.h"
#include <memory>
int main()
{
    std::vector<FuzzyElement> vec(0);
    FuzzyElement elem = {0.1, 5};
    vec.push_back(elem);
    elem = {0.8, 6};
    vec.push_back(elem);
    elem = {0.4, 7};
    vec.push_back(elem);
    std::shared_ptr<IFuzzySet> pFuzzySet1 = std::make_shared<FuzzySet>();
    (*pFuzzySet1).setVector(vec);
    std::shared_ptr<IFuzzySet> pFuzzySet2 = std::make_shared<FuzzySet>();

    vec.resize(0);
    elem = {0.2, 4};
    vec.push_back(elem);
    elem = {0.9, 5};
    vec.push_back(elem);
    elem = {0.3, 6};
    vec.push_back(elem);
    
    (*pFuzzySet2).setVector(vec);
    std::shared_ptr<IFuzzySet> pFuzzySet3 = std::make_shared<FuzzySet>(*(*pFuzzySet1 * *pFuzzySet2));
    
    return 0;
}