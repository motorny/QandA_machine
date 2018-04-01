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

  std::string currentQuestion; //!< Current question asked
                               /*!< Is used in analysis that might be needed after
                                *   processing in askQuestion is complete */

  static const std::string delimetrs;

  std::vector<std::pair<int, double>> bestMatchInd; //!< Array of best options
                                                    /*!< Holds indexes to words in set
                                                     *   pairsQAset, as well as the score  
                                                     *   corresponding to the closeness to 
                                                     *   currently asked question */

  static const size_t maxOptions = 5; //!< Number of top options considered for answer
};

#endif // !__QUESTION_ANSWER_MACHINE_CORE__