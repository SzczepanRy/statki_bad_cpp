#include "ships.hpp"
#include "utils.hpp"
#include <cwchar>
#include <iostream>
#include <string>

struct Strike {
  char x;
  char y;
};

class Game {

public:
  static const int BOARD_W = 11;
  static const int BOARD_H = 11;

  char playerBoard[BOARD_H][BOARD_W];
  char enemyBoard[BOARD_H][BOARD_W];

  Commands commandsArr[];

  void makeBoard(char board[][11]) {

    char numbersArray[] = {'a', 'O', '1', '2', '3', '4',
                           '5', '6', '7', '8', '9'};
    char lettersArray[] = {'a', 'a', 'b', 'c', 'd', 'e',
                           'f', 'g', 'h', 'i', 'j'};

    for (int i = 0; i < 11; i++) {
      for (int j = 0; j < 11; j++) {
        if (i == 0 && j == 0) {
          board[i][j] = '=';
          continue;
        }
        if (i == 0) {
          board[i][j] = numbersArray[j];
          continue;
        }
        if (j == 0) {
          board[i][j] = lettersArray[i];
          continue;
        }

        board[i][j] = '_';
      }
    }
  }

  void readBoard(char board[][11]) {
    for (int i = 0; i < 11; i++) {
      for (int j = 0; j < 11; j++) {
        std::cout << board[i][j] << ',';
      }
      std::cout << "\n";
    }
  }

  void placeShip(char board[][11], Commands commands, int length) {
    char numbersArray[] = {'*', '0', '1', '2', '3', '4',
                           '5', '6', '7', '8', '9'};
    char lettersArray[] = {'*', 'a', 'b', 'c', 'd', 'e',
                           'f', 'g', 'h', 'i', 'j'};

    char validXForLeft[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char validYForDown[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

    bool validXL = false;
    bool validYD = false;

    if (commands.dir == 'l') {
      validXL = Utils::checkCharArr(validXForLeft, 11 - length, commands.x);
      validYD = true;
    } else {
      validYD = Utils::checkCharArr(validYForDown, 11 - length, commands.y);
      validXL = true;
    }
    std::cout << "validation of placment " << validYD << "  " << validXL
              << "\n";
    if (validYD && validXL) {

      if (commands.dir == 'l') {
        char placeXArray[length];
        int placeXArrayIndex = 0;
        for (int i = 1; i < 11; i++) {
          if (lettersArray[i] == commands.y) {
            for (int j = 1; j < 11; j++) {
              if (numbersArray[j] == commands.x) {
                if (board[i][j] == 'O') {
                  std::cout << "PLACED SHIPS COLIDED\n";
                  exit(1);
                }
                board[i][j] = 'O';
                placeXArrayIndex++;

              } else if (placeXArrayIndex != 0 && placeXArrayIndex <= length) {
                if (board[i][j] == 'O') {
                  std::cout << "PLACED SHIPS COLIDED\n";
                  exit(1);
                }
                board[i][j] = 'O';
                placeXArrayIndex++;
              }
            }
          }
        }
      } else if (commands.dir == 'd') {

        char placeYArray[length];
        int placeYArrayIndex = 0;
        for (int i = 1; i < 11; i++) {
          if (numbersArray[i] == commands.x) {
            for (int j = 1; j < 11; j++) {
              if (lettersArray[j] == commands.y) {
                if (board[j][i] == 'O') {
                  std::cout << "PLACED SHIPS COLIDED\n";
                  exit(1);
                }
                board[j][i] = 'O';
                placeYArrayIndex++;

              } else if (placeYArrayIndex != 0 && placeYArrayIndex <= length) {
                if (board[j][i] == 'O') {
                  std::cout << "PLACED SHIPS COLIDED\n";
                  exit(1);
                }
                board[j][i] = 'O';
                placeYArrayIndex++;
              }
            }
          }
        }
      }
    } else {
      std::cout << "NOT A VALID POSITION\n";
      exit(1);
    }
  }

  void placeShipsLoop(char board[][11]) {
    int availibleShipsLength = 10;
    Commands commands;
    int availibleShips[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    /// init the utils class
    Utils utils;

    for (int i = 0; i < availibleShipsLength; i++) {

      std::string command;
      switch (availibleShips[i]) {
      case 4:
        std::cout << "chose the coordinates and the direction (d - down , l - "
                  << "left) of your ship ex: 0al \n :";
        std::cin >> command;
        commands = utils.getCommands(command);
        // invoke a checking and parsing commmand
        this->placeShip(board, commands, 4);
        readBoard(board);
        break;
      case 3:
        std::cout << "chose the coordinates and the direction (d - down , l - "
                  << "left) of your ship ex: 0al \n :";
        std::cin >> command;

        commands = utils.getCommands(command);
        // invoke a checking and parsing commmand

        this->placeShip(board, commands, 3);
        readBoard(board);
        break;
      case 2:
        std::cout << "chose the coordinates and the direction (d - down , l - "
                  << "left) of your ship ex: 0al \n :";
        std::cin >> command;

        commands = utils.getCommands(command);
        // invoke a checking and parsing commmand

        this->placeShip(board, commands, 2);
        readBoard(board);
        break;

      case 1:
        std::cout << "chose the coordinates and the direction (d - down , l - "
                  << "left) of your ship ex: 0al \n :";
        std::cin >> command;
        commands = utils.getCommands(command);
        // invoke a checking and parsing commmand
        this->placeShip(board, commands, 1);
        readBoard(board);
        break;
      }
    }
  }

  void gameLoop() {
    while (true) {
      std::cout << "\nYOURE BOARD \n";
      readBoard(playerBoard);

      std::cout << "\nENEMY BOARD \n";
      readBoard(playerBoard);

      std::cout << "INPUT STRIKE X COORDS :";
      Strike strike;
      std::cin >> strike.x;
      std::cout << "INPUT STRIKE Y COORDS :";
      std::cin >> strike.y;
    }
  }

  Game() {
    makeBoard(playerBoard);
    readBoard(playerBoard);
    placeShipsLoop(playerBoard);
    makeBoard(enemyBoard);
    gameLoop();
  }
};

int main() {

  Game game;

  return 0;
}
