// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: T11L
// Name: SARVESH A/L MUNUSAMY | AKHILESHNAIDU A/L JAYA KUMAR | NICHOLAS CHEOK JIA JIE
// IDs: 1211100986 | 1211101804 | 1211102168
// Emails: 1211100986@student.mmu.edu.my | 1211101804@student.mmu.edu.my | 1211102168@student.mmu.edu.my
// Phones: 0163454673 | 0167574747 | 0178879526
// *********************************************************

#include "pf/helper.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

class Board
{
private:
    vector<vector<char>> map_;
    int Row_, Col_;
    int alienRow, alienCol;
 
public:
    Board(int Row, int Col);
    void init(int Row, int Col);
    void display() const;
    bool moveAlien(char direction);
};

Board::Board(int Row, int Col)
{
    cout << endl;
    cout << "Board Settings" << endl;
    cout << "----------------" << endl;
    cout << "Enter rows => ";
    cin >> Row;
    cout << "Enter columns => ";
    cin >> Col;

    init(Col, Row);
}

void Board::init(int Row, int Col)
{
    Row_ = Row;
    Col_ = Col;
    char objects[] = {'h', 'p', 'r', '>', '<', '^', 'v', ' ', ' ', ' '};
    int noOfObjects = 10; // number of objects in the objects array
    // create dynamic 2D array using vector
    map_.resize(Col_); // create empty rows
    for (int i = 0; i < Col_; ++i)

    {
        map_[i].resize(Row_); // resize each row
    }
    // put random characters into the vector array
    for (int i = 0; i < Col_; ++i)
    {
        for (int j = 0; j < Row_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
    map_[Col_ / 2][Row_ / 2] = 'A';
}


void Board::display() const
{
    cout << " -----------------------------------" << endl;
    cout << " ==========ALIEN VS ZOMBIE==========" << endl;
    cout << " -----------------------------------" << endl;

    // for each row
    for (int i = 0; i < Col_; ++i)
    {
        // display upper border of the row
        cout << " ";
        for (int j = 0; j < Row_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;
        // display row number
        cout << setw(2) << (Col_ - i);
        // display cell content and border of each column
        for (int j = 0; j < Row_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }
    // display lower border of the last row
    cout << " ";
    for (int j = 0; j < Row_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;
    // display column number
    cout << " ";
    for (int j = 0; j < Row_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << " ";
    for (int j = 0; j < Row_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}

void startGame() {
    int rows, columns, zombies;
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> columns;
    cout << "Enter number of zombies: ";
    cin >> zombies;
    Board board(rows, columns);
    board.display();

    // Add code here to start the game
}

void displayMenu()
{
    cout << "!==========================================================!" << endl;
    cout << "!                        ALIEN VS ZOMBIE                   !" << endl;
    cout << "!==========================================================!" << endl;
    cout << " CHOOSE:                                                  " << endl;
    cout << " 1 => reveal the game's default settings  " << endl;
    cout << " 2 => reveal Help " << endl;
    cout << " 3 => Change default game settings and START the game. " << endl;
    cout << " 4 => Load game and save game " << endl;
    cout << " 5 => END GAME " << endl;
    cout << endl;
}

void displayDefault(int rows, int columns, int zombies)
{
    cout << "ROWS = " << rows << endl;
    cout << "COLUMNS = " << columns << endl;
    cout << "ZOMBIES = " << zombies << endl;
    cout << endl;
}

void displayHelp()
{
    cout << " UP = Move up" << endl;
    cout << " DOWN = Move down" << endl;
    cout << " LEFT = Move left" << endl;
    cout << " RIGHT = Move right" << endl;
    cout << " ARROW = Change the direction of an arrow" << endl;
    cout << " HELP = Display these user commands" << endl;
    cout << " SAVE = Save the game" << endl;
    cout << " LOAD = Load the game" << endl;
    cout << " QUIT = Quit the game" << endl;
    cout << endl;
}

int main()
{
    int rows = 5;
    int columns = 9;
    int zombies = 1;

    char select;
    bool done = false;
    displayMenu();
    do
    {
        cout << "Select => ";
        cin >> select;
        select = toupper(select);
        cout << endl;
        switch (select)
        {
        case '1':
            displayDefault(rows, columns, zombies);
            break;
        case '2':
            displayHelp();
            break;
        case '3':
            cout << "Change game settings" << endl;
            cout << "Enter number of rows: ";
            cin >> rows;
            cout << "Enter number of columns: ";
            cin >> columns;
            cout << "Enter number of zombies: ";
            cin >> zombies;
            break;
        case '4':
            cout << "Load or save game" << endl;
            break;
        case '5':
            done = true;
            break;
        default:
            cout << "Invalid selection" << endl;
            break;
        }
    } while (!done);

    return 0;
}

