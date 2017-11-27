#pragma once
#include "fuzzy_element.h"
//Структура представляет ссылки на пару нечетких чисел, результат арифметической операции над ними и минимум функции принадлежности
struct FuzzyPair
{
    const FuzzyElement& a;
    const FuzzyElement& b;
    double result;
    double min_membership;
};