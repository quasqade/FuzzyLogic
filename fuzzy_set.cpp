#include "fuzzy_set.h"
#include <algorithm>
#include <set>
using std::make_shared;

FuzzySet::FuzzySet()
{

}

FuzzySet::FuzzySet(const IFuzzySet& inputSet)
{
    this->setVector(inputSet.getVector());
}

shared_ptr<IFuzzySet> FuzzySet::operator+(const IFuzzySet& right)
{
    vector<FuzzyElement> result = getResultingVector(right, SUM);
    shared_ptr<IFuzzySet> ptr = make_shared<FuzzySet>();
    (*ptr).setVector(result);
    return ptr;
}

shared_ptr<IFuzzySet> FuzzySet::operator-(const IFuzzySet& right)
{
    vector<FuzzyElement> result = getResultingVector(right, SUBTRACT);
    shared_ptr<IFuzzySet> ptr = make_shared<FuzzySet>();
    (*ptr).setVector(result);
    return ptr;
}

shared_ptr<IFuzzySet> FuzzySet::operator*(const IFuzzySet& right)
{
    vector<FuzzyElement> result = getResultingVector(right, MULTIPLY);
    shared_ptr<IFuzzySet> ptr = make_shared<FuzzySet>();
    (*ptr).setVector(result);
    return ptr;
}

shared_ptr<IFuzzySet> FuzzySet::operator/(const IFuzzySet& right)
{
    vector<FuzzyElement> result = getResultingVector(right, DIVIDE);
    shared_ptr<IFuzzySet> ptr = make_shared<FuzzySet>();
    (*ptr).setVector(result);
    return ptr;
}

vector<FuzzyElement> FuzzySet::getVector() const
{
    return fuzzyVector;
}

void FuzzySet::setVector(vector<FuzzyElement> inputVector)
{
    this->fuzzyVector = inputVector;
}

vector<FuzzyElement> FuzzySet::getResultingVector(const IFuzzySet& right, Operation operation)
{
    //вектор всех возможных пар
    vector<FuzzyPair> allPairs;
    vector<double> op_results;
    //Проходим все возможные пары чисел, записывая их в вектор вместе с результатом,
    //а также записывая результаты в вектор
    for (int i = 0; i < this->getVector().size(); i++)
    {
        for (int j = 0; j < right.getVector().size(); j++)
        {
            double result=0;
            switch (operation)
            {
                case SUM:
                    result = this->getVector().at(i).value + right.getVector().at(j).value;
                    break;
                case SUBTRACT:
                    result = this->getVector().at(i).value - right.getVector().at(j).value;
                    break;
                case MULTIPLY:
                    result = this->getVector().at(i).value * right.getVector().at(j).value;
                    break;
                case DIVIDE:
                    result = this->getVector().at(i).value / right.getVector().at(j).value;
                    break;
            }

            allPairs.push_back(make_pair(this->getVector().at(i), right.getVector().at(j), result));
            op_results.push_back(result);
        }
    }

    //сортируем вектор результатов операций и убираем повторы
    std::set<double> s(op_results.begin(), op_results.end());
    op_results.assign(s.begin(), s.end());

    //объявление вектора результата
    vector<FuzzyElement> result;

    //Проходим заново все результаты операций
    for (double d : op_results)
    {
        //для каждого результата проходим вектор всех пар, записывая минимумы функций
        //принадлежностей, дающих этот результат в новый вектор
        vector<double> minima;
        for (FuzzyPair pair : allPairs)
        {
            if (pair.result==d)
            minima.push_back(pair.min_membership);
        }

        //находим максимум из минимумов
        double maxmin = *std::max_element(minima.begin(), minima.end());

        //записываем новый элемент в вектор результатов
        FuzzyElement elem = {maxmin, d};
        result.push_back(elem);
    }

    return result;
}

FuzzyPair FuzzySet::make_pair(const FuzzyElement& a, const FuzzyElement& b, double result)
{
    FuzzyPair pair = {a, b, result, std::min(a.membership, b.membership)};
    return pair;
}