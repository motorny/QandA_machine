#ifndef __QUESTION_ANSWER_MACHINE_INTERFACE__
#define __QUESTION_ANSWER_MACHINE_INTERFACE__
#pragma once

#include <string>
#include <fstream>


class IMachineCore
{
public:

	virtual void askQuestion(std::string question) = 0;
	
	virtual std::string getAnswer(void) = 0;

  virtual void printAnswer(void) = 0;

	virtual void learnFromTSV(const std::string & fileName, const std::string &rejectedWordsFileName) = 0;

    virtual ~IMachineCore() {};
};

#endif // !__QUESTION_ANSWER_MACHINE_INTERFACE__

