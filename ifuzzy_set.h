#pragma once
#include <vector>
#include "fuzzy_element.h"
#include <memory>
//Класс является интерфейсом для нечетких множеств
class IFuzzySet
{
    public:
        //Функция должна возвращать вектор с содержимым множества
        virtual std::vector<FuzzyElement> getVector() = 0;
        //Реализация класса должна поддерживать 4 перегрузки арифметических операторов, возвращающих AbstractFuzzySet
        virtual std::shared_ptr<IFuzzySet> operator+(const IFuzzySet& right) = 0;
        //virtual std::shared_ptr<IFuzzySet> operator-(const IFuzzySet& right) = 0;
        //virtual std::shared_ptr<IFuzzySet> operator*(const IFuzzySet& right) = 0;
        //virtual std::shared_ptr<IFuzzySet> operator/(const IFuzzySet& right) = 0;
};