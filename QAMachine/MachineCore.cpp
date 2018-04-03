#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>

#include "MachineCore.h"

using namespace std;

const std::string MachineCore::delimetrs = " ,.!?"; //!< delimiters
const double threshold = 1e-5;

MachineCore::MachineCore()
{
}


/*! \brief findBest function chooses 5 best options depending on score
 *
 *  Function creates a list of pairs with interger - index in set and
 *  double - value, corresponding to closeness of questions. New value
 *  is inserted while maintaining invariant (list is sorted by value).
 *  if no close options were found (irrelevance means that closeness is
 *  less than threshold that is a filed of core class and can be modified
 *  to represent more or less strict cut-plane of closeness). If no 
 *  relevant options were found than function a list of (0, -1). 
 *  \param count - number of options needed
 *  \param set - set pairs question-answer
 *  \param vocabulary - vocabulary with words and idf metric
 *  \param queryInd - indexes of words in asked question
 *  \return list of pairs of indexes of questions in set with related score
 */
list<pair<int, double>> findBest(int count, QAPairsSet &set,
  Vocabulary &vocabulary, vector<int> &queryInd)
{
  list<pair<int, double>> bestInd{ pair<int, double>(0, set[0].getDistFromQuery(vocabulary, queryInd)) };
  double value = 0.0;

  // Iterate through the whole set to find best options
  for (size_t pairInd = 1; pairInd < set.size(); ++pairInd)
  {
    // cache value of current option
    value = set[pairInd].getDistFromQuery(vocabulary, queryInd);
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

void MachineCore::askQuestion(std::string question)
{
  vector<int> queryInds;

  // Remember current question for furtherer use
  currentQuestion = question;


  queryInds = vocabulary.parseStrByVocabInds(question);

  bestMatchInd = findBest(maxOptions, pairsQAset, vocabulary, queryInds);
}

std::string MachineCore::getAnswer()
{
  if (bestMatchInd.front().second == -1)
    return "Can't find answer";

  return pairsQAset[bestMatchInd.front().first].answer;
}

void MachineCore::printAnswer(void)
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
  std::cout << std::endl;
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

    vector<int> indWordsQuestion = vocabulary.parseStrByVocabInds(currentQuestion);
    vector<int> indWordsOption = vocabulary.parseStrByVocabInds(pairsQAset[option.first].question);

    // Print additional debug information
    std::cout << "debug-info: <word>-<idf>"  << endl;
    for (int wordInd : indWordsQuestion)
      cout << vocabulary[wordInd].word << " " << vocabulary[wordInd].idf << "| ";

    for (int wordInd : indWordsOption)
      cout << vocabulary[wordInd].word << " " << vocabulary[wordInd].idf << "| ";

    std::cout << std::endl;
    std::cout << std::endl;
#endif // NDEBUG
  }

  std::cout << "----------------------------------------------" << endl << endl;
}

void MachineCore::learnFromTSV(const string & fileName, const std::string &rejectedWordsFileName)
{
  vocabulary.generateVocabularyFromQAFile(fileName, rejectedWordsFileName, pairsQAset);
  pairsQAset.getIndexByVocab(vocabulary);
  std::cout << "Vocabulary size: " << vocabulary.size() << endl;
}

MachineCore::~MachineCore()
{
}