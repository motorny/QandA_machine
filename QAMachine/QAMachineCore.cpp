#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>

#include "QAMachineCore.h"

using namespace std;

const std::string QAMachineCore::delimetrs = " ,.!?"; //!< delimiters
const double threshold = 1e-5;

QAMachineCore::QAMachineCore()
{
}


/*! \brief findBest function chooses 5 best options depending on score
 *
 *  \param count - number of options needed
 *  \param set - set pairs question-answer
 *  \param vocabulary - vocabulary with words and idf metric
 *  \param queryInd - indexes of words in asked question
 *  \return list of pairs of indexes of questions in set with related score
 */
list<pair<int, double>> findBest(int count, QApairsQAset &set,
  QAVocabulary &vocabulary, vector<int> &queryInd)
{
  list<pair<int, double>> bestInd{ pair<int, double>(0, set[0].GetDistFromQuery(vocabulary, queryInd)) };
  double value = 0.0;

  // Iterate through the whole set to find best options
  for (size_t pairInd = 1; pairInd < set.size(); ++pairInd)
  {
    // cache value of current option
    value = set[pairInd].GetDistFromQuery(vocabulary, queryInd);
    pair<int, double> curPair(pairInd, value);

    // insert into list maintaining sort order (sorted by value)
    bestInd.insert(lower_bound(bestInd.begin(), bestInd.end(), curPair, 
      [](const pair<int, double> &left, const pair<int, double> &right)
      {
        return left.second > right.second;
      }),
      curPair);

    // keep only fixed amount of best options
    bestInd.resize(std::min(static_cast<size_t>(count), bestInd.size()));
  }

  // If very best one is so low, than any option is not good enough
  if (bestInd.front().second < threshold)
  {
    list<pair<int, double>> badOptions(count, pair<int, double>(0, -1));
    return badOptions;
  }

  return bestInd;
}

void QAMachineCore::askQuestion(std::string question)
{
  vector<int> queryInds;

  // Remember current question for furtherer use
  currentQuestion = question;


  queryInds = vocabulary.ParseStrByVocabInds(question);

  bestMatchInd = findBest(maxOptions, pairsQAset, vocabulary, queryInds);
}

std::string QAMachineCore::getAnswer()
{
  if (bestMatchInd.front().second == -1)
    return "Can't find answer";

  return pairsQAset[bestMatchInd.front().first].answer;
}

void QAMachineCore::PrintAnswer(void)
{
  // Check if answer is valid
  if (bestMatchInd.front().second == -1)
  {
    std::cout << "There is no simular question, so we can't get answer!" << endl;
    
    return;
  }

  // Present best option as answer
  std::cout << "----------------------------------------------" << endl;
  std::cout << "Closest question: " << pairsQAset[bestMatchInd.front().first].question <<
     " -> " << pairsQAset[bestMatchInd.front().first].answer << "(" << bestMatchInd.front().second << ")" << endl;
  std::cout << ">> Other options: " << endl;

  // list other options from bestMatch as well
  // format: >>>> Question: <question> -> <answer> <score>
  for (auto const &option : bestMatchInd)
  {
    // Do not show results if they are not much relevant
    if (option.second < threshold)
      break;

    std::cout << ">>>> Question: " << pairsQAset[option.first].question << " -> " <<
      pairsQAset[option.first].answer << " (" << option.second << ")" << endl;

#ifndef NDEBUG

/*    istringstream stringStream(currentQuestion);

    vector<QAVocabulary::WordPair> words{ istream_iterator<string>(stringStream),
                                          istream_iterator<string>() };
*/
    // Print additional debug information
    std::cout << "debug-info: "  << endl;
    

#endif // NDEBUG
  }

  std::cout << "----------------------------------------------" << endl << endl;
}

void QAMachineCore::LearnFromTSV(const string & fileName, const std::string &rejectedWordsFileName)
{
  vocabulary.GenerateVocabularyFromQAset(fileName, rejectedWordsFileName, pairsQAset);
  pairsQAset.IndexByVocab(vocabulary);
  std::cout << "Vocabulary size: " << vocabulary.size() << endl;
}

QAMachineCore::~QAMachineCore()
{
}