#include<iostream>
#include<string>
# include"include/MineClearing.h"

int main(){
  std::srand((unsigned)std::time(NULL)*10);
  MineClearing::MineC mc(10,10);
  mc.run();
  return 0;
}