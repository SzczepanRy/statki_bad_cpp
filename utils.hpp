#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <chrono>
#include <random>
struct Commands {
  char x;
  char y;
  char dir;
};

class Utils {
private:
  char commands[3];

public:
  Commands genRandomCommands() {

    char ForLeft[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char ForDown[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    char ForDirection[2] = {'l', 'd'};
    Commands commands{
      x : ForLeft[(randomNumber(0, 9))],
      y : ForDown[(randomNumber(0, 9))],
      dir : ForDirection[(randomNumber(0,1))]
    };

    return commands;
  }

  int randint(std::mt19937_64 &rng, int lbound, int ubound) {
    return rng() % (ubound - lbound + 1) + lbound;
  }

  int randomNumber(int min , int max) {
    // Seed the RNG so it doesn't generate the same
    // numbers every time
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::mt19937_64 rng(seed);

    // Generate a random number between 5 and 20,
    // inclusive
    return randint(rng, min,max);

  }

  static bool checkCharArr(char *array, int size, char serchTerm) {
    for (int i = 0; i < size; i++) {
      if (array[i] == serchTerm) {
        return true;
      }
    }

    std::cout << "CHECK ARRAY FALED\n";

    return false;
  }

  bool vaildateCommand(std::string command) {
    char numbersArray[] = {'*', '0', '1', '2', '3', '4',
                           '5', '6', '7', '8', '9'};
    char lettersArray[] = {'*', 'a', 'b', 'c', 'd', 'e',
                           'f', 'g', 'h', 'i', 'j'};

    char dirArray[] = {'l', 'd'};

    if (command.size() != 3) {
      return false;
    }

    bool valid1 = false;
    bool valid2 = false;
    bool valid3 = false;

    for (int i = 0; i < (int)command.size(); i++) {
      this->commands[i] = command[i];
//      std::cout << "log form validation for  " << command[i] << "\n";
      if (i == 0) {
        for (int j = 1; j < 11; j++) {
          if (numbersArray[j] == command[i]) {
            valid1 = true;
          }
        }
      }
      if (i == 1) {
        for (int j = 1; j < 11; j++) {
          if (lettersArray[j] == command[i]) {
            valid2 = true;
          }
        }
      }
      if (i == 2) {
        for (int j = 0; j < 2; j++) {
          if (dirArray[j] == command[i]) {
            valid3 = true;
          }
        }
      }
    }
    // chech if valid
  //  std::cout << valid1 << "  " << valid2 << "  " << valid3 << "\n";
    if (!valid1 || !valid2 || !valid3) {
      return false;
    }

    return true;
  }

  Commands getCommands(std::string command) {
    bool valid;

    valid = this->vaildateCommand(command);

    Commands commands;
  //  std::cout << this->commands[0] << this->commands[1] << this->commands[2]
   //           << "\n";
   // std::cout << "\n";
    if (valid) {
      commands.x = this->commands[0];
      commands.y = this->commands[1];
      commands.dir = this->commands[2];

    } else {
      std::cout << "NOT VALID INPUT RESTART PROGRAM";
      exit(1);
    }

    return commands;
  }
};
