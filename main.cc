#include<iostream>
#include<string>
# include"include/Operator.h"
// # include"include/MineClearing.h"

int main(){
  std::srand((unsigned)std::time(NULL)*10);
  // MineClearing::MineC mc(10,10);
  // try{
  //   mc.run();
  // }catch(MineClearing::ClickMine CM){
  //   std::cout << CM.GetMsg();
  // }
  MineClearing::Operator OP;
  OP.run();
  return 0;
}