#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Vocabulary.h"

using namespace std;

const string Vocabulary::delimetrs = " ,.!?";

void Vocabulary::generateVocabularyFromQAFile(const string & dataFileName, const string & rejectedWordsFileName, QAPairsSet & pairsQAset)
{
  ifstream qAPairsIFS(dataFileName);

  if (!qAPairsIFS.is_open())
  {
    cout << "Could not open QuestionsAnswers pairs file: " << dataFileName << endl;
    string dataFileNameTry = "../" + dataFileName;
    qAPairsIFS = ifstream(dataFileNameTry);
    if (!qAPairsIFS.is_open())
    {
      cout << "Could not open QuestionsAnswers pairs file: " << dataFileNameTry << endl;
      return;
    }
  }

  map<string, int> tempMap; // map used to push words in O(log(n))
  string question;
  string answer;
  string pairStr;
  string word;

  // iterate through lines of dataFile
  while (std::getline(qAPairsIFS, pairStr))
  {
    //get question and answer strings
    question = pairStr.substr(0, pairStr.find(';'));
    answer = pairStr.substr(pairStr.find(';') + 1);

    // lefttrim answer string
    size_t fNotSp = answer.find_first_not_of(" \t");
    if (fNotSp != -1)
      answer = answer.substr(fNotSp);

    pairsQAset.addPair(question, answer);

    // iterate through words of question
    size_t start = question.find_first_not_of(delimetrs), end = 0;
    while ((end = question.find_first_of(delimetrs, start)) != string::npos)
    {
      word = question.substr(start, end - start);
      // transform to lowercase
      transform(word.begin(), word.end(), word.begin(), ::tolower);
      tempMap[word]++;
      //find next word's start
      start = question.find_first_not_of(delimetrs, end);
    }
    //proceed last word
    if (start != string::npos)
    {
      word = question.substr(start);
      // transform to lowercase
      transform(word.begin(), word.end(), word.begin(), ::tolower);
      tempMap[word]++;
    }
  }
  qAPairsIFS.close();
  // File parsing ended

  // delete rejected words from map
  string rWord;
  ifstream rejectedWordsIFS(rejectedWordsFileName);
  if (!rejectedWordsIFS.is_open())
  {
    cout << "Could not open Rejected words file: " << rejectedWordsFileName << endl;
    string rejectedWordsFileNameTry = "../" + rejectedWordsFileName;
    rejectedWordsIFS = ifstream(rejectedWordsFileNameTry);
    if (!rejectedWordsIFS.is_open())
    {
      cout << "Could not open Rejected words file: " << rejectedWordsFileNameTry << endl;
      return;
    }
  }

  while (rejectedWordsIFS >> rWord)
  {
    tempMap.erase(rWord);
  }
  rejectedWordsIFS.close();

  // resave as vector and calcualate idf
  for (auto &w : tempMap)
  {
    vocabulary.emplace_back(WordPair(w.first, (double)w.second));
  }
}

int Vocabulary::getWordInd(const string & word) const
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

size_t Vocabulary::size()
{
  return vocabulary.size();
}

Vocabulary::WordPair & Vocabulary::operator[](size_t ind)
{
  return vocabulary[ind];
}

std::vector<int> Vocabulary::parseStrByVocabInds(std::string & str) const
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
    if ((wordInd = this->getWordInd(word)) != -1)
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
    if ((wordInd = this->getWordInd(word)) != -1)
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

vector<Vocabulary::WordPair>::iterator Vocabulary::begin(void)
{
  return vocabulary.begin();
}

vector<Vocabulary::WordPair>::iterator Vocabulary::end(void)
{
  return vocabulary.end();
}


