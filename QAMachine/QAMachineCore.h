#ifndef __QUESTION_ANSWER_MACHINE_CORE__
#define __QUESTION_ANSWER_MACHINE_CORE__

#include <string>
#include <vector>

#include "IQAMachineCore.h"
#include "QADataBase.h"

class WordPair {
public:
  WordPair(const std::string &s, double d)
  {
    str = s;
    idf = d;
  }
  std::string str;
  double idf;
};

class QAPair {
public:
  QAPair(const std::string &q, const std::string &a)
  {
    question = q;
    answer = a;
  };
  std::string question;
  std::string answer;
  std::vector<int> wordIndeces;
  double invEuqlidSize;
};


class QAMachineCore : public IQAMachineCore
{
public:

  QAMachineCore(void);

  void askQuestion(std::string question) override;

  std::string getAnswer() override;

  void LearnFromTSV(const std::string & fileName, const std::string &rejectedWordsFileName) override;

  ~QAMachineCore();

private:
  std::vector<WordPair> vocabulary;
  std::vector<std::string> rejectedWords;

  std::vector<QAPair> questAnswArr;

  static const std::string delimetrs;
  int questionsCnt = 0;
  int answerInd = 0;
};



#endif // !__QUESTION_ANSWER_MACHINE_CORE__
