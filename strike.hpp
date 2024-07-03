#include "ships.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
struct StrikeType {
  char x;
  char y;
};

class Strike {
public:
  static bool markBoard(char board[][11], char strikeBoard[][11],
                        StrikeType coordinates) {
    char validXForLeft[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char validYForDown[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

    for (int i = 1; i < 11; i++) {
      for (int j = 1; j < 11; j++) {
        if (coordinates.x == validXForLeft[j - 1] &&
            coordinates.y == validYForDown[i - 1] && board[i][j] != 'X' &&
            board[i][j] != '0') {
    //      std::cout << "PLACED X " << i << j << "\n";
          if (board[i][j] == 'O') {

            board[i][j] = '0';
            strikeBoard[i][j] = '0';
          } else {

            board[i][j] = 'X';
            strikeBoard[i][j] = 'X';
          }

          return true;
        }
      }
    }

    return false;
  }

  static StrikeType generateRandomStrike() {
    StrikeType strike;
    Commands tempCommands;

    tempCommands = Utils::genRandomCommands();

    strike.x = tempCommands.x;
    strike.y = tempCommands.y;

    return strike;
  }

  static bool placeStrike(char strikeBoard[][11], char board[][11],
                          StrikeType coordinates, std::string userType) {
    if (userType == "player") {
      // modify board  and strike
      bool success = markBoard(board, strikeBoard, coordinates);
      return success;
    } else if (userType == "enemy") {
      bool success = markBoard(board, strikeBoard, coordinates);
      return success;
    } else {
      std::cout << "NOT VALID USER TYPE FOR STRIKE";
      exit(1);
    }
  }
};
