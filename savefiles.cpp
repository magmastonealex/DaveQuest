#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <stdio.h>



bool fileExists(const char *fileName) {
     std::ifstream infile(fileName);
     return infile.good();
} 

void saveFile(std::string saveFile, short x, short y){
  std::ofstream thesave;
  thesave.open (saveFile.c_str());
  char buffer [10];
  sprintf (buffer, "%d\n%d\n", x, y);
  thesave << buffer;
  thesave.close();


}