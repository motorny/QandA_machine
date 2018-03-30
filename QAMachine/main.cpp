#include <iostream>
#include "QAMachineCore.h"
#include <iostream>
#include <locale>
#include <Windows.h>

int main(int argc, char* argv[])
{
  setlocale(LC_ALL, "Russian");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  /*
  !!!SET CONSOLE FONT TO LUCIDA COLONAS!!!
  */


  QAMachineCore core;

  core.LearnFromTSV("quiz.txt", "rejected.txt");

  //std::cout << "QAMachine" << std::endl;

  std::cout << "LETS GO\n\n" << std::endl;
  std::string str;
  while (std::getline(std::cin, str))
  {
    
    core.askQuestion(str);
    core.PrintAnswer();

  }




  return EXIT_SUCCESS;
}