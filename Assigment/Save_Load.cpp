#include <fstream>
#include <iostream>

class Game {
public:
    int score;
    int level;
    // other game-related data

    void save(std::string filename) {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }

        file.write(reinterpret_cast<char*>(&score), sizeof(score));
        file.write(reinterpret_cast<char*>(&level), sizeof(level));
        // write other game-related data to file

        file.close();
    }

    void load(std::string filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }

        file.read(reinterpret_cast<char*>(&score), sizeof(score));
        file.read(reinterpret_cast<char*>(&level), sizeof(level));
        // read other game-related data from file

        file.close();
    }
};

int main() {
    Game game;
    game.score = 100;
    game.level = 5;
    // set other game-related data

    std::string filename = "game_data.bin";
    game.save(filename);

    // reset game data
    game.score = 0;
    game.level = 0;
    // reset other game-related data

    game.load(filename);
    std::cout << "Loaded game data: score=" << game.score << ", level=" << game.level << std::endl;

    return 0;
}
