#pragma once
#include "fuzzy_element.h"
#include <vector>
#include <memory>

using namespace std;

//Класс является чистым абстрактным и представляет интерфейс для класса нечеткого множества,
//  который должен давать доступ к вектору элементов и реализовывать 4 перегрузки операторов
class IFuzzySet
{
    public:
        virtual ~IFuzzySet() {};
    
        
        //возвращает вектор элементов
        virtual vector<FuzzyElement> getVector() const = 0;

        //перегружает операторы
        virtual shared_ptr<IFuzzySet> operator+(const IFuzzySet& right) = 0;
        virtual shared_ptr<IFuzzySet> operator-(const IFuzzySet& right) = 0;
        virtual shared_ptr<IFuzzySet> operator*(const IFuzzySet& right) = 0;
        virtual shared_ptr<IFuzzySet> operator/(const IFuzzySet& right) = 0;

        //Устанавливает вектор элементов
        virtual void setVector(vector<FuzzyElement> inputVector) = 0;


};