# include<string>
# include<vector>
# include<iostream>
# include<sstream>
# include"../include/MineClearing.h"
namespace MineClearing
{
// get a uniform distribution between maxVal and minVal
double Uniform(double minVal , double maxVal){
  // std::srand((unsigned)std::time(NULL)*10);
  return ((double)rand()/32767.0) * (maxVal - minVal)+minVal;
}

MCMetrix::MCMetrix(int inN,int inMineN):realMCMetrix(),n(inN),MineN(inMineN){
  // std::cout << realMCMetrix.size() << std::endl;
  std::vector<int> tmp(n,MC_E);
  for(int row=0 ; row<inN ; ++row){
    realMCMetrix.push_back(tmp);
  }
  setLandMine(MineN);
}

// set Landmine for MCMetrix
void MCMetrix::setLandMine(int inMineN){
  int remainLandMine = MineN;
  double LandMineForEveryRow = MineN/(double)n;
  int maxLandMineNForEveryRow = LandMineForEveryRow + 
                                ((int)LandMineForEveryRow < LandMineForEveryRow ? 1:0);
  for(int row = 0 ; row<n && remainLandMine > 0 ; ++row){
    // std::cout << " out loop " << std::endl;
    int MineNInCurrentRow = (int)Uniform(0,maxLandMineNForEveryRow)+1;
    MineNInCurrentRow = MineNInCurrentRow <= remainLandMine ? MineNInCurrentRow : remainLandMine;
    std::vector<int> VForSelecting;
    for(int colNum=0 ; colNum<n ;){
      VForSelecting.push_back(colNum++);
    }
    for(int MineNForSetted=0 ; MineNForSetted < MineNInCurrentRow ; ++MineNForSetted){
      int selectedLocation = Uniform(0,n);
      std::vector<int>::iterator deleteIter = VForSelecting.begin();
      for(;deleteIter!=VForSelecting.end() && selectedLocation>0;){
        ++deleteIter;
        --selectedLocation;
      }
      realMCMetrix[row][*deleteIter] = MC_M;
      // std::cout << "here" << std::endl;
      VForSelecting.erase(deleteIter);
    }
    remainLandMine -= MineNInCurrentRow;
  }
}

int MCMetrix::getSize(){
  return n;
}

int MCMetrix::getItemInMetrix(int row,int col){
  return realMCMetrix[row][col];
}

void MCMetrix::setItemInMetrix(int row,int col, int Item){
  realMCMetrix[row][col] = Item;
}

// Print MCMetrix to an ostream
void MCMetrix::PrintTo(std::ostream& printOut){
  int rowCount = 0;
  // print col number
  printOut << std::cout.width(2) << 0 << " ";
  for(int colNumber=0 ; colNumber < realMCMetrix.size() ;++colNumber){
    printOut << std::cout.width(2) << colNumber << " ";
  }
  printOut << std::endl;
  for(int colNumber=0 ; colNumber <= realMCMetrix.size() ;++colNumber){
    printOut <<"----";
  }
  printOut << std::endl;
  for ( auto row : realMCMetrix){
    // print mextrix
    for(int colInRow=0 ; colInRow < realMCMetrix.size() ; ++colInRow ){
      if(colInRow==0){
        printOut << std::cout.width(2)  << rowCount << "|";
      }
      if(row[colInRow] == MC_M || row[colInRow] == MC_E){
        printOut << std::cout.width(2) << "?" << " ";
      }else if (row[colInRow] == MC_X){
        printOut << "X" << " ";
      }else{
        printOut << std::cout.width(2) << row[colInRow] << " " ;
      }
    }
    ++rowCount;
    printOut << std::endl;
  }
}

// print origin
void MCMetrix::OriginPrint(std::ostream& printOut){
  for(auto row : realMCMetrix){
    for( auto colInRow : row ){
      printOut << colInRow << " ";
    }
    printOut << std::endl;
  }
}

MineC::MineC():MC(MCMetrix(10,10)){}

MineC::MineC(int inN , int inMineN): MC(MCMetrix(inN,inMineN)){}

void MineC::setMetrix( int inN,int inMineN){
  MC = MCMetrix(inN,inMineN);
}

void MineC::click(int row, int col){
  if(! valid(row,col)){
    throw MCExceptions::outOfMetrixRange(row,col,MC.getSize());
  }else{
    std::vector<KeyV> ToClick = realClick(KeyV(row,col));
    while(ToClick.size()){
      std::vector<KeyV>::iterator deleteIter = ToClick.begin();
      std::vector<KeyV> newToClick = realClick(*deleteIter);
      ToClick.erase(deleteIter);
      for(auto itToClick:newToClick){
        ToClick.push_back(itToClick);
      }
    }
  }
}

std::vector<KeyV> MineC::realClick(KeyV toClick){
  std::vector<KeyV> newToClick;
  if(MC.getItemInMetrix(toClick.row,toClick.col) == MC_M){
    MC.setItemInMetrix(toClick.row,toClick.col,MC_X);
    throw ClickMine();
  }else{
    MC.setItemInMetrix(toClick.row,toClick.col,findNeighborsLandMine(toClick.row,toClick.col));
    if(MC.getItemInMetrix(toClick.row,toClick.col)==MC_B){
      int minRowNum = toClick.row - 1 >= 0 ? toClick.row - 1: toClick.row;
      int maxRowNum = toClick.row + 1 < MC.getSize() ? toClick.row + 1 : toClick.row;
      int minColNum = toClick.col - 1 >= 0 ? toClick.col - 1: toClick.col;
      int maxColNum = toClick.col + 1 < MC.getSize() ? toClick.col + 1 : toClick.col;
      for(;minRowNum<=maxRowNum;++minRowNum){
        for(int minColNumTmp=minColNum;minColNumTmp<=maxColNum;++minColNumTmp){
          if(!clicked(minRowNum,minColNumTmp)){
            newToClick.push_back(KeyV(minRowNum,minColNumTmp));
          }
        }
      }
    }
  }
  return newToClick;
}

void MineC::reset(){
  MC = MCMetrix(10,10);
}

bool MineC::valid(int row, int col){
  if( row >= 0 && row < MC.getSize()){
    if( col >= 0 && col < MC.getSize()){
      return true;
    }else{
      return false;
    }
  }else{
    return false;
  }
}

bool MineC::clicked(int row,int col){
  if(MC.getItemInMetrix(row,col) >= 0 && MC.getItemInMetrix(row,col)< 9){
    return true;
  }else{
    return false;
  }
}

int MineC::findNeighborsLandMine(int row,int col){
  int minRowNum = row - 1 >= 0 ? row - 1: row;
  int maxRowNum = row + 1 < MC.getSize() ? row + 1 : row;
  int minColNum = col - 1 >= 0 ? col - 1: col;
  int maxColNum = col + 1 < MC.getSize() ? col + 1 : col;
  int NeighborsLandMine = 0;
  for(;minRowNum<= maxRowNum;++minRowNum){
    for(int minColNumTmp = minColNum;minColNumTmp<= maxColNum;++minColNumTmp){
      if(MC.getItemInMetrix(minRowNum,minColNumTmp)==MC_M){
        ++NeighborsLandMine;
      }
    }
  }
  return NeighborsLandMine;
}

void MineC::PrintTo(std::ostream& PrintOut){
  MC.PrintTo(PrintOut);
}

std::string ClickMine::GetMsg() const{
  return msg;
}

void MineC::run(){
  std::string row("");
  std::string col("");
  while(row != "#"){
    PrintTo(std::cout);
    // MC.OriginPrint(std::cout);
    std::cout << "input click row and col (like 1 2)\nor input # to exit" << std::endl;
    std::cin >> row >> col;
    if(row != "#"){
      try{
        click(std::stoi(row),std::stoi(col));
      }catch(MCExceptions::outOfMetrixRange e){
        std::cout << e.what() << std::endl;
      }catch(ClickMine CM){
        std::cout << CM.GetMsg() << std::endl;
        std::string question("");
        std::cout << "Do you want start again?\nY for yes \nor random words to exit" << std::endl;
        std::cin >> question;
        if(question!="Y"){
          throw CM;
        }
        reset();
      }
    }
  }
}

namespace MCExceptions{
MCBaseException::MCBaseException( std::string description):desc(description){}

std::string MCBaseException::what() const{
  return desc;
}

outOfMetrixRange::outOfMetrixRange(int row,int col, int n):MCBaseException(""){
  std::string desc;
  if(row >= 0 && row < n){
    desc += "col is out of range\n";
    desc += "col range is [0," + std::to_string(n) + "]\\";
  }else{
    desc += "row is out of range\n";
    desc += "row range is [0," + std::to_string(n) + "]\\";
    if(col >= 0 && col < n){
      desc += "col is out of range\n";
      desc += "col range is [0," + std::to_string(n) + "]\\";
    }
  }
}
} // namespace MCExceptions
} // namespace MineClearing