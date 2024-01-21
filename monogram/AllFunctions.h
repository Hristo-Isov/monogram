#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_SIZE = 15;
const int MAX_WRONG_ANSWERS = 3;
const int MAX_DIFFICULTY_LEVEL = 5;

struct UserProfile {
    string username;
    int currentLevel;
    int currentWrongAnswers;
    char currentGrid[MAX_SIZE][MAX_SIZE];
};

struct NonogramLevel {
    int size;
    int maxWrongAnswers;
    char picture[MAX_SIZE][MAX_SIZE];
};

void loadLevels(NonogramLevel levels[MAX_DIFFICULTY_LEVEL]) {
    // Super Easy Level
    levels[0].size = 5;
    levels[0].maxWrongAnswers = 3;
    char superEasy1[MAX_SIZE][MAX_SIZE] =
    {
        {'X', '-', 'X', '-', 'X'},
        {'X', '-', '-', '-', '-'},
        {'X', '-', '-', '-', '-'},
        {'X', '-', '-', '-', '-'},
        {'X', '-', '-', '-', '-'},
    };
    char superEasy2[MAX_SIZE][MAX_SIZE] =
    {
        {'-', '-', '-', '-', 'X'},
        {'X', '-', '-', '-', '-'},
        {'X', '-', '-', '-', '-'},
        {'X', '-', '-', '-', '-'},
        {'X', '-', '-', '-', '-'},
    };
    for (int i = 0; i < MAX_SIZE; ++i) {
        for (int j = 0; j < MAX_SIZE; ++j) {
            int randomChoice = rand() % 2;

            // Choose either superEasy1 or superEasy2 based on the random number
            levels[0].picture[i][j] = (randomChoice == 0) ? superEasy1[i][j] : superEasy2[i][j];
        }
    }

    // Easy Level
    levels[1].size = 5;
    levels[1].maxWrongAnswers = 3;
    char easy[MAX_SIZE][MAX_SIZE] =
    {
        {'X', '-', 'X', '-', 'X'},
        {'X', '-', 'x', '-', 'X'},
        {'X', '-', 'x', '-', 'X'},
        {'X', '-', 'x', '-', 'X'},
        {'X', '-', 'x', '-', 'X'},
    };
    for (int i = 0; i < MAX_SIZE; ++i) {
        for (int j = 0; j < MAX_SIZE; ++j) {
            levels[1].picture[i][j] = easy[i][j];
        }
    }
}

bool areMatricesEqual(char grid[MAX_SIZE][MAX_SIZE], char picture[MAX_SIZE][MAX_SIZE], int size) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            if (grid[i][j] != picture[i][j]) {
                return false;
            }
        }
    }
    cout << "Matrices are equal\n";
    return true;
}

void printGrid(char grid[MAX_SIZE][MAX_SIZE], char picture[MAX_SIZE][MAX_SIZE], int size) {
    std::cout << "\nYour Current Grid:\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (grid[i][j] == 'X') {
                std::cout << 'X';
            }
            else if (grid[i][j] == '-') {
                std::cout << '-';
            }
            else {
                std::cout << '_';
            }
            std::cout << ' ';
        }
        std::cout << '\n';
    }
    cout << "\nRow Numbers and Column Numbers:\n";
    for (int i = 0; i < size; ++i) {
        std::vector<int> columnNumbers;
        int count = 0;
        std::cout << i + 1 << " column ";
        for (int j = 0; j < size; ++j) {
            if (picture[j][i] == 'X') {
                count++;
            }
            else if (count > 0) {
                columnNumbers.push_back(count);
                count = 0;
            }
        }
        if (count > 0) {
            columnNumbers.push_back(count);
        }
        else {
            columnNumbers.push_back(0);
        }
        for (int num : columnNumbers) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }
    for (int i = 0; i < size; ++i) {
        int count = 0;
        std::cout << i + 1 << " row ";
        for (int j = 0; j < size; ++j) {
            if (picture[i][j] == 'X') {
                count++;
            }
            else {
                if (count > 0) {
                    std::cout << count << " ";
                    count = 0;
                }
            }
        }
        if (count > 0) {
            std::cout << count << " ";
        }
        std::cout << "\n";
    }
}

