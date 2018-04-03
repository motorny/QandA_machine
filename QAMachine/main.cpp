#include <iostream>
#include "MachineCore.h"
#include <iostream>
#include <locale>
#include <Windows.h>

#pragma warning(disable: 4100)

int main(int argc, char* argv[])
{
  setlocale(LC_ALL, "Russian");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  MachineCore core;

  core.learnFromTSV("quiz.txt", "rejected.txt");

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