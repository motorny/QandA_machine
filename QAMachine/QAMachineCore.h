#ifndef __QUESTION_ANSWER_MACHINE_CORE__
#define __QUESTION_ANSWER_MACHINE_CORE__

#include <string>
#include <vector>

#include "IQAMachineCore.h"
#include "QAVocabulary.h"
#include "QApairsQAset.h"


class QAMachineCore : public IQAMachineCore
{
public:

  QAMachineCore(void);

  void askQuestion(std::string question) override;

  std::string getAnswer() override;

  void PrintAnswer(void);

  void LearnFromTSV(const std::string & fileName, const std::string &rejectedWordsFileName) override;

  ~QAMachineCore();

private:
  QAVocabulary vocabulary;
  QApairsQAset pairsQAset;
  

  static const std::string delimetrs;

  int answerInd = 0;
};

#endif // !__QUESTION_ANSWER_MACHINE_CORE__