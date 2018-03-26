#include <iostream>
#include "QAMachineCore.h"

int main(int argc, char* argv[])
{
    QAMachineCore core;

    if (argc > 1)
    {
        std::cout << argv[1] << std::endl;
    }
	
	std::cout << "QAMachine" << std::endl;

	return EXIT_SUCCESS;
}   