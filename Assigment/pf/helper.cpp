#include "helper.h"
#include <cstdlib>
#include <iostream>
#include <ctime> // for seeding srand

namespace pf
{
    const int kRows = 3;
    const int kColumns = 5;
    char kBoard[kRows][kColumns];

    int ClearScreen()
    {
        #if defined(_WIN32)
            return std::system("cls");
        #elif defined(linux) || defined(APPLE)
            return std::system("clear");
        #endif
    }

    void Pause()
    {
        std::cout << "Press any key to continue . . ." << std::endl;
        std::cin.get();
    }

    void CreateGameBoard()
    {
        std::srand(time(0));
        for (int row = 0; row < kRows; ++row)
        for (int col = 0; col < kColumns; ++col)
        {
            int random_number = std::rand() % 2;
            if (random_number)
                kBoard[row][col] = '*';
            else
                kBoard[row][col] = 'r';
        }
    }

    void ShowGameBoard()
    {
        for (int row = 0; row < kRows; ++row)
        {
            for (int col = 0; col < kColumns; ++col)
            {
                std::cout << kBoard[row][col];
            }
            std::cout << std::endl;
        }
    }
}