#pragma once

#include "utils.hpp"
#include <iostream>
#include <type_traits>

struct Coordinets {
  int x;
  int y;
};

class Ship {
public:
  int length;
  int x;
  int y;
  char dir;

  Commands commandsArr[];
  void test() { std::cout << "test on Ship called"; }

  static void checkShips(char board[][11]) {
    int controllSum = 0;
    for (int i = 0; i < 11; i++) {
      for (int j = 0; j < 11; j++) {
        if (board[i][j] == 'O') {
          controllSum++;
        }
      }
    }

    if (controllSum < 20) {
      int aditionalShipLength = 20 - controllSum;

      bool validPlacement= false;
      Commands commands;
      Utils utils;
      while (!validPlacement) {

        // std::cout <<  "PLACED 2\n";
        commands = utils.genRandomCommands();
        validPlacement = Ship::placeShip(board, commands, 2);
      }
    }
  }

  static bool placeShip(char board[][11], Commands commands, int length) {
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
 //    std::cout << "validation of placment " << validYD << "  " << validXL
   //            << "\n";
    if (validYD && validXL) {

      if (commands.dir == 'l') {
        Coordinets shipArray[length];
        char placeXArray[length];
        int placeXArrayIndex = 0;
        for (int i = 1; i < 11; i++) {
          if (lettersArray[i] == commands.y) {
            for (int j = 1; j < 11; j++) {
              if (numbersArray[j] == commands.x) {
                if (board[i][j] == 'O') {
                  std::cout << "PLACED SHIPS COLIDED\n";
                  return false;
                }
                Coordinets coords{x : i, y : j};
                shipArray[placeXArrayIndex] = coords;
                placeXArrayIndex++;

              } else if (placeXArrayIndex != 0 && placeXArrayIndex < length) {
                if (board[i][j] == 'O') {
                  std::cout << "PLACED SHIPS COLIDED\n";
                  return false;
                }
                Coordinets coords{x : i, y : j};
                shipArray[placeXArrayIndex] = coords;
                placeXArrayIndex++;
              }
            }
          }
        }

        for (int i = 0; i < length; i++) {
          board[shipArray[i].x][shipArray[i].y] = 'O';
        }

      } else if (commands.dir == 'd') {
        Coordinets shipArray[length];

        char placeYArray[length];
        int placeYArrayIndex = 0;
        for (int i = 1; i < 11; i++) {
          if (numbersArray[i] == commands.x) {
            for (int j = 1; j < 11; j++) {
              if (lettersArray[j] == commands.y) {
                if (board[j][i] == 'O') {
                  std::cout << "PLACED SHIPS COLIDED\n";
                  return false;
                }
                Coordinets coords{x : i, y : j};
                shipArray[placeYArrayIndex] = coords;
                placeYArrayIndex++;

              } else if (placeYArrayIndex != 0 && placeYArrayIndex < length) {
                if (board[j][i] == 'O') {
                  std::cout << "PLACED SHIPS COLIDED\n";

                  return false;
                }
                Coordinets coords{x : i, y : j};
                shipArray[placeYArrayIndex] = coords;
                placeYArrayIndex++;
              }
            }
          }
        }
        for (int i = 0; i < length; i++) {
          board[shipArray[i].x][shipArray[i].y] = 'O';
        }
      }

    } else {
      std::cout << "NOT A VALID POSITION\n";
      return false;
    }
    return true;
  }

  Ship(int length, int x, int y, char dir) {
    this->length = length;
    this->x = x;
    this->y = y;
    this->dir = dir;
  }
};
