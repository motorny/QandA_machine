#include <iostream>
#include "QAMachineCore.h"
#include <iostream>
#include <locale>
#include <Windows.h>

#pragma warning(disable: 4100)

/*
Overcoming Qt build errors:
- go to solution explorer, rightclick on solution and choose " Change solution's Qt vesion"
- go to solution explorer, rightclick on project "test" and choose "Qt project settings", then edit "Qt version field"
*/

int main(int argc, char* argv[])
{
  setlocale(LC_ALL, "Russian");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  QAMachineCore core;

  std::cout << "For working with russian language, please, set console font to \"Lucida Console\"" << std::endl;
  std::cout << "Parsing ..." << std::endl;
  core.learnFromFile("../dataset/quiz.txt", "../dataset/rejected.txt");


  std::cout << "LETS GO\n\n" << std::endl;
  std::string str = "";
  while (std::getline(std::cin, str))
  {
    std::cout << "Question: " <<  str << std::endl;
    core.askQuestion(str);
    std::cout << core.getAnswer() << std::endl << std::endl;
 
    core.askQuestion(str);
    core.printAnswer();
  }

  return EXIT_SUCCESS;
}