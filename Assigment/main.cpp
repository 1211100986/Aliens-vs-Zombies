// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: T11L
// Name: SARVESH A/L MUNUSAMY | AKHILESHNAIDU A/L JAYA KUMAR | NICHOLAS CHEOK JIA JIE
// IDs: 1211100986 | 1211101804 | 1211102168
// Emails: 1211100986@student.mmu.edu.my | 1211101804@student.mmu.edu.my | 1211102168@student.mmu.edu.my
// Phones: 0163454673 | 0167574747 | 0178879526
// *********************************************************

#include "Save_Load.cpp"
#include "pf/helper.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>


using namespace std;

class Arrow 
{
public:
    void Init() {}
};

class Health 
{
public:
    void Init() {}
};

class Pod 
{
public:
    void Init() {}
};

class Rock 
{
public:
    void Init() {}
};

class Empty 
{
public:
    void Init() {}
};

class Trail 
{
public:
    void Init() {}
};

class Alien 
{
private:
    int row_;
    int col_;
    char direction_;

public:
    Alien(int row, int col);
    void setPosition(int row, int col);
    void setDirection(char direction);
    int getRow() const;
    int getCol() const;
    char getDirection() const;
    void move(char direction);
};

Alien::Alien(int row, int col) {
    setPosition(row, col);
    setDirection('^');  // start facing upwards
}

void Alien::setPosition(int row, int col) {
    row_ = row;
    col_ = col;
}

void Alien::setDirection(char direction) {
    direction_ = direction;
}

int Alien::getRow() const {
    return row_;
}

int Alien::getCol() const {
    return col_;
}

char Alien::getDirection() const {
    return direction_;
}

void Alien::move(char direction) {
    switch (direction) {
        case 'U':
            row_--;
            setDirection('^');
            break;
        case 'D':
            row_++;
            setDirection('v');
            break;
        case 'L':
            col_--;
            setDirection('<');
            break;
        case 'R':
            col_++;
            setDirection('>');
            break;
        default:
            // do nothing
            break;
    }
}

class Zombie 
{
private:
    int row_;
    int col_;
    char direction_;

public:
    Zombie(int row, int col);
    void setPosition(int row, int col);
    void setDirection(char direction);
    int getRow() const;
    int getCol() const;
    char getDirection() const;
    void move(char direction);
};

Zombie::Zombie(int row, int col) {
    setPosition(row, col);
    setDirection('^');  // start facing upwards
}

void Zombie::setPosition(int row, int col) {
    row_ = row;
    col_ = col;
}

void Zombie::setDirection(char direction) {
    direction_ = direction;
}

int Zombie::getRow() const {
    return row_;
}

int Zombie::getCol() const {
    return col_;
}

char Zombie::getDirection() const {
    return direction_;
}

void Zombie::move(char direction) {
    switch (direction) {
        case 'U':
            row_--;
            setDirection('^');
            break;
        case 'D':
            row_++;
            setDirection('v');
            break;
        case 'L':
            col_--;
            setDirection('<');
            break;
        case 'R':
            col_++;
            setDirection('>');
            break;
        default:
            // do nothing
            break;
    }
}

class Board
{
private:
    vector<vector<char>> map_;
    int row_, col_;
    Alien alien_;
    Zombie zombie_;
 
public:
    Board(int row, int col);
    void init();
    void display() const;
    bool moveAlien(char direction);
    bool moveZombie(char direction);
    char getSymbolAt(int row, int col) const;
    void setSymbolAt(int row, int col, char symbol);
    void moveZombie(bool shouldMoveFast);
    vector<vector<char>> getMap() const;
};

Board::Board(int row, int col) : row_(row), col_(col), alien_(row / 2, col / 2), zombie_(row / 3, col / 3)
{
    init();
}

