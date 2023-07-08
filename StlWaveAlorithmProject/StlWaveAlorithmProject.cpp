// StlWaveAlorithmProject.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "Wave.h"

int main()
{
    Wave wave("map.txt");
    wave.CreateMap();
    wave.ShowMap();

    if (wave.MoveWave())
    {
        wave.ShowMap();
        wave.CreateWay();
        wave.ShowMap();
    }
        

    cout << "\n";
}
