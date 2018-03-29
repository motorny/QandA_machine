#ifndef __QUESTION_ANSWER_MACHINE_INTERFACE__
#define __QUESTION_ANSWER_MACHINE_INTERFACE__
#pragma once

#include <string>
#include <fstream>

#include "QADataBase.h"


class IQAMachineCore
{
public:

	virtual void askQuestion(std::string question) = 0;
	
	virtual std::string getAnswer(void) = 0;

	virtual void LearnFromTSV(const std::string & fileName, const std::string &rejectedWordsFileName) = 0;

    virtual ~IQAMachineCore() {};
};

#endif // !__QUESTION_ANSWER_MACHINE_INTERFACE__

