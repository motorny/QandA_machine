#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>

#include "QAMachineCore.h"

using namespace std;

const std::string QAMachineCore::delimetrs = " ,.!?";

QAMachineCore::QAMachineCore()
{
}

//! A function to find best options for answers
/*! \brief findBest function chooses 5 best options depending on score
 *
 *  \param count - number of options needed
 *  \param set - set pairs question-answer
 *  \param vocabulary - vocabulary with words and idf metric
 *  \param queryInd - indexes of words in asked question
 *  \return vector of pairs of indexes of questions in set with related score
 */
vector<pair<int, double>> findBest(int count, QApairsQAset &set,
  QAVocabulary &vocabulary, vector<int> &queryInd)
{
  vector<pair<int, double>> bestInd; //!< bestInd accumulates best option

  bestInd.resize(1);
  // insert first element to be able to compare
  bestInd[0] = pair<int, double>(0, set[0].GetDistFromQuery(vocabulary, queryInd));

  double value = 0.0;
  // Iterate through the whole set to find best options
  for (size_t pairInd = 1; pairInd < set.size(); ++pairInd)
  {
    // cache value of current option
    value = set[pairInd].GetDistFromQuery(vocabulary, queryInd);

    // Find place for insertion
    size_t insertIndex = bestInd.size() - 1;
    while (insertIndex > 0 && value > set[insertIndex].GetDistFromQuery(vocabulary, queryInd))
      --insertIndex;

    // Insert new value in appropriate index
    bestInd.insert(bestInd.begin() + insertIndex, pair<int, double>(pairInd, value));

    // keep only fixed amount of best options
    bestInd.resize(std::min(static_cast<size_t>(count), bestInd.size()));
  }

  // Make extra effort to sort using lambda
  sort(bestInd.begin(), bestInd.end(), [](const pair<int, double> &left, const pair<int, double> &right)
  {
    return left.second > right.second;
  });

  double threshold = 1e-8;

  // If very best one is so low, than any option is not good enough
  if (set[bestInd[0].first].GetDistFromQuery(vocabulary, queryInd) < threshold)
  {
    vector<pair<int, double>> badOptions(count, pair<int, double>(0, -1));
    return badOptions;
  }

  return bestInd;
}

void QAMachineCore::askQuestion(std::string question)
{
  vector<int> queryInds;
  string word;
  int wordInd;

  size_t start = question.find_first_not_of(delimetrs), end = 0;
  while ((end = question.find_first_of(delimetrs, start)) != string::npos)
  {
    word = question.substr(start, end - start);
    transform(word.begin(), word.end(), word.begin(), ::tolower);

    if ((wordInd = vocabulary.GetWordInd(word)) != -1)
      queryInds.push_back(wordInd);

    start = question.find_first_not_of(delimetrs, end);
  }

  if (start != std::string::npos)
  {
    word = question.substr(start);
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if ((wordInd = vocabulary.GetWordInd(word)) != -1)
      queryInds.push_back(wordInd);
  }

  bestMatchInd = findBest(maxOptions, pairsQAset, vocabulary, queryInds);
  answerInd = bestMatchInd[0].first;
}

std::string QAMachineCore::getAnswer()
{
  if (bestMatchInd[0].second == -1)
    return "Can't find answer";

  return pairsQAset[bestMatchInd[0].first].answer;
}

void QAMachineCore::PrintAnswer(void)
{
  // Check if answer is valid
  if (bestMatchInd[0].second == -1)
  {
    cout << "There is no simular question, so we can't get answer!" << endl;
    
    return;
  }

  // Present best option as answer
  cout << "----------------------------------------------" << endl;
  cout << "Closest question: " << pairsQAset[bestMatchInd[0].first].question <<
     " -> " << pairsQAset[bestMatchInd[0].first].answer << "(" << bestMatchInd[0].second << ")" << endl;
  cout << ">> Other options: " << endl;

  // list other options from bestMatch as well
  // format: >>>> Question: <question> -> <answer> <score>
  for (size_t it = 0; it < bestMatchInd.size() - 1; ++it)
  {
    cout << ">>>> Question: " << pairsQAset[bestMatchInd[it].first].question << " -> " <<
      pairsQAset[bestMatchInd[it].first].answer << " (" << bestMatchInd[it].second << ")" << endl;
  }

  cout << "----------------------------------------------" << endl << endl;
}

void QAMachineCore::LearnFromTSV(const string & fileName, const std::string &rejectedWordsFileName)
{
  vocabulary.GenerateVocabularyFromQAset(fileName, rejectedWordsFileName, pairsQAset);
  pairsQAset.IndexByVocab(vocabulary);
  cout << "Vocabulary size: " << vocabulary.size() << endl;
}

QAMachineCore::~QAMachineCore()
{
}