void Board::init()
{
    char objects[] = {'h', 'p', 'r', '>', '<', '^', 'v', ' ', ' ', ' '};
    int noOfObjects = 10; // number of objects in the objects array
    // create dynamic 2D array using vector
    map_.resize(row_); // create empty rows
    for (int i = 0; i < row_; ++i)
    {
        map_[i].resize(col_); // resize each row
    }
    // put random characters into the vector array
    for (int i = 0; i < row_; ++i)
    {
        for (int j = 0; j < col_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
    map_[alien_.getRow()][alien_.getCol()] = 'A';
    map_[zombie_.getRow()][zombie_.getCol()] = 'Z';
}

bool Board::moveAlien(char direction) {
    alien_.move(direction);
    int row = alien_.getRow();
    int col = alien_.getCol();
    if (row < 0 || row >= row_ || col < 0 || col >= col_) {
        // the alien has gone out of bounds, so undo the move and return false
        alien_.move((direction == 'U') ? 'D' : ((direction == 'D') ? 'U' : ((direction == 'L') ? 'R' : 'L')));
        return false;
    }
    char symbol = map_[row][col];
    if (symbol == 'Z') {
        // the alien has collided with the zombie, so the game is over
        map_[row][col] = 'X'; // mark the collision point with 'X'
        return false;
    }
    // the move is valid, so update the map
    map_[alien_.getRow()][alien_.getCol()] = 'A';
    map_[row][col] = ' ';
    return true;
}

bool Board::moveZombie(Zombie& zombie, char direction) {
    int row = zombie.getRow();
    int col = zombie.getCol();
    int target_row = row, target_col = col;

    switch (direction) {
        case 'U': target_row = row - 1; break;
        case 'D': target_row = row + 1; break;
        case 'L': target_col = col - 1; break;
        case 'R': target_col = col + 1; break;
    }

    if (isValidCell(target_row, target_col) && getSymbolAt(target_row, target_col) == ' ') {
        // Clear the zombie's current position
        setSymbolAt(row, col, ' ');
        // Move the zombie to the new position
        setSymbolAt(target_row, target_col, 'Z');
        zombie.setPosition(target_row, target_col);
        return true;
    }

    return false;
}

char Board::getSymbolAt(int row, int col) const {
    return map_[row][col];
}

void Board::setSymbolAt(int row, int col, char symbol) {
    map_[row][col] = symbol;
}

vector<vector<char>> Board::getMap() const {
    return map_;
}

void Board::display() const
{
    cout << " -----------------------------------" << endl;
    cout << " ==========ALIEN VS ZOMBIE==========" << endl;
    cout << " -----------------------------------" << endl;

    // for each row
    for (int i = 0; i < row_; ++i)
    {
        // display upper border of the row
        cout << " ";
        for (int j = 0; j < col_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;
        // display row number
        cout << setw(2) << (row_ - i);
        // display cell content and border of each column
        for (int j = 0; j < col_; ++j)
        {
            cout << "|";
            if (alien_.getRow() == i && alien_.getCol() == j)
            {
                cout << 'A';
            }
            else if (zombie_.getRow() == i && zombie_.getCol() == j)
            {
                cout << 'Z';
            }
            else
            {
                cout << map_[i][j];
            }
        }
        cout << "|" << endl;
    }
    // display lower border of the board
    cout << " ";
    for (int i = 0; i < col_; ++i)
    {
        cout << "+-";
    }
    cout << "+" << endl;
    // display column numbers
    cout << " ";
    for (int i = 0; i < col_; ++i)
    {
        cout << setw(3) << (i + 1);
    }
    cout << endl;
}

char get_random_direction()
{
    int rand_int = rand() % 4;
    if (rand_int == 0) {
        return 'U';
    }
    else if (rand_int == 1) {
        return 'D';
    }
    else if (rand_int == 2) {
        return 'L';
    }
    else {
        return 'R';
    }
}

void startgame(int rows, int columns, int zombies)
{
    Board board(rows, columns);
    board.display();
    cout << "Starting game with " << rows << " rows, " << columns << " columns, and " << zombies << " zombies." << endl;
    // Add zombies to the board
    int num_zombies = 0;
    while (num_zombies < zombies) 
    {
        int row = rand() % rows;
        int col = rand() % columns;
        if (board.getSymbolAt(row, col) != 'Z') {
            board.setSymbolAt(row, col, 'Z');
            num_zombies++;
        }
    }

    Alien alien(rows / 2, columns / 2); // create Alien object and place it in the center of the board
    bool gameOver = false;
    while (!gameOver) {
        char direction;
        cout << "Enter direction (U/D/L/R): ";
        cin >> direction;

        // move the Alien in the specified direction
        if (board.moveAlien(direction)) {
            alien.move(direction);
            board.display();
        }

        // check if the Alien has collided with a zombie
        if (board.getSymbolAt(alien.getRow(), alien.getCol()) == 'Z') {
            cout << "Game over! Alien collided with a zombie." << endl;
            gameOver = true;
        }

        // check if the Alien has reached the edge of the board
        if (alien.getRow() == 0 || alien.getRow() == rows - 1 || alien.getCol() == 0 || alien.getCol() == columns - 1) {
            cout << "Game over! Alien has reached the edge of the board." << endl;
            gameOver = true;
        }
    }

    // create a vector to store Zombie objects
    vector<Zombie> zombiesOnBoard;

    // add zombies to the vector
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            if (board.getSymbolAt(row, col) == 'Z') {
                Zombie zombie(row, col);
                zombiesOnBoard.push_back(zombie);
            }
        }
    }

    // move the zombies randomly
    while (!zombiesOnBoard.empty()) {
        for (auto it = zombiesOnBoard.begin(); it != zombiesOnBoard.end();) {
            char direction = get_random_direction();
            int prev_row = it->getRow();
            int prev_col = it->getCol();
            if (board.moveZombie(*it, direction)) {
                it->move(direction);
                board.display();
                if (board.getSymbolAt(it->getRow(), it->getCol()) == 'A') {
                    cout << "Game over! Zombie collided with the alien." << endl;
                    gameOver = true;
                    break;
                }
            }
            if (prev_row == it->getRow() && prev_col == it->getCol()) {
                it = zombiesOnBoard.erase(it);
            }
        }
    }

    if (!gameOver) {
        cout << "Congratulations! You have won the game!" << endl;
    }
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
void displayMenu();
void displayDefault(int rows, int columns, int zombies);
void displayHelp();
void startgame(int rows, int columns, int zombies);


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
            startgame(rows, columns, zombies);
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
            cout << endl;
            break;
        }
    } while (!done);
    cout << endl;
}

