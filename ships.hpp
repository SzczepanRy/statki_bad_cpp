#pragma once

#include <iostream>
class Ship {
public:
  int length;
  int x;
  int y;
  char dir;

  void test() { std::cout << "test on Ship called"; }
  Ship(int length, int x, int y, char dir) {
    this->length = length;
    this->x = x;
    this->y = y;
    this->dir = dir;
  }
};
