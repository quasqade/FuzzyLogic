#pragma once
#include "ifuzzy_set.h"
#include "fuzzy_pair.h"
#include <iostream>
using std::vector;
using std::cout;
using std::shared_ptr;

//Перечисление типов арифметических операций
enum Operation{SUM, SUBTRACT, MULTIPLY, DIVIDE};

//Класс публично наследует интерфейс чтобы отделить интерфейс от реализации
class FuzzySet : public IFuzzySet
{
    public:
        //Конструктор
        FuzzySet();

        //Конструктор копии
        FuzzySet(const IFuzzySet& inputSet);

        //перегрузки наследований
        virtual vector<FuzzyElement> getVector() const override;
        virtual void setVector(vector<FuzzyElement> inputVector) override;
        virtual shared_ptr<IFuzzySet> operator+(const IFuzzySet& right) override;
        virtual shared_ptr<IFuzzySet> operator-(const IFuzzySet& right) override;
        virtual shared_ptr<IFuzzySet> operator*(const IFuzzySet& right) override;
        virtual shared_ptr<IFuzzySet> operator/(const IFuzzySet& right) override;


        static FuzzyPair make_pair(const FuzzyElement& a, const FuzzyElement& b, double result);
    private:
        vector<FuzzyElement> fuzzyVector;
        
        vector<FuzzyElement> getResultingVector(const IFuzzySet& right, Operation operation);
};