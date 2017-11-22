#include "ifuzzy_set.h"
#include "fuzzy_set.h"
#include <memory>
#include <typeinfo>
int main()
{
    std::shared_ptr<IFuzzySet> fuzzySet1 = std::make_shared<FuzzySet>();
    std::shared_ptr<IFuzzySet> fuzzySet2 = std::make_shared<FuzzySet>();
    std::shared_ptr<IFuzzySet> fuzzySet3 = *fuzzySet1+*fuzzySet2;
    std::cout << "type of fuzzySet1 is " << typeid(*fuzzySet1).name() << std::endl;
    return 0;
}