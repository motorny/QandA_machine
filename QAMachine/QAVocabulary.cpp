#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "QAVocabulary.h"

using namespace std;

const string QAVocabulary::delimetrs = " ,.!?";

void QAVocabulary::GenerateVocabularyFromQAset(const string & dataFileName, const string & rejectedWordsFileName, QApairsQAset & pairsQAset)
{
  ifstream qAPairsIFS(dataFileName);

  if (!qAPairsIFS.is_open()) {
    cout << "Could not open QuestionsAnswers pairs file: " << dataFileName << endl;
    return;
  }

  map<string, int> tempMap;
  string question;
  string answer;
  string pairStr;
  string word;
  int questionsCnt = 0;
  while (std::getline(qAPairsIFS, pairStr))
  {
    questionsCnt++;
    question = pairStr.substr(0, pairStr.find(';'));
    answer = pairStr.substr(pairStr.find(';') + 1);
    pairsQAset.AddPair(question, answer);

    size_t start = question.find_first_not_of(delimetrs), end = 0;
    while ((end = question.find_first_of(delimetrs, start)) != string::npos)
    {
      word = question.substr(start, end - start);
      transform(word.begin(), word.end(), word.begin(), ::tolower);
      tempMap[word]++;
      start = question.find_first_not_of(delimetrs, end);
    }
    if (start != string::npos)
    {
      word = question.substr(start);
      transform(word.begin(), word.end(), word.begin(), ::tolower);
      tempMap[word]++;
    }
  }
  qAPairsIFS.close();
  // File parsing ended

  string rWord;
  ifstream rejectedWordsIFS(rejectedWordsFileName);
  if (!rejectedWordsIFS.is_open()) {
    cout << "Could not open Rejected words file: " << rejectedWordsFileName << endl;
    return;
  }

  while (rejectedWordsIFS >> rWord)
  {
    tempMap.erase(rWord);
  }
  rejectedWordsIFS.close();

  // resave as vector and calcualate idf
  for (auto &w : tempMap)
  {
    vocabulary.emplace_back(WordPair(w.first, log((double)questionsCnt / (double)w.second)));
  }
}

int QAVocabulary::GetWordInd(const string & word)
{
  //int left = 0, right = vocabulary.size() - 1;
  //int middle;

  //while (right >= left)
  //{
  //  middle = left + (right - left) / 2;

  //  if (vocabulary[middle].str == word)
  //    return static_cast<int>(middle);

  //  if (vocabulary[middle].str < word)
  //    right = middle - 1;
  //  else
  //    left = middle + 1;
  //}
  for (size_t ind = 0; ind < vocabulary.size(); ++ind)
  {
    if (word == vocabulary[ind].str)
    {
      return (int)ind;
    }
  }
  
  //std::cout << "NOT FOUND IN DICT" << endl;
  return -1;
}

size_t QAVocabulary::size()
{
  return vocabulary.size();
}

QAVocabulary::WordPair & QAVocabulary::operator[](size_t ind)
{
  return vocabulary[ind];
}


