#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "QAMachineCore.h"

using namespace std;



const std::string QAMachineCore::delimetrs = " ,.!?"; // delimiters
const double threshold = 1e-5; // threshold used in evaluation relevance 


QAMachineCore::QAMachineCore()
{
}

list<pair<int, double>> QAMachineCore::findBest(vector<int> &queryInd)
{
  list<pair<int, double>> bestInd{ pair<int, double>(0, pairsQAset[0].getDistFromQuery(vocabulary, queryInd)) };
  double value = 0.0;

  // Iterate through the whole pairsQAset to find best options
  for (size_t pairInd = 1; pairInd < pairsQAset.size(); ++pairInd)
  {
    // cache value of current option
    value = pairsQAset[pairInd].getDistFromQuery(vocabulary, queryInd);
    pair<int, double> curPair(pairInd, value);

    // insert into list maintaining sort order (sorted by value)
    bestInd.insert(lower_bound(bestInd.begin(), bestInd.end(), curPair, 
      [](const pair<int, double> &left, const pair<int, double> &right)
      {
        return left.second > right.second;
      }),
      curPair);

    // keep only fixed amount of best options
    bestInd.resize(std::min(static_cast<size_t>(maxOptions), bestInd.size()));
  }

  // If very best one is so low, than any option is not good enough
  if (bestInd.front().second < threshold)
  {
    list<pair<int, double>> badOptions(maxOptions, pair<int, double>(0, -1));
    return badOptions;
  }

  return bestInd;
}


void QAMachineCore::askQuestion(std::string question)
{
  vector<int> queryInds;

  // Remember current question for furtherer use
  currentQuestion = question;

  // Get indexes of words in question
  queryInds = vocabulary.parseStrByVocabInds(question);

  // Find out what best answers are
  bestMatchInd = findBest(queryInds);
}


std::string QAMachineCore::getAnswer()
{
  if (bestMatchInd.front().second == -1)
    return "Can't find answer";

  return pairsQAset[bestMatchInd.front().first].answer;
}

template <class InputIterator, class T>
inline bool contains(InputIterator start, InputIterator end, const T& element)
{
  return find(start, end, element) != end;
}

void QAMachineCore::printAnswer(void)
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
    vector<int> indWordsCommon;

    for (int wordInd : indWordsOption)
      if (contains(indWordsQuestion.begin(), indWordsQuestion.end(), wordInd))
        indWordsCommon.push_back(wordInd);

    // Print additional debug information
    std::cout << "debug-info: <word>-<idf>"  << endl;
    for (int wordInd : indWordsCommon)
      cout << vocabulary[wordInd].word << " " << vocabulary[wordInd].idf << "| ";

    std::cout << std::endl;
    std::cout << std::endl;
#endif // NDEBUG
  }

  std::cout << "----------------------------------------------" << endl << endl;
}


void QAMachineCore::learnFromFile(const string & fileName, const std::string &rejectedWordsFileName)
{
  vocabulary.generateVocabularyFromQAFile(fileName, rejectedWordsFileName, pairsQAset);
  pairsQAset.getIndexByVocab(vocabulary);
  std::cout << "Vocabulary size: " << vocabulary.size() << endl;
}

QAMachineCore::~QAMachineCore()
{
}