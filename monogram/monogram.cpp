#include <iostream>
#include"AllFunctions.h"

using namespace std;


int main() {
    srand(static_cast<unsigned int>(time(0)));
    NonogramLevel levels[MAX_DIFFICULTY_LEVEL];
    loadLevels(levels);
    std::string username;
    std::cout << "Enter your username: ";
    std::cin >> username;
    UserProfile user;
    user.username = username;
    if (loadGame(user, MAX_SIZE)) {
        std::cout << "Do you want to continue your last attempt? (Y/N): ";
        char choice;
        std::cin >> choice;

        if (choice == 'Y' || choice == 'y') {
            playGame(user, levels[user.currentLevel - 1]);
        }
        else {
            user.currentLevel = 1;
            int difficultyChoice = getDifficultyChoice();
            playGame(user, levels[difficultyChoice - 1]);
        }
    }
    else {
        user.currentLevel = 1;
        int difficultyChoice = getDifficultyChoice();
        playGame(user, levels[difficultyChoice - 1]);
    }

    return 0;
}