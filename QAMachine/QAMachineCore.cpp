#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include "QAMachineCore.h"
#include <algorithm>

using namespace std;

const std::string QAMachineCore::delimetrs = " ,.!?";

QAMachineCore::QAMachineCore()
{
  // TODO
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

  int qapInd = 0;

  for (size_t pairInd= 0; pairInd < pairsQAset.size(); ++pairInd)
  {
    val = pairsQAset[pairInd].GetDistFromQuery(vocabulary,queryInds);
    
    if (val > maxValue)
    {
      answerInd = pairInd;
      maxValue = val;
    }

    qapInd++;
  }

  if (maxValue == 0)
    answerInd = -1;
}

std::string QAMachineCore::getAnswer()
{
  // TODO
  if (answerInd == -1)
  {
    return "Can't find answer!";
  }
  return pairsQAset[answerInd].answer;
}

void QAMachineCore::PrintAnswer(void)
{
  if (answerInd == -1)
  {
    cout << "There is no similar question, so we can't get answer!"<< endl;
  }
  cout << "Most sutable question: " + pairsQAset[answerInd].question + "\nAnswer: " + pairsQAset[answerInd].answer + "\n________________________" <<endl;

}

void QAMachineCore::LearnFromTSV(const string & fileName, const std::string &rejectedWordsFileName)
{
  vocabulary.GenerateVocabularyFromQAset(fileName, rejectedWordsFileName, pairsQAset);
  pairsQAset.IndexByVocab(vocabulary);
}

QAMachineCore::~QAMachineCore()
{
}
