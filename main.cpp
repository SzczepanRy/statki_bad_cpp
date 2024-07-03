#include "ships.hpp"
#include "strike.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

class Game {

public:
  static const int BOARD_W = 11;
  static const int BOARD_H = 11;

  char playerBoard[BOARD_H][BOARD_W];
  char enemyBoard[BOARD_H][BOARD_W];
  char strikeBoard[BOARD_H][BOARD_W];

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
  int checkHits(char board[][11]) {
    int count = 0;
    for (int i = 0; i < 11; i++) {
      for (int j = 0; j < 11; j++) {
        if (board[i][j] == '0') {
          count++;
        }
      }
    }
    return count;
  }

  void readBoard(char board[][11]) {
    for (int i = 0; i < 11; i++) {
      for (int j = 0; j < 11; j++) {
        std::cout << board[i][j] << ',';
      }
      std::cout << "\n";
    }
  }
  void conditionalExit(bool val) {
    if (!val) {
      exit(1);
    }
  }

  void placeShipsLoop(char board[][11], std::string userType) {
    int availibleShipsLength = 10;
    Commands commands;
    int availibleShips[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    /// init the utils class
    Utils utils;

    for (int i = 0; i < availibleShipsLength; i++) {

      bool validPlacement = false;
      std::string command;
      switch (availibleShips[i]) {
      case 4:
        if (userType == "player") {
          std::cout
              << "chose the coordinates and the direction (d - down , l - "
              << "left) of your ship ex: 0al \n :";
          std::cin >> command;
          commands = utils.getCommands(command);
          validPlacement = Ship::placeShip(board, commands, 4);

          std::cout << "Placement validation sucess " << validPlacement;
          conditionalExit(validPlacement);
        } else if (userType == "enemy") {
          while (!validPlacement) {
            // std::cout << "PLACED 4 \n";
            commands = utils.genRandomCommands();
            validPlacement = Ship::placeShip(board, commands, 4);
          }
        } else {
          std::cout << "INVALID USER TYPE";
          conditionalExit(false);
        }
        // invoke a checking and parsing commmand
        break;
      case 3:
        if (userType == "player") {
          std::cout
              << "chose the coordinates and the direction (d - down , l - "
              << "left) of your ship ex: 0al \n :";
          std::cin >> command;
          commands = utils.getCommands(command);
          Ship::placeShip(board, commands, 3);
        } else if (userType == "enemy") {
          while (!validPlacement) {
            // std::cout << "PLACED 3\n";
            commands = utils.genRandomCommands();
            validPlacement = Ship::placeShip(board, commands, 3);
          }

        } else {
          std::cout << "INVALID USER TYPE";
          conditionalExit(false);
        }
        break;
      case 2:
        if (userType == "player") {
          std::cout
              << "chose the coordinates and the direction (d - down , l - "
              << "left) of your ship ex: 0al \n :";
          std::cin >> command;
          commands = utils.getCommands(command);
          Ship::placeShip(board, commands, 2);
        } else if (userType == "enemy") {
          while (!validPlacement) {

            // std::cout <<  "PLACED 2\n";
            commands = utils.genRandomCommands();
            validPlacement = Ship::placeShip(board, commands, 2);
          }
        } else {
          std::cout << "INVALID USER TYPE";
          conditionalExit(false);
        }

        break;

      case 1:
        if (userType == "player") {
          std::cout
              << "chose the coordinates and the direction (d - down , l - "
              << "left) of your ship ex: 0al \n :";
          std::cin >> command;
          commands = utils.getCommands(command);
          Ship::placeShip(board, commands, 1);
        } else if (userType == "enemy") {
          while (!validPlacement) {
            // std::cout << "PLACED 1\n";
            commands = utils.genRandomCommands();
            validPlacement = Ship::placeShip(board, commands, 1);
          }
        } else {
          std::cout << "INVALID USER TYPE";
          conditionalExit(false);
        }
        break;
      }
      readBoard(board);
    }
    // check if there are all thips
    Ship::checkShips(enemyBoard);
  }
  void genEnemyBoard(char enemyBoard[][11]) {
    placeShipsLoop(enemyBoard, "enemy");
  }

  void gameLoop() {
    std::string userType = "player";
    while (true) {
      bool validStrike = false;

      std::cout << "################################ " << userType
                << "###########################\n";
      std::cout << "\nYOURE BOARD \n";
      readBoard(playerBoard);
      std::cout << "\nENEMY BOARD \n";
      readBoard(enemyBoard);
      std::cout << "\nSTRIKE BOARD \n";
      readBoard(strikeBoard);

      if (userType == "player") {
        std::cout << "INPUT STRIKE  COORDS :";
        StrikeType strike;
        std::cin >> strike.x;
        std::cin >> strike.y;
      //  std::cout << "OOOOOOOOOOOOOO";
      //  std::cout << strike.x << strike.y << "\n";
      //  std::cout << "OOOOOOOOOOOOOO";
        bool success = Utils::validateStrike(strike.x, strike.y);
        conditionalExit(success);
        // strike is valid
        //

        validStrike =
            Strike::placeStrike(strikeBoard, enemyBoard, strike, userType);

      } else {
        // GRNRATE RNDOM STRIKE
        StrikeType enemeyStrike;
        enemeyStrike = Strike::generateRandomStrike();

        char trashBoard[11][11];
        //std::cout << "enemy strike " << enemeyStrike.x << enemeyStrike.y
         //         << "\n";
        validStrike = Strike::placeStrike(trashBoard, playerBoard, enemeyStrike,
                                          userType);
      }
      if (!validStrike) {
        std::cout << "INVALID STRIKE ";
        validStrike = false;
      }
      if (userType == "player") {
        std::cout << "Strike cout " << checkHits(enemyBoard) << "\n";
        if (checkHits(enemyBoard) == 20) {
          std::cout << "PLAYER WONNNNNNNNNNNN";
          conditionalExit(false);
        }

        userType = "enemy";
      } else {
        if (checkHits(playerBoard) == 20) {
          std::cout << "ENEMY WONNNNNNNNNNNN";
          conditionalExit(false);
        }

        userType = "player";
      }
    }
  }

  Game() {
    makeBoard(playerBoard);
    readBoard(playerBoard);
    placeShipsLoop(playerBoard, "player");
    makeBoard(enemyBoard);
    placeShipsLoop(enemyBoard, "enemy");
    makeBoard(strikeBoard);
    gameLoop();
  }
};

int main() {
  Game game;
  return 0;
}
