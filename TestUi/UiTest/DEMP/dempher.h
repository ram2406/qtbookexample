#ifndef DEMPHER_H
#define DEMPHER_H

#include <cstdio>

#include <string>
#include <vector>
/*
 Модуль считывает сигналы управляющей программы
, модифицирует в зависемости от характеристекк стонка
    звдвнные пользователем.
*/



enum result_code {
 SUCCESS  = 0,
 ERROR_01 = 1,
 ERROR_02 = 2,
 ERROR_03 = 3,
 ERROR_04 = 4,
 ERROR_05 = 5,
 ERROR_06 = 6,
 ERROR_07 = 7,
 ERROR_08 = 8,
 ERROR_09 = 9
};

inline std::string getTextResCode(result_code code) {
    switch (code) {
    //case ERROR_01: return "\nERROR_01: не указано имя входного файла!";
    //case ERROR_02: return "\nERROR_02: не указано имя выходного файла!";
    case ERROR_03: return "\nERROR_03: невозможно открыть входной файлы!";
    case ERROR_04: return "\nERROR_04: невозможно открыть выходной файлы!";
    case ERROR_05: return "\nERROR_05: не найден файл параметров!";
    case ERROR_06: return "\nERROR_06: не все параметры найдены!";
    case ERROR_07: return "\nERROR_07: превышено максимальное число кадров!";
    case ERROR_08: return "\nERROR_08: не найден символ начала кадра N%d!";
    case ERROR_09: return "\nERROR_09: не хватает перемещений для разгона/торможения в кадре N%d!";

    default: return 0;
    }
}




struct CONFIG
{
    double dF1;     //допустимый перепад скоростей
    double dF2;     //минимальное приращение скорости при демпфирировании
};


struct CADR
{
    //координаты
    long   X;
    long   Y;
    long   Z;
    //количество не нулевых символов в кадре
    long   L;
    //значение скорости выдачи унитарного кода
    double F;
};




class DempherClass {
public:
    result_code exec(std::string filenameIn, std::string filenameOut, bool step , CONFIG &conf);

    DempherClass();
private:

    CONFIG config;                  //конфигурация dF1, dF2
    std::vector<CADR>   cadr;       //массив считанных кадров из файла
    int    nCadr;                   //количество считанных кадров

    void GetConfig(void);           //не используется

    result_code GetCadr(FILE * fin);    //считывание кадров
    void PutCadr(int step);             //вывод кадров

    result_code Dempher(FILE * fin, FILE * fout);   //демпфирование

    static unsigned short NCADR;  //количество заранее зарезервированных

};


#endif // DEMPHER_H
