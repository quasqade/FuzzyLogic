#include "ifuzzy_set.h"
#include "fuzzy_set.h"
#include <memory>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using std::cout;
using std::vector;

//Прототип парсера ввода
vector<FuzzyElement> parseInput(std::string inputString);

int main()
{
    //Интерфейс пользователя

    //Ввод множеств
    cout << "Введите входные нечёткие множества, над которыми нужно выполнить операции. Для прекращения ввода нажмите Enter." << std::endl;


    vector<FuzzySet> inputSets;

    while (true)
    {
        cout << "Введите нечёткое множество в формате m1/v1, m2/v2, ..., mN/vN" << std::endl;
        vector<FuzzyElement> inputElements;
        string input;
        std::getline(std::cin, input);
        if (input == "")
            {
                break;
            }
        inputElements = parseInput(input);
        if (inputElements.size() == 0)
            {
                cout << "Неправильный формат! Повторите ввод..." << std::endl;
                continue;
            }
        
        cout << "Множество записано!" << std::endl;
        FuzzySet fuzzySet;
        fuzzySet.setVector(inputElements);
        inputSets.push_back(fuzzySet);
    }
    
    //Вектор результатов
    vector<FuzzySet> outputSets;

    //Запись в результаты первого множества
    for (int i = 0; i < 4; i++)
    {
        outputSets.push_back(inputSets.at(0));
    }

    //В цикле проходим все остальные множества, перезаписывая результат операции
    for (int i = 1; i < inputSets.size(); i++)
    {
        //Сложение
        std::shared_ptr<IFuzzySet> pFuzzySet1 = std::make_shared<FuzzySet>(*(inputSets[i] + outputSets[0])); //создаём указатель на новое множество из результата операции
        outputSets[0] = *pFuzzySet1;

        //Вычитание
        std::shared_ptr<IFuzzySet> pFuzzySet2 = std::make_shared<FuzzySet>(*(inputSets[i] - outputSets[1])); //создаём указатель на новое множество из результата операции
        outputSets[1] = *pFuzzySet2;

        //Умножение
        std::shared_ptr<IFuzzySet> pFuzzySet3 = std::make_shared<FuzzySet>(*(inputSets[i] * outputSets[2])); //создаём указатель на новое множество из результата операции
        outputSets[2] = *pFuzzySet3;

        //Деление
        std::shared_ptr<IFuzzySet> pFuzzySet4 = std::make_shared<FuzzySet>(*(inputSets[i] / outputSets[3])); //создаём указатель на новое множество из результата операции
        outputSets[3] = *pFuzzySet4;
    }

    //Вывод результата
    for (int i = 0; i < outputSets.size(); i++)
    {
        cout << "A";
        char ch = 'B';
        for (int j = 1; j < inputSets.size(); j++)
        {
            switch (i)
            {
            case 0:
                cout << " + " << ch++;
                break;
            case 1:
                cout << " - " << ch++;
                break;
            case 2:
                cout << " * " << ch++;
                break;
            case 3:
                cout << " / " << ch++;
                break;
            }
        }
        cout << " = {";
        for (int j = 0; j < outputSets[i].getVector().size(); j++)
        {
          cout << outputSets[i].getVector()[j].membership << "/" << outputSets[i].getVector()[j].value;
          if (j!=outputSets[i].getVector().size()-1)
          {
              cout << ", ";
          }
        }
        cout << "}" << std::endl;
    }
    
    cout << std::endl << "Нажмите Enter, чтобы завершить работу...";
    std::cin.ignore();
    return 0;
}

vector<FuzzyElement> parseInput(std::string inputString)
{
    vector<FuzzyElement> empty(0); //возвращается в случае ошибки
    vector<FuzzyElement> output;
    //Делим ввод по запятым
    std::istringstream ss(inputString);
    vector<std::string> commasplits;
    std::string token;

    while (std::getline(ss, token, ','))
    {
        //сразу чистим от пробелов
        token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
        commasplits.push_back(token);
    }

    //если нет результатов, возвращаем пустое
    if (commasplits.size()==0)
        return empty;


    //проходим разбиение по запятым и делим по /
    for (string str : commasplits)
    {
        //деление по /
        std::istringstream ss(str);
        vector<std::string> slashsplits;
        std::string token;

        while (std::getline(ss, token, '/'))
        {
            slashsplits.push_back(token);
        }

        if (slashsplits.size()!=2)
            return empty;
        
        vector<double> doubles;
        for (string doublestring : slashsplits)
        {
            try
            {
            double d = std::stod(doublestring);
            doubles.push_back(d);
            }
            catch(...) //ловится любое исключение
            {
                return empty;
            }
        }
        
        if (doubles.size()!=2)
            return empty;
        
        FuzzyElement elem = {doubles[0], doubles[1]};
        output.push_back(elem);
    }

    //возвращаем вывод
    return output;

}