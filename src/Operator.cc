# include"../include/Operator.h"
# include<string>
namespace MineClearing
{
void Operator::setn(int n_){
  n = n_;
}
int Operator::getn() const {
  return n;
}
void Operator::setMineN(int MineN_){
  MineN = MineN;
}
int Operator::getMineN() const {
  return MineN;
}

void Operator::run(){
  std::cout << ">>Welcome to MineClearing<<" << std::endl;
  std::cout << "<operations>" << std::endl;
  admin_selection_out(std::cout);
  std::cout << "enter your selection" << std::endl;
  int selection;
  std::cin >> selection;
  operate(str_selection_to_opt(selection));
}

void Operator::operate(operation_type op){
  switch(op){
    case operation_type::play :
      MC.run();
      break;
    case operation_type::change_mineC_setting :
      change_MineC_setting();
      break;
    case operation_type::not_op:
      std::cout << "it's not an option!" << std::endl;
  }
}

void Operator::change_MineC_setting(){
  std::cout << "<MineC Setting>" << std::endl;
  int Matrix_size = -1;
  int Mine_size = -1;
  while(Matrix_size<0){
    std::cout << "enter your Matrix size: " << std::endl;
    std::cout << ">";
    std::cin >> Matrix_size;
    if(Matrix_size < 0 ){
      std::cout << "Matrix size should be >0 , or enter 0 to exit(Matrix size will be 10" << std::endl;
    }else if(Matrix_size==0){
      Matrix_size = 10;
      break;
    }
  }
  while(Mine_size<0){
    std::cout << "enter your Mine size: " << std::endl;
    std::cout << ">";
    std::cin >> Mine_size;
    if(Mine_size < 0 ){
      std::cout << "Mine size should be >0 , or enter 0 to exit(Mine size will be 10" << std::endl;
    }else if(Mine_size==0){
      Mine_size = 10;
      break;
    }
  }
  MC.setMetrix(Matrix_size,Mine_size);
}

void Operator::admin_selection_out(std::ostream& PrintOut){
  std::cout << "1 play" << std::endl;
  std::cout << "2 change MineC setting " << std::endl;
}
Operator::operation_type Operator::str_selection_to_opt(int selection){
  switch (selection)
  {
  case 1:
    return operation_type::play;
  case 2:
    return operation_type::change_mineC_setting;
  default:
    return operation_type::not_op;
  }
}
} // MineClearing