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
vector<int> findBest(int count, QApairsQAset &set,
  QAVocabulary &vocabulary, vector<int> &queryInd)
{
  vector<int> bestInd;
  double value;

  // Iterate through the whole set to find best options
  for (size_t pairInd = 0; pairInd < set.size(); ++pairInd)
  {
    // cache value of current option
    value = set[pairInd].GetDistFromQuery(vocabulary, queryInd);

    // Find place for insertion
    int insertIndex = bestInd.size() - 1;
    while (value > set[insertIndex].GetDistFromQuery(vocabulary, queryInd))
      ++insertIndex;
    // Insert new value in appropriate index
    bestInd.insert(bestInd.begin() + insertIndex, pairInd);

    // keep only fixed amount of best options
    bestInd.resize(count);
  }

  double threshold = 1e-8;

  // If very best one is so low, than any option is not good enough
  if (set[bestInd[0]].GetDistFromQuery(vocabulary, queryInd) < threshold)
  {
    vector<int> badOptions(count, -1);
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

  double maxValue = 0.0, val;

  for (size_t pairInd = 0; pairInd < pairsQAset.size(); ++pairInd)
  {
    val = pairsQAset[pairInd].GetDistFromQuery(vocabulary,queryInds);
    
    if (val > maxValue)
    {
      answerInd = pairInd;
      maxValue = val;
    }
  }

  if (maxValue == 0)
    answerInd = -1;

  bestMatchInd = vector<int>(maxOptions, answerInd);

  //bestMatchInd = findBest(maxOptions, pairsQAset, vocabulary, queryInds);
  //answerInd = bestMatchInd[0];
}

std::string QAMachineCore::getAnswer()
{
  if (bestMatchInd[0] == -1)
    return "Can't find answer";

  return pairsQAset[bestMatchInd[0]].answer;
}

void QAMachineCore::PrintAnswer(void)
{
  if (bestMatchInd[0] == -1)
  {
    cout << "There is no simular question, so we can't get answer!" << endl;
  }
  cout << "----------------------------------------------" << endl;
  cout << "Closest question: " << pairsQAset[bestMatchInd[0]].question <<
    " -> " << pairsQAset[bestMatchInd[0]].answer << endl;
  cout << ">> Other options: " << endl;

  for (size_t it = 0; it < bestMatchInd.size() - 1; ++it)
  {
    cout << ">>>> Question: " << pairsQAset[it].question << " -> " <<
      pairsQAset[it].answer << " " << it << endl;
  }

  cout << "----------------------------------------------" << endl;
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