void saveGame(UserProfile& user, int size) {
    ofstream file(user.username + "_save.txt");
    if (file.is_open()) {
        file << user.currentLevel << '\n';
        file << user.currentWrongAnswers << '\n';
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file << user.currentGrid[i][j] << ' ';
            }
            file << '\n';
        }
        file.close();
        cout << "Game saved successfully.\n";
    }
    else {
        cerr << "Unable to save the game.\n";
    }
}

bool loadGame(UserProfile& user, int size) {
    std::ifstream file(user.username + "_save.txt");

    if (file.is_open()) {
        file >> user.currentLevel;
        file >> user.currentWrongAnswers;

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file >> user.currentGrid[i][j];
            }
        }

        file.close();
        std::cout << "Game loaded successfully.\n";
        return true;
    }
    else {
        std::cerr << "Unable to load the game.\n";
        return false;
    }
}

bool isLevelComplete(char grid[MAX_SIZE][MAX_SIZE], char picture[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (grid[i][j] != picture[i][j]) {
                return false;
            }
        }
    }
    return true;
}
int getDifficultyChoice() {
    int choice;
    cout << "Choose difficulty level:\n";
    cout << "1. Super Easy\n";
    cout << "2. Easy\n";
    cout << "3. Medium\n";
    cout << "4. Hard\n";
    cout << "5. Extreme\n";
    cout << "Enter the number corresponding to your choice: ";
    cin >> choice;
    return choice;
}
void playGame(UserProfile& user, NonogramLevel& level) {
    int size = level.size;
    char picture[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (level.picture[i][j] == '\0') {
                picture[i][j] = '_';
            }
            else {
                picture[i][j] = level.picture[i][j];
            }
        }
    }


    while (user.currentWrongAnswers < level.maxWrongAnswers) {
        if (isLevelComplete(user.currentGrid, picture, size)) {
            std::cout << "Congratulations! You completed Level " << user.currentLevel << "!\n";
            user.currentLevel++;

            if (user.currentLevel > MAX_DIFFICULTY_LEVEL) {
                saveGame(user, size);
                std::cout << "You completed all levels. Game over.\n";
                break;
            }
        }

        printGrid(user.currentGrid, picture, size);

        int row, col;
        std::cout << "\nEnter row and column (1-" << size << "): ";
        std::cin >> row >> col;

        if (row < 1 || row > size || col < 1 || col > size) {
            std::cout << "Invalid input. Please enter valid row and column numbers.\n";
            continue;
        }

        char guess;
        std::cout << "Enter 'F' for filled or 'E' for empty: ";
        std::cin >> guess;

        if (guess == 'q') {
            saveGame(user, size);
            exit(0);
        }

        if (guess == 'F') {
            if (picture[row - 1][col - 1] == 'X') {
                user.currentGrid[row - 1][col - 1] = 'X';
            }
            else {
                std::cout << "Wrong guess!\n";
                user.currentWrongAnswers++;
            }
        }
        else if (guess == 'E') {
            if (picture[row - 1][col - 1] == '_') {
                user.currentGrid[row - 1][col - 1] = '_';
            }
            else {
                std::cout << "Wrong guess!\n";
                user.currentWrongAnswers++;
            }
        }
        else {
            std::cout << "Invalid input. Please enter 'F' or 'E'.\n";
        }

     
        for (int i = 0; i < size; ++i) {
            bool rowComplete = true;
            bool colComplete = true;

            for (int j = 0; j < size; ++j) {
                if (picture[i][j] == 'X' && user.currentGrid[i][j] != 'X') {
                    rowComplete = false;
                }

                if (picture[j][i] == 'X' && user.currentGrid[j][i] != 'X') {
                    colComplete = false;
                }
            }

            if (rowComplete) {
                for (int j = 0; j < size; ++j) {
                    if (user.currentGrid[i][j] == '_') {
                        user.currentGrid[i][j] = '-';
                    }
                }
            }

            if (colComplete) {
                for (int j = 0; j < size; ++j) {
                    if (user.currentGrid[j][i] == '_') {
                        user.currentGrid[j][i] = '_';
                    }
                }
            }
        }
    }
    std::cout << "Game over! You reached the maximum number of wrong answers.\n";
}