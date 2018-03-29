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
  size_t start = question.find_first_not_of(delimetrs), end = 0;
  while ((end = question.find_first_of(delimetrs, start)) != std::string::npos)
  {
    word = question.substr(start, end - start);
    transform(word.begin(), word.end(), word.begin(), ::tolower);

    /* TO DO:
    Lecsigraphical search
    */
    for (size_t ind = 0; ind < vocabulary.size(); ++ind)
    {
      if (word == vocabulary[ind].str)
      {
        queryInds.push_back(ind);
        break;
      }
    }
    start = question.find_first_not_of(delimetrs, end);
  }
  if (start != std::string::npos)
  {
    word = question.substr(start);
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    /* TO DO:
    Lecsigraphical search
    */
    for (size_t ind = 0; ind < vocabulary.size(); ++ind)
    {
      if (word == vocabulary[ind].str)
      {
        queryInds.push_back(ind);
        break;
      }
    }
  }


  /*for (int i : queryInds) 
  {
    cout << vocabulary[i].str << " ";
  }
  cout << endl;*/

  double maxValue = 0.0, val;
  int qapInd = 0;
  for (auto &qaP : questAnswArr)
  {
    val = 0.0;
    for (size_t iQueryInd = 0; iQueryInd < queryInds.size(); ++iQueryInd)
    {
      for (size_t iDBQInd = iQueryInd; iDBQInd < qaP.wordIndeces.size(); ++iDBQInd)
      {
        if (queryInds[iQueryInd] == qaP.wordIndeces[iDBQInd])
          val += vocabulary[queryInds[iQueryInd]].idf;
      }
    }

    val *= qaP.invEuqlidSize;
    if (val > maxValue)
    {
      answerInd = qapInd;
      maxValue = val;
    }

    qapInd++;
  }


}

std::string QAMachineCore::getAnswer()
{
  // TODO

  return questAnswArr[answerInd].answer;
}

void QAMachineCore::LearnFromTSV(const string & fileName, const std::string &rejectedWordsFileName)
{

  ifstream qAPairsIFS(fileName);
  if (!qAPairsIFS.is_open()) {
    cout << "Could not open QuestionsAnswers pairs file: " << fileName << endl;
    return;
  }

  map<string, int> tempMap;
  string question;
  string answer;
  string pairStr;
  string word;
  while (std::getline(qAPairsIFS, pairStr))
  {
    questionsCnt++;
    question = pairStr.substr(0, pairStr.find(';'));
    answer = pairStr.substr(pairStr.find(';') + 1);
    questAnswArr.push_back(QAPair(question, answer));
    //cout << "Question: " << question << " Answer: " << answer << endl;
    size_t start = question.find_first_not_of(delimetrs), end = 0;
    while ((end = question.find_first_of(delimetrs, start)) != std::string::npos)
    {
      word = question.substr(start, end - start);
      transform(word.begin(), word.end(), word.begin(), ::tolower);
      tempMap[word]++;
      start = question.find_first_not_of(delimetrs, end);
    }
    if (start != std::string::npos)
    {
      word = question.substr(start);
      transform(word.begin(), word.end(), word.begin(), ::tolower);
      tempMap[word]++;
    }
  }
  qAPairsIFS.close();

  string rWord;
  ifstream rejectedWordsIFS(rejectedWordsFileName);
  if (!rejectedWordsIFS.is_open()) {
    cout << "Could not open Rejected words file: " << fileName << endl;
    return;
  }
  while (rejectedWordsIFS >> rWord)
  {
    rejectedWords.push_back(rWord);
    tempMap.erase(rWord);
  }

  rejectedWordsIFS.close();

  for (auto &w : tempMap)
  {
    vocabulary.emplace_back(WordPair(w.first, (double)w.second));
  }

  cout << "Questions count: " << questionsCnt << endl;
  for (auto &wp : vocabulary)
  {
    wp.idf = log((double)questionsCnt / wp.idf);
    cout << wp.str << " cnt: " << wp.idf << endl;
  }
  //end preparing vocabulary

  for (auto &qaP : questAnswArr)
  {
    int wordsCnt = 0;
    size_t start = qaP.question.find_first_not_of(delimetrs), end = 0;
    while ((end = qaP.question.find_first_of(delimetrs, start)) != std::string::npos)
    {
      word = qaP.question.substr(start, end - start);
      transform(word.begin(), word.end(), word.begin(), ::tolower);
      /* TO DO:
      Lecsigraphical search
      */
      for (size_t ind = 0; ind < vocabulary.size(); ++ind)
      {
        if (word == vocabulary[ind].str)
        {
          qaP.wordIndeces.push_back(ind);
          break;
        }
      }

      wordsCnt++;
      start = qaP.question.find_first_not_of(delimetrs, end);
    }
    if (start != std::string::npos)
    {
      word = qaP.question.substr(start);
      transform(word.begin(), word.end(), word.begin(), ::tolower);

      for (size_t ind = 0; ind < vocabulary.size(); ++ind)
      {
        if (word == vocabulary[ind].str)
        {
          qaP.wordIndeces.push_back(ind);
          break;
        }
      }

      wordsCnt++;
    }

    qaP.invEuqlidSize = 1 / sqrt((double)wordsCnt);
  }


  for (auto &qaP : questAnswArr)
  {
    cout << qaP.question << " INDS: ";
    for (auto wI : qaP.wordIndeces)
      cout << wI << " ";
    cout << endl;
  }

}

QAMachineCore::~QAMachineCore()
{
}
