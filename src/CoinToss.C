#include <iostream>
#include <fstream>

#include "Random.hh"

using namespace std;

// main function for compiled executable CoinToss
int main(int argc, char* argv[]){
  bool printhelp = false;
  long seed = 5555;

  // single coin-toss probability for "1"
  double p = 0.5;

  // Number of coin tosses (per experiment)
  int Ntoss = 1;

  // Number of experiments
  int Nexp = 1;

  bool doOutputFile = false;
  string OutputFileName;
  

  // parsing any command line options added by the user
  for(int i = 0; i < argc; i++){
    if(strncmp(argv[i],"--help", 6) == 0){
      printhelp = true;
    }
    if(strncmp(argv[i],"-h", 2) == 0){
      printhelp = true;
    }
    if(strncmp(argv[i],"-seed", 5) == 0){
      i++;
      seed = std::stol(argv[i]);
    }
    if(strncmp(argv[i],"-prob", 5) == 0){
      i++;
      double prob = std::stod(argv[i]);
      if(prob >= 0. && prob <= 1.)
	p = prob;
    }
    if(strncmp(argv[i],"-Ntoss", 6) == 0){
      i++;
      int Nt = std::stoi(argv[i]);
      if(Nt > 0)
	Ntoss = Nt;
    }
    if(strncmp(argv[i],"-Nexp", 4) == 0){
      i++;
      int Ne = std::stoi(argv[i]);
      if(Ne > 0)
	Nexp = Ne;
    }
    if(strncmp(argv[i],"-output", 7) == 0){
      i++;
      OutputFileName = string(argv[i]);
      doOutputFile = true;
    }
  }

  // print the executable usage options if the user adds -h or --help
  if(printhelp){
    cout << "Usage: " << argv[0] << " [options]" << endl;
    cout << "  options:" << endl;
    cout << "   --help(-h)          print options" << endl;
    cout << "   -seed [number]      random seed to use" << endl;
    cout << "   -prob [number]      probability of 1 for single toss" << endl;
    cout << "   -Ntoss [number]     number of coin tosses per experiment" << endl;
    cout << "   -Nexp [number]      number of experiments" << endl;
    cout << "   -output [filename]  name of ouptut file" << endl;
   
    return 0;
  }

  // declare an instance of our Random class
  Random  random(seed);

  if(doOutputFile){ // write experiments to file
    ofstream outfile;
    outfile.open(OutputFileName.c_str());
    for(int e = 0; e < Nexp; e++){
      for(int t = 0; t < Ntoss; t++){
	outfile << random.Bernoulli(p) << " ";
      }
      outfile << endl;
    }
    outfile.close();
  } else { // write experiments to stdout
    for(int e = 0; e < Nexp; e++){
      for(int t = 0; t < Ntoss; t++){
	cout << random.Bernoulli(p) << " ";
      }
      cout << endl;
    }
  }
  
}

