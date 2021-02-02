# if !defined(M_OPERATOR_H_)
# define M_OPERATOR_H_
# include"MineClearing.h"
namespace MineClearing
{
class Operator{
  public:
  enum operation_type{exit,play,change_mineC_setting,not_op};
  Operator():n(10),MC(10,10),MineN(10){}
  void setn(int n_);
  int getn() const ;
  void setMineN(int MineN_);
  int getMineN() const ;
  void run();
  bool operate(operation_type op);
  void change_MineC_setting();
  void admin_selection_out(std::ostream& PrintOut);
  operation_type str_selection_to_opt(int selection);
  private:
  MineClearing::MineC MC;
  int n;
  int MineN;
};
} // MineClearing
# endif