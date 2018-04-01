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
    size_t fNotSp = answer.find_first_not_of(" \t");
    if (fNotSp != -1)
      answer = answer.substr(fNotSp);
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

int QAVocabulary::GetWordInd(const string & word) const
{
  int left = 0, right = vocabulary.size() - 1;
  int middle;

  while (right >= left)
  {
    middle = left + (right - left) / 2;

    if (vocabulary[middle].word == word)
      return middle;

    if (vocabulary[middle].word > word)
      right = middle - 1;
    else
      left = middle + 1;
  }

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

std::vector<int> QAVocabulary::ParseStrByVocabInds(std::string & str) const
{
  string word;
  vector<int> res;
  int wordInd;
  bool indRepeat;
  size_t start = str.find_first_not_of(delimetrs), end = 0;

  // iterate by words untill end of string
  while ((end = str.find_first_of(delimetrs, start)) != string::npos)
  {
    word = str.substr(start, end - start);
    // make word lowercase
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if ((wordInd = this->GetWordInd(word)) != -1)
    {
      // check for wordInd uniquenss
      indRepeat = false;
      for (int wInd : res)
        if (wInd == wordInd)
          indRepeat = true;

      if (!indRepeat)
        res.push_back(wordInd);
    }

    // recalculate new word start
    start = str.find_first_not_of(delimetrs, end);
  }

  //proceed last word
  if (start != std::string::npos)
  {
    word = str.substr(start);
    // make word lowercase
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if ((wordInd = this->GetWordInd(word)) != -1)
    {
      // check for wordInd uniquenss
      indRepeat = false;
      for (int wInd : res)
        if (wInd == wordInd)
          indRepeat = true;

      if (!indRepeat)
        res.push_back(wordInd);
    }
  }

  return res;
}

vector<QAVocabulary::WordPair>::iterator QAVocabulary::begin(void)
{
  return vocabulary.begin();
}

vector<QAVocabulary::WordPair>::iterator QAVocabulary::end(void)
{
  return vocabulary.end();
}


