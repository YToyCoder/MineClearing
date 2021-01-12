# if !defined(_MINECLEARING_H)
# define _MINECLEARING_
# include<iostream>
# include<vector>
# include<cstdlib>
# include<ctime>
namespace MineClearing
{
# if !defined(MCSymbol)
# define MCSymbol
# define MC_M -1 // 未点击地雷
# define MC_E 9  // 未点击空块
# define MC_B 0  // 已挖出的周围地雷数为 0
# define MC_X 10 // 已挖出的地雷
# endif

// get a uniform distribution between maxVal and minVal
double Uniform(double minVal , double maxVal);

class MCMetrix{
  public:
  MCMetrix(int inN,int inMineN);
  void setLandMine(int inMineN);
  void PrintTo(std::ostream& );
  int getItemInMetrix(int row, int col);
  void setItemInMetrix(int row, int col , int Item);
  int getSize();
  private:
  std::vector<std::vector<int> > realMCMetrix;
  int n;
  int MineN;
};
class KeyV{
  public:
  KeyV(int row_,int col_):row(row_),col(col_){}
  int row;
  int col;
};
class MineC{
  public:
  MineC();
  MineC(int inN,int inMineN);
  void setMetrix(int  inN,int inMineN);
  void click(int row,int col);
  std::vector<KeyV> realClick(KeyV);
  void reset();
  bool valid(int row,int col);
  bool clicked(int row ,int col);
  int  findNeighborsLandMine(int row,int col);
  void PrintTo(std::ostream& PrintOut);
  void run();
  private:
  MCMetrix MC;
};
class ClickMine{
  public:
  ClickMine():msg("you lose!"){}
  std::string GetMsg() const;
  private:
  std::string msg;
};
namespace MCExceptions{
class MCBaseException{
  public:
  MCBaseException( std::string description);
  std::string what() const ;
  protected:
  std::string desc;
};

class outOfMetrixRange : public MCBaseException{
  public:
  outOfMetrixRange(int row,int col, int n);
};

} // namespace MCExceptions

} // namespace MineClearing

# endif