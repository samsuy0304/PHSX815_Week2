#include <iostream>
#include <fstream>

#include "matplotlibcpp.h"

using namespace std;

namespace plt = matplotlibcpp;

vector<double> GetLineValues(std::string& line);

// main function for compiled executable CoinAnalysis
int main(int argc, char* argv[]){
  bool printhelp = false;

  // single coin-toss probability for hypothesis 0
  double p0 = 0.5;

  // single coin-toss probability for hypothesis 1
  double p1 = 0.9;

  bool haveH0 = false;
  string InputFile0;

  bool haveH1 = false;
  string InputFile1;
  
  // parsing any command line options added by the user
  for(int i = 0; i < argc; i++){
    if(strncmp(argv[i],"--help", 6) == 0){
      printhelp = true;
    }
    if(strncmp(argv[i],"-h", 2) == 0){
      printhelp = true;
    }
    if(strncmp(argv[i],"-prob0", 6) == 0){
      i++;
      double prob0 = std::stod(argv[i]);
      if(prob0 >= 0. && prob0 <= 1.)
	p0 = prob0;
    }
    if(strncmp(argv[i],"-prob1", 6) == 0){
      i++;
      double prob1 = std::stod(argv[i]);
      if(prob1 >= 0. && prob1 <= 1.)
	p1 = prob1;
    }
    if(strncmp(argv[i],"-input0", 7) == 0){
      i++;
      InputFile0 = string(argv[i]);
      haveH0 = true;
    }
    if(strncmp(argv[i],"-input1", 7) == 0){
      i++;
      InputFile1 = string(argv[i]);
      haveH1 = true;
    }
  }

  // print the executable usage options if the user adds -h or --help
  if(printhelp || !haveH0){
    cout << "Usage: " << argv[0] << " [options]" << endl;
    cout << "  options:" << endl;
    cout << "   --help(-h)          print options" << endl;
    cout << "   -input0 [filename]  name of file for H0 data" << endl;
    cout << "   -input1 [filename]  name of file for H1 data" << endl;
    cout << "   -prob0 [number]     probability of 1 for single toss for H0" << endl;
    cout << "   -prob1 [number]     probability of 1 for single toss for H1" << endl;
   
    return 0;
  }

  string line;
  vector<double> lineVals;

  int Ntoss;
  vector<double> Npass0;
  vector<double> LogLikeRatio0;
  vector<double> Npass1;
  vector<double> LogLikeRatio1;

  double Npass_min = 1e8;
  double Npass_max = -1e8;
  double LLR_min = 1e8;
  double LLR_max = -1e8;
  
  // read H0 input file
  std::ifstream ifile0(InputFile0.c_str());
  if(!ifile0.is_open()){
    std::cout << "Unable to read input data file " << InputFile0 << std::endl;
    return 0;
  }
  while(getline(ifile0,line)){
    lineVals = GetLineValues(line);

    // number of tosses in this experiment
    Ntoss = lineVals.size();
    double Npass = 0;
    double LLR = 0.;
    for(int i = 0; i < Ntoss; i++){
      Npass += lineVals[i];
      // adding LLR for this toss
      if(lineVals[i] >= 1)
	LLR += log( p1/p0 );
      else
	LLR += log( (1.-p1)/(1.-p0) );
    }
    if(Npass < Npass_min)
      Npass_min = Npass;
    if(Npass > Npass_max)
      Npass_max = Npass;
    if(LLR < LLR_min)
      LLR_min = LLR;
    if(LLR > LLR_max)
      LLR_max = LLR;
    Npass0.push_back(Npass);
    LogLikeRatio0.push_back(LLR);
  }
  ifile0.close();

  // read H1 input file
  while(haveH1){
    std::ifstream ifile1(InputFile1.c_str());
    if(!ifile1.is_open()){
      std::cout << "Unable to read input data file " << InputFile1 << std::endl;
      haveH1 = false;
      break;
    }
    while(getline(ifile1,line)){
      lineVals = GetLineValues(line);
      
      // number of tosses in this experiment
      Ntoss = lineVals.size();
      double Npass = 0;
      double LLR = 0.;
      for(int i = 0; i < Ntoss; i++){
      Npass += lineVals[i];
      // adding LLR for this toss
      if(lineVals[i] >= 1)
	LLR += log( p1/p0 );
      else
	LLR += log( (1.-p1)/(1.-p0) );
      }
      if(Npass < Npass_min)
	Npass_min = Npass;
      if(Npass > Npass_max)
	Npass_max = Npass;
      if(LLR < LLR_min)
	LLR_min = LLR;
      if(LLR > LLR_max)
	LLR_max = LLR;
      Npass1.push_back(Npass);
      LogLikeRatio1.push_back(LLR);
    }
    ifile1.close();
    break;
  }
  
  char title[400];
  sprintf(title, "%d tosses / experiment", Ntoss);
  
  // Npass figure
  plt::figure();
  plt::xlim(Npass_min, Npass_max);
  plt::named_hist("assuming $\\mathbb{H}_0$", Npass0, Ntoss+1, "b", 0.5);
  if(haveH1){
    plt::named_hist("assuming $\\mathbb{H}_1$", Npass1, Ntoss+1, "g", 0.7);
    plt::legend(); 
  }
  plt::title(title); 
  plt::xlabel("$\\lambda = N_{pass}$");
  plt::ylabel("Counts");
  plt::grid();

  // LLR figure
  plt::figure();
  plt::xlim(LLR_min, LLR_max);
  plt::named_hist("assuming $\\mathbb{H}_0$", LogLikeRatio0, Ntoss+1, "b", 0.5);
  if(haveH1){
    plt::named_hist("assuming $\\mathbb{H}_1$", LogLikeRatio1, Ntoss+1, "g", 0.7);
    plt::legend(); 
  }
  plt::title(title); 
  plt::xlabel("$\\lambda = \\log({\\cal L}_{\\mathbb{H}_{1}}/{\\cal L}_{\\mathbb{H}_{0}})$");
  plt::ylabel("Counts");
  plt::grid();

  plt::show();
  
}

vector<double> GetLineValues(std::string& line){
  // remove leading whitespace
  while(line[0] == string(" ")[0])
    line.erase(0,1);

  vector<double> ret;
  string num;
  while(line.find(" ") != string::npos){
    size_t p = line.find(" ");
    num = line.substr(0,p);
    line.erase(0,p+1);
    while(line[0] == string(" ")[0])
      line.erase(0,1);

    ret.push_back(stod(num));
  }
  
  return ret;
}
