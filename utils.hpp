#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>


struct Commands {
  char x;
  char y;
  char dir;
};

class Utils {
private:
  char commands[3];

public:

   static bool checkCharArr(char* array , int size, char serchTerm){
      for(int i = 0 ; i < size ; i++){
          if(array[i] == serchTerm){
              return  true;
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
      std::cout << "log form validation for  "<< command[i] << "\n";
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
    std::cout << valid1 << "  "<< valid2 << "  "<< valid3<< "\n";
    if (!valid1 || !valid2 || !valid3) {
      return false;
    }

    return true;
  }


  Commands getCommands(std::string command) {
    bool valid;

    valid = this->vaildateCommand(command);

    Commands commands;
    std::cout << this->commands[0] << this->commands[1] << this->commands[2] << "\n";
    std::cout<< "\n";
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
